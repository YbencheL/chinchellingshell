/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_n_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:25:04 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/22 19:45:32 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	in_n_out_backup(int *stdin_b, int *stdout_b)
{
	*stdin_b = dup(STDIN_FILENO);
	*stdout_b = dup(STDOUT_FILENO);
}

int	check_redirection(t_file *files)
{
    int fd;
    
	fd = 0;
    if (files->type == RED_OUT)
        fd = open(files->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (files->type == RED_APPEND)
        fd = open(files->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (files->type == RED_IN)
        fd = open(files->file, O_RDONLY);
    else if (files->type == HEREDOC)
        fd = files->fd;
    if (fd == -1)
    {
        perror(files->file);
        return (EXIT_FAILURE);
    }
    if (files->type == RED_IN || files->type == HEREDOC)
        dup_in(fd);
    else 
        dup_out(fd);
    return (EXIT_SUCCESS);	
}

void	check_herdoc(t_file *files)
{
    char    *line;
    t_file  *current;
	int 	fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe error");
		return;
	}
    current = files;
    while (current)
    {
        if (current->type == HEREDOC)
        {
            current->fd = fds[0];
            line = readline("> ");
            while (line && ft_strcmp(line, current->file) != 0)
            {
                write(fds[1], line, ft_strlen(line));
                write(fds[1], "\n", 1);
                free(line);
                line = readline("> ");
            }
            if (line)
                free(line);
            close(fds[1]);
        }
        current = current->next;
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
