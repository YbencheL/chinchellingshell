/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:47 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 14:22:33 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *cmd, char *path, t_mp *pg)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_split(path, ":");
	while (paths[i])
	{
		tmp = ft_strjoin("/", cmd);
		tmp = ft_strjoin(paths[i], tmp);
		if (!access(tmp, F_OK | X_OK))
			return (tmp);
		i++;
	}
	pg->exit_status = 126 ;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (NULL);
}

char	*get_cmd_dir(char *cmd, t_mp *pg)
{
	char	*cmd_dir;
	char	*path;
	struct stat st;
	
	if(ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Is a directory\n", 17);
			pg->exit_status = 126;
			return (NULL);
		}
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) != 0)
			{
				write(2, "minishell: ", 11);
				write(2, cmd, ft_strlen(cmd));
				write(2, ": Permission denied\n", 19);
				pg->exit_status = 126;
				return (NULL);
			}
			else
				return (cmd);
		}
		else
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": No such file or directory\n", 28);
			pg->exit_status = 127;
			return (NULL);
		}
	}
	path = my_getenv(pg->env, "PATH");
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		pg->exit_status = 127;
		return (NULL);
	}
	cmd_dir = get_path(cmd, path, pg);
	return (cmd_dir);
}
