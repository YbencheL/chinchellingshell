/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:13:41 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/15 10:42:09 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_qouted_delimter(char *str)
{
	int		i;
	int		c;
	char	*s;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			c = 1;
		i++;
	}
	if (c == 1)
	{
		s = quote_remover(str);
		return (s);
	}
	else
		return (str);
}

int	handle_heredoc_child(int fd, char *delimiter, char *original, t_mp *pg)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (!ft_strcmp(delimiter, original))
			line = expand_heredoc(line, pg);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	return (0);
}

int	read_heredoc(t_file *file, t_mp *pg)
{
	char	*delimiter;
	int		fds[2];
	int		pid;
	int		status;

	delimiter = check_qouted_delimter(file->file);
	if (pipe(fds) == -1)
		return (pipe_err(pg), 1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		handle_heredoc_child(fds[1], delimiter, file->file, pg);
		exit(0);
	}
	close(fds[1]);
	waitpid(pid, &status, 0);
	signal_setup();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(fds[0]), pg->exit_status = 130, write(1, "\n", 1), 1);
	file->fd = fds[0];
	return (0);
}

int	fill_herdoc(t_cmds *cmds, t_mp *pg)
{
	t_file	*tmp;

	while (cmds)
	{
		tmp = cmds->files;
		while (tmp)
		{
			if (tmp->type == HEREDOC)
			{
				if (read_heredoc(tmp, pg))
					return (1);
			}
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
