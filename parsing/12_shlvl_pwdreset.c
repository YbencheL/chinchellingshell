/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_shlvl_pwdreset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:22:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/13 13:07:04 by ybenchel         ###   ########.fr       */
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
	shlvl = getenv("SHLVL");
	count = ft_atoi(shlvl);
	tmp = ft_strjoin("SHLVL=", ft_itoa(count + 1));
	add_var(&pg->env, tmp);
	update_env(pg);
}
