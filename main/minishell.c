/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/23 12:40:29 by ybenchel         ###   ########.fr       */
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
        printf("\n\033[1;31m[DEBUG] No commands to print\033[0m\n");
        return;
    }
    
    current = cmds;
    printf("\n\033[1;36m===== COMMAND STRUCTURE (DEBUG) =====\033[0m\n");
    
    int cmd_num = 0;
    while (current)
    {
        cmd_num++;
        printf("\n\033[1;33m[Command #%d]\033[0m\n", cmd_num);
        
        // Print command and arguments
        printf("• \033[1;32mCommand:\033[0m ");
        if (current->cmds)
        {
            i = 0;
            printf("\n");
            while (current->cmds[i])
            {
                printf("  - Arg[%d]: \"%s\"\n", i, current->cmds[i]);
                i++;
            }
            printf("  - Total arguments: %d\n", i);
        }
        else
            printf("\033[1;31m[None]\033[0m\n");
            
        // Print all redirections
        printf("• \033[1;32mRedirections:\033[0m ");
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
                printf("  - File[%d]: \"%s\", Type: ", file_count, file->file);
                if (file->type == RED_IN)
                    printf("\033[1;34mInput Redirection (<)\033[0m");
                else if (file->type == RED_OUT)
                    printf("\033[1;34mOutput Redirection (>)\033[0m");
                else if (file->type == RED_APPEND)
                    printf("\033[1;34mAppend Redirection (>>)\033[0m");
                else if (file->type == HEREDOC)
                    printf("\033[1;34mHeredoc (<<)\033[0m");
                else
                    printf("\033[1;31mUnknown\033[0m");
                
                printf(", FD: %d\n", file->fd);
                file = file->next;
            }
            printf("  - Total redirections: %d\n", file_count);
        }
        
        if (current->next)
            printf("\n\033[1;35m|     PIPE     |\n      ↓      \033[0m\n");
            
        current = current->next;
    }
    printf("\n\033[1;36m===================================\033[0m\n\n");
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
                printf("\n\033[1;33m[Testing Heredoc]\033[0m\n");
                check_herdoc(cmds->files);
                
                // Create a simple command to display the heredoc content
                // For example, if we want to cat the heredoc content:
                printf("\n\033[1;33m[Heredoc Content]\033[0m\n");
                int stdin_backup = dup(STDIN_FILENO);
                
                // Set up the input redirection from heredoc
                dup2(cmds->files->fd, STDIN_FILENO);
                
                // Read and display the content
                char buffer[1024];
                ssize_t bytes_read;
                while ((bytes_read = read(STDIN_FILENO, buffer, 1023)) > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("%s", buffer);
                }
                
                // Restore stdin
                dup2(stdin_backup, STDIN_FILENO);
                close(stdin_backup);
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
