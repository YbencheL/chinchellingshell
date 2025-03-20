/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/20 16:25:28 by abenzaho         ###   ########.fr       */
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
	//t_list *f;
	//char	**str;
	
	(void)pg;
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
			split_phrase(rl);
			//current = f;
			// if(f)
			// {			
			// 	while (current != NULL)
			// 	{
			// 		if (current->ptr != NULL)
			// 			printf("%s\n", (char *)current->ptr);
			// 		current = current->next;
			// 	}
			// }
			//str = ft_split(rl);
			//int i = 0;
			//while (str[i])
			//{
			//	printf("%s\n",str[i]);
			//	i++;
			//}
			/*// Step 1: Tokenization
			tokens = tokenize(rl);
			if (!tokens)
				allocation_fails();

			// Step 2: Syntax Checking
			if (check_syntax_error(tokens))
				allocation_fails();
				
			// Step 3: Expand Variables (Replacing $VAR with it's value and handling $?)
			expand_variables(tokens, pg->env);

			// Step 4: Handle Quotes (Double "" and single ')
			handle_quotes(tokens);

			// Step 5: Convert Tokens to Commands
			cmds = parse_tokens(tokens);
			
			// Step 6: Execute Commands
			execute_commands(cmds, pg);*/
		}
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mp	pg;

	g_gbc = NULL;
	check_args(ac, av);
	pg.envp = init_env(env);
	print_banner();
	signal_setup();
	shell_loop(&pg);
	print_exit();
	ft_lstclear(&g_gbc, free);
}
