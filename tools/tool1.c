/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:32:03 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/17 13:25:37 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_env(char **envp)
{
	char	**env;
	int		i;

	env = (char **)malloc(sizeof(char *) * (ft_pcounter(envp) + 1));
	if (!env)
		allocation_fails();
	ft_lstadd_back(&g_gbc, ft_lstnew(env));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i])
			allocation_fails();
		ft_lstadd_back(&g_gbc, ft_lstnew(env));
		i++;
	}
	env[i] = NULL;
	return (env);
}
void	allocation_fails(void)
{
	ft_putstr_fd("Error : Allocation fails 😞\n", 2);
	ft_lstclear(&g_gbc, free);
	exit(1);
}

void    sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    signal_setup(void)
{
    struct sigaction    sa;

    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    rl_catch_signals = 0;
}



