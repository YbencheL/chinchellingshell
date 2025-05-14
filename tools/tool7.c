/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:48:42 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/14 14:19:01 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env_to_sort(char **str)
{
	int		i;
	char	**s;

	i = 0;
	s = (char **)ft_malloc(sizeof(char *) * (ft_pcounter(str) + 1));
	while (str[i])
	{
		s[i] = ft_strdup(str[i]);
		i++;
	}
	s[i] = NULL;
	return (str);
}

char	**sort_env(char **env)
{
	int		i;
	char	*tmp;
	char	**envs;

	i = 0;
	if (!env)
		return (NULL);
	envs = copy_env_to_sort(env);
	while (envs[i] && envs[i + 1])
	{
		if (ft_strcmp(envs[i], envs[i + 1]) > 0)
		{
			tmp = envs[i];
			envs[i] = envs[i + 1];
			envs[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (envs);
}
