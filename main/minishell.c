/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/08 19:50:49 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;

void shell_loop(t_mp *pg)
{
	char    *rl;
	t_arg	*token;
	t_cmd	*cmds;
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
			head = token;
			while (token != NULL)
			{
				printf("%s is of type : %d\n", token->arg, token->type);
				token = token->next;
			}
			token = head;
		// 	f = split_phrase(rl, pg);
		// 	token = split_tokens(f);
		// 	typeof_token(token);
		// 	if (!error_slayer(token, pg))
		// 		continue;
		// 	checking_variables(token, pg);
		// 	head = token;
		// 	while (token != NULL)
		// 	{
		// 		printf("%s is of type : %d\n", token->arg, token->type);
		// 		token = token->next;
		// 	}
		token = head;
		cmds = tokens_to_cmds(token);
		t_cmd *current = cmds;
		int i = 1;
		while (current)
		{
			printf("== Command #%d ==\n", i);
			if (current->cmds)
			{
				printf("Command and args: ");
				for (int j = 0; current->cmds[j]; j++)
					printf("[%s] ", current->cmds[j]);
				printf("\n");
			}
			if (current->infile)
				printf("Input Redirection: %s\n", current->infile);
			if (current->appendfile)
				printf("Append Redirection: %s\n", current->appendfile);
			if (current->outfile)
				printf("Output Redirection: %s\n", current->outfile);
			printf("\n");
			current = current->next;
			i++;
		}		
		// 	// // Step 6: Execute Commands
		// 	// execute_commands(cmds, pg);
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
