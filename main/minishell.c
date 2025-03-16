/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/16 19:45:28 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*g_gbc;
/*  need to inisialize this garbage collector and first use ft_lstnew to get the first node
    use this to add another adresse 					ft_lstadd_back(&gbc, *ft_lstnew(ptr))
	to free all the memory thats allocated use this 	ft_lstclear(t_list &gbc, free)
    */

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_lstadd_back(&g_gbc, ft_lstnew(env));
	env->envp = envp;
	return (env);
}

int	main(int ac, char **av, char **env)
{
	t_env	*e_env;

	(void)av;
	e_env = init_env(env);
	check_args(ac);
	ft_lstclear(&g_gbc, free);
	g_gbc = NULL;
}
