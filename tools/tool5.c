/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/10 16:12:39 by abenzaho         ###   ########.fr       */
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

void	close_files(t_file *files)
{
	while (files)
	{
		if (files->fd > 0)
			close(files->fd);
		files = files->next;
	}
}

void	dup_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 in");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	dup_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 out");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
