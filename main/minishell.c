/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/17 13:26:38 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  need to inisialize this garbage collector and first use ft_lstnew to get the first node
    use this to add another adresse 					ft_lstadd_back(&g_gbc, *ft_lstnew(ptr))
	to free all the memory thats allocated use this 	ft_lstclear(t_list &gbc, free)
    */

void    shell_loop(char **env)
{
    char    *rl;

    (void)env;
    while (1)
    {
        rl = readline("Minishell> ");
        if (!rl)
            return ;
        ft_lstadd_back(&g_gbc, ft_lstnew(rl));
        if (rl)
            add_history(rl);
        
        //parsing and excution;
        
    }
}

int	main(int ac, char **av, char **env)
{
	t_mp	*pg;

	g_gbc = NULL;
	pg = NULL;
	check_args(ac, av);
	pg->envp = init_env(env);
	signal_setup();
    shell_loop(pg->envp);
	ft_lstclear(&g_gbc, free);
}
