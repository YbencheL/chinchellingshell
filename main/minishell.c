/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/23 10:34:47 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;

// void print_cmds(t_cmds *cmds)
// {
//     int i;
//     t_file *file;
//     t_cmds *current;
    
//     if (!cmds)
//     {
//         printf("No commands to print\n");
//         return;
//     }
    
//     current = cmds;
//     printf("\n----- COMMAND STRUCTURE -----\n");
    
//     while (current)
//     {
//         printf("\n• Command: ");
//         if (current->cmds)
//         {
//             i = 0;
//             while (current->cmds[i])
//             {
//                 printf("[%s] ", current->cmds[i]);
//                 i++;
//             }
//         }
//         else
//             printf("[None]");
            
//         printf("\n• Redirections: ");
//         file = current->files;
//         if (!file)
//             printf("[None]\n");
//         else
//         {
//             printf("\n");
//             while (file)
//             {
//                 printf("  - File: %s, Type: ", file->file);
//                 if (file->type == RED_IN)
//                     printf("Input Redirection (<)\n");
//                 else if (file->type == RED_OUT)
//                     printf("Output Redirection (>)\n");
//                 else if (file->type == RED_APPEND)
//                     printf("Append Redirection (>>)\n");
//                 else if (file->type == HEREDOC)
//                     printf("Heredoc (<<)\n");
//                 else
//                     printf("Unknown\n");
//                 file = file->next;
//             }
//         }
        
//         if (current->next)
//             printf("\n|  Pipe  |\n↓\n");
            
//         current = current->next;
//     }
//     printf("\n---------------------------\n\n");
// }

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
