/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:47 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/05 18:30:13 by abenzaho         ###   ########.fr       */
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
			return (tmp);// handle /ls should not work
		i++;
	}
	// print the error
	pg->exit_status = 22 ;// check what exit error we return; 
	return (NULL);
}

char	*get_cmd_dir(char *cmd, t_mp *pg)
{
	char	*cmd_dir;
	char	*path;
	
	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	path = my_getenv(pg->env, "PATH");
	//if (!path) handle if the path is inset it shoud display command not found
	cmd_dir = get_path(cmd, path, pg);
	return (cmd_dir);
}
