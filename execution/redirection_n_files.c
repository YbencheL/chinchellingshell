/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_n_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:25:04 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/20 14:12:12 by ybenchel         ###   ########.fr       */
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
	
	if (ft_strcmp(tokens->cmd[0] == ">") == 0)
		fd = open(tokens->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(tokens->cmd[0] == ">>") == 0)
		fd = open(tokens->cmd[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(tokens->cmd[0] == "<") == 0)
		fd = open(tokens->cmd[1], O_RDONLY);
	else
		return (EXIT_FAILURE);
	if (fd == -1)
	{
		perror(tokens->cmd[1]);
		return (EXIT_FAILURE);
	}
	return (fd);	
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
