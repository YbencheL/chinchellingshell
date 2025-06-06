/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_check_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:33:11 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/13 13:06:05 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quotes(s, &i, s[i]);
			i++;
		}
		else if (s[i] == ' ' || s[i] == '\t')
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_files(t_cmds *cmds, t_mp *pg)
{
	t_file	*tmp;

	while (cmds)
	{
		tmp = cmds->files;
		while (tmp)
		{
			if (tmp->type >= 2 && tmp->type <= 4)
			{
				if (check_file(tmp->file))
				{
					write(2, "minishell : $x: ambiguous redirect\n", 35);
					pg->exit_status = 1;
					return (1);
				}
				else
					tmp->file = quote_remover(tmp->file);
			}
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

void	quote_back(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == DQUOTE)
			s[i] = '"';
		else if (s[i] == SQUOTE)
			s[i] = '\'';
		i++;
	}
}

void	getback_quotes(t_cmds *cmd)
{
	t_file	*tmp;
	int		i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->cmds[i])
		{
			quote_back(cmd->cmds[i]);
			i++;
		}
		tmp = cmd->files;
		while (tmp)
		{
			quote_back(tmp->file);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}
