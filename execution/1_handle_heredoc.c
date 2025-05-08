/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:13:41 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/08 16:43:19 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	pipe_err(t_mp *pg)
{
	perror("pipe error");
	pg->exit_status = 141;
}

char	*expand_heredoc(char *s, t_mp *pg)
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
	return (s);
}

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
	if(c == 1)
	{
		s = quote_remover(str);
		return (s);
	}
	else
		return (str);
}

int	read_heredoc(t_file *file, t_mp *pg)
{
	char	*line;
	char	*delimiter;
	int		fds[2];

	delimiter = check_qouted_delimter(file->file);
	if (pipe(fds) == -1)
		return (pipe_err(pg), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (!ft_strcmp(delimiter, file->file))
			line = expand_heredoc(line, pg);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	free(line);
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
