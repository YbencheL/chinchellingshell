/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:13:41 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/05 14:48:38 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_heredoc(t_file *file, t_mp *pg)
{
	char *line;
	char *delimiter;
	int fds[2];
	
	delimiter = file->file;
	if (pipe(fds) == -1)
	{
		perror("pipe error");
		pg->exit_status = 22;
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
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
	file->fd = fds[0];
	return (0);
}

int	fill_herdoc(t_cmds *cmds, t_mp *pg)
{
    t_cmds *current_cmd = cmds;
    t_file *current_file;
    
    while (current_cmd)
    {
        current_file = current_cmd->files;
        while (current_file)
        {
            if (current_file->type == HEREDOC)
            {
                if (read_heredoc(current_file, pg))
                    return (1);
            }
            current_file = current_file->next;
        }
        current_cmd = current_cmd->next;
    }
    return (0);
}
