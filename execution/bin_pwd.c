/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:00:26 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/15 16:54:31 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_mp *pg)
{
	char	*path;
	int		e;

	path = my_getenv(pg->env, "PWD");
	if (path == NULL)
	{
		perror("getcwd error");
		pg->exit_status = 1;
		return ;
	}
	e = write(1, path, ft_strlen(path));
	e = write(1, "\n", 1);
	if (e == -1)
		write_error("pwd", pg, 1);
	else
		pg->exit_status = 0;
}

void	update_pwd(t_list *env)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	pwd = ft_strjoin("PWD=", cwd);
	while (env)
	{
		if (!ft_strncmp(env->ptr, "PWD=", 4))
		{
			env->ptr = pwd;
			return ;
		}
		env = env->next;
	}
}
