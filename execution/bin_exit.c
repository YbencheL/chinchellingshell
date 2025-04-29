/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:06:15 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 15:04:17 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit(t_cmds *cmds, int pid)
{
	if (cmds->cmds[1])
		write(2, "minishell: exit: too many arguments\n", 35);
	if (!pid)
	{
		ft_lstclear(g_gbc, free);
		printf("exit\n");
	}
	else
		exit (0);
}
