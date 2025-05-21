/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:50:50 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 16:25:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_error(char *s, t_mp *pg, int exit)
{
	pg->exit_status = exit;
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": write error: No space left on device\n", 39);
}

void	echo(t_cmds *cmds, t_mp *pg)
{
	int	i;
	int	nl;
	int	e;

	i = 1;
	nl = 1;
	while (cmds->cmds[i] && !ft_strcmp(cmds->cmds[i], "-n"))
	{
		nl = 0;
		i++;
	}
	while (cmds->cmds[i])
	{
		e = write(1, cmds->cmds[i], ft_strlen(cmds->cmds[i]));
		if (cmds->cmds[i + 1])
			e = write(1, " ", 1);
		i++;
	}
	if (nl)
		e = write(1, "\n", 1);
	if (e == -1)
		write_error("echo", pg, 1);
	else
		pg->exit_status = 0;
}
