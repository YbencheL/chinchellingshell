/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/16 14:57:55 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;

void shell_loop(t_mp *pg)
{
    char    *rl;
    t_arg	*token;
    t_arg	*head;
    
    token = NULL;
    while (1)
    {
        rl = readline("Minishell$ ");
        if (!rl)
             return ;
        if (ft_strlen(rl))
        {
            add_history(rl);
            if (!check_unclosed_quotes(rl, pg))
                continue;
            token = tokenize(rl, pg);
            if (!token)	
                continue;
            expand_variables(token, pg);
            handle_var_space(&token);
            head = token;
            while (token != NULL)
            {
                printf("%s is of type : %d\n", token->arg, token->type);
                token = token->next;
            }
            token = head;
			t_token *tokens = tokens_to_cmds(token);
            t_token *current = tokens;
            
            printf("\n+--------------- COMMAND INFORMATION ---------------+\n");
            int i = 0;
            while (current)
            {
                printf("| Command #%d:\n", i + 1);
                printf("+---------------------------------------------------+\n");
                
                // Display command content
                if (current->cmds && current->cmds[0])
                {
                    printf("| Command: %s\n", current->cmds[0]);
                    
                    // Display all arguments
                    printf("| Arguments: ");
                    int arg_idx = 1;
                    if (current->cmds[arg_idx])
                    {
                        while (current->cmds[arg_idx])
                        {
                            printf("%s ", current->cmds[arg_idx]);
                            arg_idx++;
                        }
                        printf("\n");
                    }
                    else
                        printf("None\n");
                }
                else
                    printf("| No command string\n");
                
                // Display command type
                printf("| Type: ");
                if (current->type == CMD)
                    printf("Command\n");
                else if (current->type == PIPELINE)
                    printf("Pipeline\n");
                else if (current->type == RED_IN)
                    printf("IN (%d)\n", current->type);
                else if (current->type == RED_OUT)
                    printf("OUT (%d)\n", current->type);
                else if (current->type == RED_APPEND)
                    printf("APPEND (%d)\n", current->type);
                else if (current->type == FILE_ARG)
                    printf("FILE (%d)\n", current->type);
                else
                    printf("Unknown (%d)\n", current->type);
                
                // Display heredoc flag
                printf("| Heredoc: %s\n", current->heredoc ? "Yes" : "No");
                
                printf("+---------------------------------------------------+\n");
                current = current->next;
                i++;
            }
            printf("\n");
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
