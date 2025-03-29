/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/29 18:02:27 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *g_gbc;
/*  need to inisialize this garbage collector and first use ft_lstnew to get the first node
    use this to add another adresse 					ft_lstadd_back(&g_gbc, *ft_lstnew(ptr))
	to free all the memory thats allocated use this 	ft_lstclear(t_list &gbc, free)
    */

void shell_loop(t_mp *pg)
{
	char    *rl;
	/*t_token *tokens;
	t_cmd   *cmds;*/
	t_list	*f;
	t_arg	*token;
	t_arg	*head;
	//char	**str;

	while (1)
	{
		rl = readline("Minishell$ ");
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
			expand_variables(token, pg);
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
				
			// // Step 3: Expand Variables (Replacing $VAR with it's value and handling $?)
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
