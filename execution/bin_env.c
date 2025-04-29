/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:25 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 17:41:41 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_list *env)
{
	while(env)
	{
		printf("%s\n", (char *)(env->ptr));
		env = env->next;
	}
}

void	env(t_cmds *cmds, t_list *env)
{
	if (!cmds->cmds[1])
		print_env(env);
	// else
	// {
	// // need to excute cmd after this	
	// }
}
