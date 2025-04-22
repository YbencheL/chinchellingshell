/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:48:26 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/21 15:16:41 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *cmd)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ":");
	while (paths[i])
	{
		tmp = ft_strjoin("/", cmd);
		tmp = ft_strjoin(paths[i], tmp);
		if (!access(tmp, F_OK | X_OK));
			return (ft_str_dup(path[i]));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_token *tokens)
{
		
	if (!access(tokens->cmds[0], F_OK | X_OK))
		return (tokens->cmds[0]);
	
}