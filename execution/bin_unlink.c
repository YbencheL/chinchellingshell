/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:53 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/29 17:34:11 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bin_unlink(t_cmds *cmds)
{
	char 	*path_name;
	int		status;

	if (!cmds->cmds[1])
    {
        write(2, "minishell: unlink: missing operand\n", 35);
        return ;
    }
	path_name = cmds->cmds[1];
	status = unlink(path_name);
	if (status == -1)
	{
    	perror("minishell: unlink");
    	return ;
	}
}