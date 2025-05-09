/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:19:30 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/09 11:50:20 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_env_updated(t_mp *pg)
{
	int		i;
	t_list	*tmp;

	i = 0;
	// int	j=0;
	// while (pg->envp[j])
	// {
	// 	printf("%s---------\n", pg->envp[j]);
	// 	j++;
	// }
	tmp = pg->env;
	while (tmp && tmp->ptr && pg->envp[i])
	{
		if (ft_strcmp(tmp->ptr, pg->envp[i]))
			return (1);
		tmp = tmp->next;
		i++;
	}
	if (ft_pcounter(pg->envp) != ft_lstsize(pg->env))
		return (1);
	return (0);
}

void	update_env(t_mp *pg)
{
	int		size;
	t_list	*tmp;
	int		i;
	char	**new_env;

	i = 0;
	if (!check_if_env_updated(pg))
		return ;
	size = ft_lstsize(pg->env) + 1;
	new_env = (char **)ft_malloc(sizeof(char *) * size);
	tmp = pg->env;
	while(tmp)
	{
		new_env[i] = ft_strdup(tmp->ptr);
		tmp = tmp->next;
		i++;
	}
	new_env[i] = NULL;
	pg->envp = new_env;
}
