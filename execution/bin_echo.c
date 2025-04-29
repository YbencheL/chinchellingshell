/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:50:50 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 15:04:16 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(t_cmds *cmds)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (cmds-cmds[i] && !ft_strcmp(cmds->cmds[i], "-n"))
	{
		nl = 0;
		i++;
	}
	while (cmds->cmds[i])
	{
		printf("%s", cmds->cmds[i]);
		if (cmds->cmds[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	exit (0);
}
