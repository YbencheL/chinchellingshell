/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:53 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/10 13:47:14 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_var(t_list **env, char *s)
{
	t_list	*prv;
	t_list	*first; 
	int		len;
	
	prv = NULL;
	first = *env;
	len = ft_strlen(s);
	while (*env)
	{
		if (strncmp((char *)(*env)->ptr, s, len) == 0 && ((char *)(*env)->ptr)[len] == '=')
		{
			if (!prv)
				first = (*env)->next;
			else
				prv->next = (*env)->next;
			break ;
		}
		prv = *env;
		*env = (*env)->next;
	}
	*env = first;
}

void	unset(t_cmds *cmds, t_list *env, t_mp *pg)
{
	int	i;

	i = 1;
	while (cmds->cmds[i])
	{
		remove_var(&env, cmds->cmds[i]);
		i++;
	}
	pg->exit_status = 0;
}
