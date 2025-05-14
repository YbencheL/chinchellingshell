/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_shlvl_pwdreset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:22:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/14 13:29:18 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_shvl(t_mp *pg)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	int		count;
	char	*shlvl;

	if (getcwd(cwd, sizeof(cwd)))
	{
		tmp = ft_strjoin("PWD=", cwd);
		add_var(&pg->env, tmp);
	}
	shlvl = my_getenv(pg->env, "SHLVL");
	if (!shlvl)
		tmp = ft_strdup("SHLVL=0");
	else
	{
		count = ft_atoi(shlvl);
		tmp = ft_strjoin("SHLVL=", ft_itoa(count + 1));
	}
	add_var(&pg->env, tmp);
	update_env(pg);
}
