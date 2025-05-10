/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:25 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 13:32:12 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_cmds *cmds, t_list *env, t_mp *pg)
{
	if (cmds->cmds[1])
	{
		write(2, "minishell : env : does not take any arguments", 45);
		pg->exit_status = 1;
		return (1);
	}
	while(env)
	{
		printf("%s\n", (char *)(env->ptr));
		env = env->next;
	}
	pg->exit_status = 0;
	return (0);
}
