/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_n_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:25:04 by ybenchel          #+#             */
/*   Updated: 2025/04/23 12:56:24 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restor_fd(int stdin_b, int stdout_b)
{
	dup2(stdin_b, STDIN_FILENO);
	dup2(stdout_b, STDOUT_FILENO);
}

void	in_n_out_backup(t_mp *pg)
{
	pg->std_in = dup(STDIN_FILENO);
	pg->std_out = dup(STDOUT_FILENO);
}

int	check_redirection(t_file *files)
{
	int	fd;

	fd = 0;
	if (files->type == RED_OUT)
		fd = open(files->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (files->type == RED_APPEND)
		fd = open(files->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (files->type == RED_IN)
		fd = open(files->file, O_RDONLY);
	else if (files->type == HEREDOC)
		fd = dup(files->fd);
	if (fd == -1)
	{
		perror(files->file);
		return (1);
	}
	files->fd = fd;
	if (files->type == RED_IN || files->type == HEREDOC)
		dup_in(fd);
	else
		dup_out(fd);
	return (0);
}

int	open_files_red(t_file *files)
{
	while (files)
	{
		if (check_redirection(files))
			return (1);
		files = files->next;
	}
	return (0);
}
