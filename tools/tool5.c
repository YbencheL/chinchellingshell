/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/03 15:24:13 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_getenv(t_list *env, char *name)
{
	int		len;

	len = ft_strlen(name);
	while (env)
	{
		if (!strncmp(name, ((char *)(env->ptr)), len)
			&& ((char *)(env->ptr))[len] == '=')
			return (ft_strdup(((char *)(env->ptr)) + len + 1));
		env = env->next;
	}
	return (NULL);
}
