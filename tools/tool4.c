/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:25:20 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/22 15:51:37 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (RED_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (RED_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (RED_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else
		return (WORD);
}

void	typeof_token(t_arg *arg)
{
	t_arg	*head;

	head = arg;
	while (head)
	{
		head->type = token_type(head->arg);
		head = head->next;
	}
}

t_arg	*new_arg(char *arg)
{
	t_arg	*new;

	new = (t_arg *)ft_malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->arg = arg;
	new->next = NULL;
	return (new);
}

void	argadd_back(t_arg **arg, t_arg *new)
{
	t_arg	*temp;

	if (!arg || !new)
		return ;
	if (!*arg)
	{
		*arg = new;
		return ;
	}
	temp = *arg;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_arg	*ft_arglast(t_arg *lst)
{
	t_arg	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}