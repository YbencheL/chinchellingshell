/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_check_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:33:11 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:18:58 by abenzaho         ###   ########.fr       */
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
