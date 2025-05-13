/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:47 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/13 14:11:26 by ybenchel         ###   ########.fr       */
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
	pg->exit_status = 127;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (NULL);
}

static void	print_cmd_error(char *cmd, char *error_msg, int exit_code, t_mp *pg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, error_msg, ft_strlen(error_msg));
	pg->exit_status = exit_code;
}

static char	*handle_direct_path(char *cmd, t_mp *pg)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_cmd_error(cmd, ": Is a directory\n", 126, pg);
		return (NULL);
	}
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) != 0)
		{
			print_cmd_error(cmd, ": Permission denied\n", 126, pg);
			return (NULL);
		}
		return (cmd);
	}
	print_cmd_error(cmd, ": No such file or directory\n", 127, pg);
	return (NULL);
}

char	*get_cmd_dir(char *cmd, t_mp *pg)
{
	char	*path;
	char	*cmd_dir;

	if (ft_strchr(cmd, '/'))
		return (handle_direct_path(cmd, pg));
	path = my_getenv(pg->env, "PATH");
	if (!path)
	{
		print_cmd_error(cmd, ": command not found\n", 127, pg);
		return (NULL);
	}
	cmd_dir = get_path(cmd, path, pg);
	return (cmd_dir);
}
