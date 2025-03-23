/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/23 20:26:49 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;
/*  need to inisialize this garbage collector and first use ft_lstnew to get the first node
    use this to add another adresse 					ft_lstadd_back(&g_gbc, *ft_lstnew(ptr))
	to free all the memory thats allocated use this 	ft_lstclear(t_list &gbc, free)
    */

void shell_loop(void)
{
	char    *rl;
	/*t_token *tokens;
	t_cmd   *cmds;*/
	t_list	*f;
	t_arg	*token;
	t_arg	*head;
	//char	**str;
	
	//t_list *current;
	while (1)
	{
		rl = readline("Minishell$ ");
		// hadi hiya li katkhdm ctr + d ila haydtiha ctr + d maghatkhdmsh
		if (!rl)
		 	return ;
		if (ft_strlen(rl))
		{
			add_history(rl);
			f = split_phrase(rl);
			token = split_tokens(f);
			typeof_token(token);
			if (!error_slayer(token))
				continue;
			head = token;
			while (token != NULL)
			{
				printf("%s is of type : %d\n", token->arg, token->type);
				token = token->next;
			}
			token = head;
			// f = NULL;
			// t_list *current = f;			
			// while (current != NULL)
			// {
			// 	if (current->ptr != NULL)
			// 		printf("%s\n", (char *)current->ptr);
			// 	current = current->next;
			// }
			//str = ft_split(rl);
			//int i = 0;
			//while (str[i])
			//{
			//	printf("%s\n",str[i]);
			//	i++;
			//}
			// Step 1: Tokenization
			// tokens = tokenize(rl);
			// if (!tokens)
			// 	allocation_fails();

			// // Step 2: Syntax Checking
			// if (check_syntax_error(tokens))
			// 	allocation_fails();
				
			// // Step 3: Expand Variables (Replacing $VAR with it's value and handling $?)
			// expand_variables(token);
			// // Step 4: Handle Quotes (Double "" and single ')
			// handle_quotes(tokens);

			// // Step 5: Convert Tokens to Commands
			// cmds = parse_tokens(tokens);
			
			// // Step 6: Execute Commands
			// execute_commands(cmds, pg);
		}
		free(rl);
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mp	pg;

	g_gbc = ft_lstnew_custom(NULL);
	check_args(ac, av);
	pg.envp = init_env(env);
	print_banner();
	signal_setup();
	shell_loop();
	print_exit();
	ft_lstclear(&g_gbc, free);
}
