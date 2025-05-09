/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:03:07 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/09 14:17:28 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtins(t_cmds *cmds, t_mp *pg)
{
	int	exit_s;
	
	if (!cmds->cmds || !cmds->cmds[0])
		return 1;
    else if (!ft_strcmp(cmds->cmds[0], "cd"))
        return (cd(cmds, pg), 0);
    else if (!ft_strcmp(cmds->cmds[0], "export"))
	{
        exit_s = export(cmds, pg->env);
		pg->exit_status = exit_s;
		return 0;
	}
    else if (!ft_strcmp(cmds->cmds[0], "env"))
        return (env(cmds, pg->env), 0);
    else if (!ft_strcmp(cmds->cmds[0], "pwd"))
        return (pwd(), 0);
	else if (!ft_strcmp(cmds->cmds[0], "echo"))
        return (echo(cmds, pg), 0);
    else if (!ft_strcmp(cmds->cmds[0], "unset"))
        return (unset(cmds, pg->env), 0);
	else if (!ft_strcmp(cmds->cmds[0], "exit"))
        return (bin_exit(cmds, pg), 0);
    else
		return 1;
}
