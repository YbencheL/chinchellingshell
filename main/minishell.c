/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/10 20:01:11 by abenzaho         ###   ########.fr       */
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
		rl = readline("\033[1;32mMinishell$\033[0m ");
		if (!rl)
		 	return ;
		if (ft_strlen(rl))
		{
			add_history(rl);
			if (!check_unclosed_quotes(rl, pg))
			{
				free(rl);
				continue;
			}
			token = add_token(split_words(rl));
			if (!typeof_token(token, pg))	
			{
				free(rl);
				continue;
			}
			//expand_variables(token, pg);
			head = token;
			while (token != NULL)
			{
				printf("%s is of type : %d\n", token->arg, token->type);
				token = token->next;
			}
			token = head;
			// t_token *tokens = tokens_to_cmds(token);  // Convert tokens to commands
			// t_token *current = tokens;
			// int cmd_num = 1;
			
			// while (current)
			// {
			// 	printf("== Command #%d ==\n", cmd_num);
			
			// 	// Print command and arguments
			// 	t_cmd *cmd = current->cmds;
			// 	if (cmd)
			// 	{
			// 		printf("Command and args: ");
			// 		while (cmd)
			// 		{
			// 			for (int i = 0; cmd->arg[i]; i++)
			// 				printf("[%s] ", cmd->arg[i]);
			// 			cmd = cmd->next;
			// 		}
			// 		printf("\n");
			// 	}
			
			// 	// Print redirections
			// 	t_red *red = current->redi;
			// 	if (red)
			// 	{
			// 		printf("Redirections:\n");
			// 		while (red)
			// 		{
			// 			if (*(red->type) == RED_IN)
			// 				printf("  Input: [%s]\n", red->file);
			// 			else if (*(red->type) == RED_OUT)
			// 				printf("  Output: [%s]\n", red->file);
			// 			else if (*(red->type) == RED_APPEND)
			// 				printf("  Append: [%s]\n", red->file);
			// 			else if (*(red->type) == HEREDOC)
			// 				printf("  Heredoc: [%s]\n", red->file);
			// 			red = red->next;
			// 		}
			// 	}
			
			// 	if (current->heredoc)
			// 		printf("Heredoc active: yes\n");
			
			// 	printf("\n");
			// 	current = current->next;
			// 	cmd_num++;
			// }		
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
