/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:13:41 by ybenchel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/05 14:48:38 by abenzaho         ###   ########.fr       */
=======
/*   Updated: 2025/05/03 15:22:03 by ybenchel         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_err(t_mp *pg)
{
	perror("pipe error");
	pg->exit_status = 22;
}

void	expand_heredoc(char *s, t_mp *pg, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1])
				|| s[i + 1] == '_' || s[i + 1] == '?'))
			s = expand(s, &i, pg);
		else
			i++;
	}
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	read_heredoc(t_file *file, t_mp *pg)
{
	char *line;
	char *delimiter;
	int fds[2];
	delimiter = file->file;
	if (pipe(fds) == -1)
	{
		pipe_err(pg);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expand_heredoc(line, pg, fds[1]);
		free(line);
	}
	close(fds[1]);
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
