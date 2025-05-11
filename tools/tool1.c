/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:03 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/11 11:33:41 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_env(char **envp)
{
	int		i;
	t_list	*env;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (!env)
			env = ft_lstnew(envp[i]);
		else
			ft_lstadd_back(&env, ft_lstnew(envp[i]));
		i++;
	}
	return (env);
}

void	allocation_fails(void)
{
	ft_lstclear(&g_gbc, free);
	exit(1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_setup(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
