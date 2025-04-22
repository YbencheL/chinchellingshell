/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_n_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:25:04 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/22 17:57:59 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	in_n_out_backup(int *stdin_b, int *stdout_b)
{
	*stdin_b = dup(STDIN_FILENO);
	*stdout_b = dup(STDOUT_FILENO);
}

int	check_redirection(t_token *tokens)
{
	int fd;
	
	if (ft_strcmp(tokens->cmds[0], ">") == 0)
		fd = open(tokens->cmds[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(tokens->cmds[0], ">>") == 0)
		fd = open(tokens->cmds[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(tokens->cmds[0], "<") == 0)
		fd = open(tokens->cmds[1], O_RDONLY);
	else
		return (EXIT_FAILURE);
	if (fd == -1)
	{
		perror(tokens->cmds[1]);
		return (EXIT_FAILURE);
	}
	return (fd);	
}

void	check_herdoc(t_file *files)
{
    char    *line;
    int     fds[2];
    t_file  *current;
    int     found_heredoc;

    found_heredoc = 0;
    if (pipe(fds) == -1)
    {
        perror("pipe error\n");
        return ;
    }
    current = files;
    while (current)
    {
        if (current->type == HEREDOC)
        {
            found_heredoc = 1;
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
        }
        current = current->next;
    }
    
    if (found_heredoc)
    {
        close(fds[1]);
        dup_in(fds[0]);
    }
    else
    {
        close(fds[0]);
        close(fds[1]);
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
