/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_remove_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:38:28 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/07 12:57:36 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(t_cmds *cmds)
{
	int	i;

	while(cmds)
	{
		i = 0;
		while(cmds->ar)
		{
			i++;
		}
		cmds = cmds->next;
	}
}