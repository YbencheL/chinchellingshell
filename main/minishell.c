/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/16 13:06:43 by ybenchel         ###   ########.fr       */
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
			t_token **tokens = tokens_to_cmds(token);
                
            int i = 0;
            while (tokens[i])
            {
                t_token *current = tokens[i];
                printf("== Command #%d ==\n", i + 1);
                
                // Display command type
                if (current->type == CMD)
                    printf("Type: Command\n");
                else if (current->type == PIPELINE)
                    printf("Type: Pipeline\n");
                else if (current->type == RED_IN)
                    printf("Type: IN (%d)\n", current->type);
				else if (current->type == RED_OUT)
                    printf("Type: OUT (%d)\n", current->type);
				else if (current->type == RED_APPEND)
                    printf("Type: APPEND (%d)\n", current->type);
				else if (current->type == FILE_ARG)
                    printf("Type: FILE (%d)\n", current->type);
                // Display command content
                if (current->cmds && current->cmds[0])
                    printf("Command string: %s\n", current->cmds[0]);
                else
                    printf("No command string\n");
                
                // Display heredoc flag
                if (current->heredoc)
                    printf("Has heredoc: Yes\n");
                else
                    printf("Has heredoc: No\n");
                
                printf("\n");
                i++;
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
