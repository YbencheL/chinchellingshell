/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:25 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 18:57:48 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_cmds *cmds, t_list *env)
{
	if (cmds->cmds[1])
	{
		write(2, "minishell : env : does not take any arguments", 45);
		return (1);
	}
	while(env)
	{
		printf("%s\n", (char *)(env->ptr));
		env = env->next;
	}
	return (0);
}
