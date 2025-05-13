/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_handling_null.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:19:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/13 13:06:30 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_first(t_arg **token)
{
	t_arg	*tmp;

	tmp = *token;
	while (tmp && !tmp->arg)
		tmp = tmp->next;
	*token = tmp;
}

void	skip_null(t_arg **token)
{
	t_arg	*curr;
	t_arg	*prv;

	skip_first(token);
	curr = *token;
	while (curr)
	{
		if (!curr->arg)
		{
			prv->next = curr->next;
			curr = curr->next;
		}
		else
		{
			prv = curr;
			curr = curr->next;
		}
	}
}
