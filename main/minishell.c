/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/08 09:48:12 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;

void print_cmds(t_cmds *cmds)
{
    int i;
    t_file *file;
    t_cmds *current;
    
    if (!cmds)
    {
        printf("\n\033[1;31m[DEBUG] No commands to parse or execute\033[0m\n");
        return;
    }
    
    current = cmds;
    printf("\n\033[1;36m╔════════ COMMAND STRUCTURE ════════╗\033[0m\n");
    
    int cmd_num = 0;
    while (current)
    {
        cmd_num++;
        printf("\n\033[1;33m┌─ Command #%d ─────────────────────┐\033[0m\n", cmd_num);
        
        // Print command and arguments
        printf("\033[1;33m│\033[0m \033[1;32mCommand:\033[0m ");
        if (current->cmds)
        {
            i = 0;
            printf("\n");
            while (current->cmds[i])
            {
                printf("\033[1;33m│\033[0m   - Arg[%d]: \033[1;37m\"%s\"\033[0m\n", i, current->cmds[i]);
                i++;
            }
            printf("\033[1;33m│\033[0m   - Total arguments: \033[1;37m%d\033[0m\n", i);
        }
        else
            printf("\033[1;31m[None]\033[0m\n");
            
        // Print all redirections
        printf("\033[1;33m│\033[0m \033[1;32mRedirections:\033[0m ");
        file = current->files;
        if (!file)
            printf("\033[1;31m[None]\033[0m\n");
        else
        {
            int file_count = 0;
            printf("\n");
            while (file)
            {
                file_count++;
                printf("\033[1;33m│\033[0m   - File[%d]: \033[1;37m\"%s\"\033[0m, Type: ", file_count, file->file);
                if (file->type == RED_IN)
                    printf("\033[1;34m< (Input)\033[0m");
                else if (file->type == RED_OUT)
                    printf("\033[1;34m> (Output)\033[0m");
                else if (file->type == RED_APPEND)
                    printf("\033[1;34m>> (Append)\033[0m");
                else if (file->type == HEREDOC)
                    printf("\033[1;34m<< (Heredoc)\033[0m");
                else
                    printf("\033[1;31mUnknown\033[0m");
                
                printf(", FD: \033[1;37m%d\033[0m\n", file->fd);
                file = file->next;
            }
            printf("\033[1;33m│\033[0m   - Total redirections: \033[1;37m%d\033[0m\n", file_count);
        }
        
        if (current->next)
            printf("\n\033[1;35m|     PIPE     |\n      ↓      \033[0m\n");
            
        current = current->next;
    }
    printf("\n\033[1;36m╚═══════════════════════════════════╝\033[0m\n\n");
}

void print_all_heredocs(t_cmds *cmds)
{
	t_cmds *current_cmd = cmds;
	int cmd_count = 0;
	int total_heredocs = 0;
	
	printf("\n\033[1;36m╔════════ HEREDOC CONTENTS ════════╗\033[0m\n");
	
	while (current_cmd)
	{
		cmd_count++;
		t_file *current = current_cmd->files;
		int heredoc_count = 0;
		
		while (current)
		{
			if (current->type == HEREDOC && current->fd > 0)
			{
				heredoc_count++;
				total_heredocs++;
				printf("\n\033[1;33m┌─ Command #%d - Heredoc #%d (\"%s\") ─┐\033[0m\n", 
					   cmd_count, heredoc_count, current->file);
				
				// Read the heredoc content properly
				lseek(current->fd, 0, SEEK_SET);
				char buffer[1024];
				ssize_t bytes_read;
				printf("\033[1;37m");
				while ((bytes_read = read(current->fd, buffer, 1023)) > 0)
				{
					buffer[bytes_read] = '\0';
					printf("%s", buffer);
				}
				printf("\033[0m");
				printf("\n\033[1;33m└─────────────────────────────────┘\033[0m\n");
			}
			current = current->next;
		}
		
		current_cmd = current_cmd->next;
	}
	
	if (total_heredocs == 0)
		printf("\n\033[1;31m[No heredocs found]\033[0m\n");
	
	printf("\n\033[1;36m╚═══════════════════════════════════╝\033[0m\n\n");
}

int builtins(t_cmds *cmds, t_mp *pg)
{
	if (!cmds->cmds || !cmds->cmds[0])
		return 1;
    if (!ft_strcmp(cmds->cmds[0], "cd"))
    {
        cd(cmds);
        return 0;
    }
    if (!ft_strcmp(cmds->cmds[0], "export"))
    {
        export(cmds, pg->env);
        return 0;
    }
    if (!ft_strcmp(cmds->cmds[0], "env"))
    {
        env(cmds, pg->env);
        return 0;
    }
    if (!ft_strcmp(cmds->cmds[0], "pwd"))
    {
        pwd();
        return 0;
    }
	if (!ft_strcmp(cmds->cmds[0], "echo"))
    {
        echo(cmds);
        return 0;
    }
    if (!ft_strcmp(cmds->cmds[0], "unset"))
    {
        unset(cmds, pg->env);
        return 0;
    }
	if (!ft_strcmp(cmds->cmds[0], "exit"))
    {
        bin_exit(cmds, pg);
        return 0;
    }
    return 1;
}

void	execution(t_cmds *cmds, t_mp *pg)
{
	int	cmd_count;
	t_cmds *cmd_ptr;

	fill_herdoc(cmds, pg);
	cmd_ptr = cmds;
	cmd_count = 0;
	while(cmd_ptr)
	{
		cmd_count++;
		cmd_ptr = cmd_ptr->next;
	}
	if (cmd_count == 1)
	{
		execute_one_cmd(cmds, pg);
		close_files(cmds->files);
		restor_fd(pg->std_in, pg->std_out);
	}
	else
		execute_multiple_commands(cmds, cmd_count, pg);
	return;
}

t_cmds	*parsing(char *rl, t_mp *pg)
{
	t_arg	*token;
    t_token *tokens;
    t_cmds  *cmds;
	
	if (!check_unclosed_quotes(rl, pg))
		return (NULL);
	token = tokenize(rl, pg);
	if (!token)	
		return (NULL);
	expand_variables(token, pg);
	handle_var_space(&token);
	tokens = tokens_to_cmds(token);
	cmds = get_final_cmds(tokens);
	if (check_files(cmds,pg))
		return (NULL);
	remove_quotes(cmds);
	return (cmds);
}

void shell_loop(t_mp *pg)
{
    char    *rl;
    t_cmds  *cmds;
    while (1)
    {
        rl = readline("Minishell$ ");
        if (!rl)
             return;
        if (ft_strlen(rl))
        {
            add_history(rl);
            cmds = parsing(rl, pg);
			if (!cmds)
                continue;
            // print_cmds(cmds);
			execution(cmds, pg);   
            // Test heredoc functionality with all commands
            // print_all_heredocs(cmds);
            // execution(cmds, pg);   
        }
        free(rl);
    }
    clear_history();
}

int	main(int ac, char **av, char **env)
{
    t_mp	pg;

    pg.exit_status = 0;
    pg.is_child = 0;
    g_gbc = ft_lstnew_custom(NULL);
    check_args(ac, av);
    pg.env = init_env(env);
    pg.envp = env;
    // print_banner();
    signal_setup();
	in_n_out_backup(&pg);
    shell_loop(&pg);
    // print_exit();
	close(pg.std_in);
	close(pg.std_out);
    ft_lstclear(&g_gbc, free);
}
