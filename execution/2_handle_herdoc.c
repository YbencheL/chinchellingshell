/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:26:56 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/15 10:27:19 by ybenchel         ###   ########.fr       */
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
