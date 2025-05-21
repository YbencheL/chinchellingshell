/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:24:08 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 17:01:56 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_success(t_cmds *cmds, t_mp *pg)
{
	update_pwd(pg->env);
	cmds->cmds[1] = NULL;
	pg->exit_status = 0;
}

int	check_file_name_len(char *s)
{
	int	i;
	int	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
		{
			i++;
			c = 0;
			while (s[i] && s[i] != '/')
			{
				c++;
				i++;
			}
			if (c > 255)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

void	cd_oldpwd(t_mp *pg)
{
	char	*last_path;
	int		e;

	last_path = my_getenv(pg->env, "OLDPWD");
	if (!last_path)
		cd_error(pg, "OLDPWD not set", 1);
	else
	{
		e = write(1, last_path, ft_strlen(last_path));
		e = write(1, "\n", 1);
		chdir(last_path);
		update_pwd(pg->env);
		if (e == -1)
			write_error("cd", pg, 1);
		else
			pg->exit_status = 0;
	}
}

void	cd_home(t_mp *pg)
{
	char	*path;

	path = my_getenv(pg->env, "HOME");
	if (!path)
		cd_error(pg, "HOME not set", 1);
	else
	{
		chdir(path);
		update_pwd(pg->env);
		pg->exit_status = 0;
	}
}

void	cd(t_cmds *cmds, t_mp *pg)
{
	if (!cmds->cmds[1])
		return (cd_home(pg));
	if (cmds->cmds[2])
		return (cd_error(pg, "too many arguments", 1));
	if (ft_strncmp(cmds->cmds[1], "-", ft_strlen(cmds->cmds[1])) == 0)
		return (cd_oldpwd(pg));
	if (ft_strlen(cmds->cmds[1]) > 4094)
		return (cd_error(pg, "Pathname too long", 1));
	if (check_file_name_len(cmds->cmds[1]))
		return (cd_error(pg, "File name too long", 1));
	if (!chdir(cmds->cmds[1]))
		return (cd_success(cmds, pg));
	perror("minishell cd : ");
	pg->exit_status = 1;
}
