/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/23 15:08:22 by ybenchel         ###   ########.fr       */
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

void print_all_heredocs(t_file *files)
{
    t_file *current = files;
    int heredoc_count = 0;
    
    while (current)
    {
        if (current->type == HEREDOC)
        {
            heredoc_count++;
            printf("\n\033[1;33m┌─ Heredoc #%d (\"%s\") ────────────┐\033[0m\n", 
                   heredoc_count, current->file);
            
            int stdin_backup = dup(STDIN_FILENO);
            dup2(current->fd, STDIN_FILENO);
            
            char buffer[1024];
            ssize_t bytes_read;
            printf("\033[1;37m");
            while ((bytes_read = read(STDIN_FILENO, buffer, 1023)) > 0)
            {
                buffer[bytes_read] = '\0';
                printf("%s", buffer);
            }
            printf("\033[0m");
            printf("\n\033[1;33m└─────────────────────────────────┘\033[0m\n");
            
            // Restore stdin
            dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
        }
        current = current->next;
    }
    
    if (heredoc_count == 0)
        printf("\n\033[1;31m[No heredocs found]\033[0m\n");
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
            print_cmds(cmds);
                
            // Test heredoc functionality
            if (cmds->files && cmds->files->type == HEREDOC)
            {
                printf("\n\033[1;33m[Testing Heredocs]\033[0m\n");
                check_herdoc(cmds->files);
                
                // Print contents of ALL heredocs
                print_all_heredocs(cmds->files);
            }
        }
        free(rl);
    }
    clear_history();
}

int	main(int ac, char **av, char **env)
{
    t_mp	pg;

    pg.exit_status = 0;
    g_gbc = ft_lstnew_custom(NULL);
    check_args(ac, av);
    pg.envp = init_env(env);
    print_banner();
    signal_setup();
    shell_loop(&pg);
    print_exit();
    ft_lstclear(&g_gbc, free);
}
