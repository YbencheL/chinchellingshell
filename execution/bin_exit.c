/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:06:15 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/08 13:13:06 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exit_error(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if(s[j] == '+' || s[j] == '-')
	{
		j++;
		if (s[j] == '-' || s[j] == '+')
		{
			write (2, "bash: exit : numeric argument required\n", 39);
			return (2);
		}
	}
	while (s[j])
	{
		if (s[j] > '9' || s[j] < '0')
		{
			write(2, "bash: exit : numeric argument required\n", 39);
			return (2);
		}
		j++;
	}
	return (i);	
}

void	bin_exit(t_cmds *cmds, t_mp *pg)
{
	int	i;

	i = 0;
	if (cmds->cmds[1] && cmds->cmds[2])
	{
		write(2, "minishell: exit: too many arguments\n", 35);
		exit(1);
	}
	else if (cmds->cmds[1])
	{
		i = check_exit_error(cmds->cmds[1]);
		if (i != 2)
		{
			i = ft_atoi(cmds->cmds[1]);
			i = i % 256;
		}
	}
	close_files(cmds->files);
	restor_fd(pg->std_in, pg->std_out);
	ft_lstclear(&g_gbc, free);
	if (!pg->is_child)
		write(1, "exit\n", 5);
	exit (i);
}
