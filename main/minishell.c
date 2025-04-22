/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/22 17:57:59 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;

void print_cmds(t_cmds *cmds)
{
    t_cmds *current = cmds;
    int stdin_backup, stdout_backup;
    
    in_n_out_backup(&stdin_backup, &stdout_backup);    
    
    while (current)
    {
        printf("Command: ");
        for (int i = 0; current->cmds && current->cmds[i]; i++)
        {
            printf("%s ", current->cmds[i]);
        }
        printf("\n");
        
        t_file *file = current->files;
        while (file)
        {
            printf("  File: %s, Type: ", file->file);
            if (file->type == RED_IN)
            {
                printf("Input < ");
                int fd = open(file->file, O_RDONLY);
                if (fd != -1)
                {
                    printf("(fd: %d) - Redirecting input\n", fd);
                    dup_in(fd);
                }
                else
                    printf("(fd: -1) - Failed to open file\n");
            }
            else if (file->type == RED_OUT)
            {
                printf("Output > ");
                int fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd != -1)
                {
                    printf("(fd: %d) - Redirecting output\n", fd);
                    dup_out(fd);
                }
                else
                    printf("(fd: -1) - Failed to open file\n");
            }
            else if (file->type == RED_APPEND)
            {
                printf("Append >> ");
                int fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd != -1)
                {
                    printf("(fd: %d) - Redirecting output (append)\n", fd);
                    dup_out(fd);
                }
                else
                    printf("(fd: -1) - Failed to open file\n");
            }
            else if (file->type == HEREDOC)
            {
                printf("Heredoc << ");
                printf("(fd: %d) - Processing heredoc\n", file->fd);
                check_herdoc(current->files);
                break;
            }
            file = file->next;
        }
        
        current = current->next;
    }
    
    // Restore standard input/output
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdin_backup);
    close(stdout_backup);
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
             return ;
        if (ft_strlen(rl))
        {
            add_history(rl);
			cmds = parsing(rl, pg);
			if (!cmds)
				continue;
           // print_cmds(cmds);
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
