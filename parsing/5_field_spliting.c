/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_field_spliting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:44:52 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 15:54:35 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_space(t_arg *token)
{
	int	i;

	i = 0;
	if (!token->arg)
		return (0);
	while (token->arg[i])
	{
		if (token->arg[i] == '\'' || token->arg[i] == '"')
		{
			skip_quotes(token->arg, &i, token->arg[i]);
			i++;
		}
		else if (token->arg[i] == ' ' || token->arg[i] == '\t')
			return (1);
		else
			i++;
	}
	return (0);
}

void	add_splited_tokens(int i, t_arg **new_list, char **str)
{
	while (str[i])
	{
		(*new_list)->next = new_arg(str[i]);
		*new_list = (*new_list)->next;
		(*new_list)->type = WORD;
		i++;
	}
}

void	split_word_var(t_arg **current, t_arg **previous, t_arg **new_head)
{
	char	**str;
	int		i;
	t_arg	*new_list;
	t_arg	*head;

	str = split_token_field((*current)->arg);
	new_list = new_arg(str[0]);
	new_list->type = WORD;
	head = new_list;
	if (!(*new_head))
		*new_head = head;
	i = 1;
	add_splited_tokens(i, &new_list, str);
	if (!(*previous))
		*previous = new_list;
	else
		(*previous)->next = head;
	new_list->next = (*current)->next;
	*current = new_list;
	*previous = new_list;
}

void	export_skip(t_arg **token, t_arg **new_head)
{
	if (!(*new_head))
		*new_head = *token;
	if (!ft_strcmp("export", (*token)->arg))
		hundle_export_field(*token);
	else
		*token = (*token)->next;
}

void	handle_var_space(t_arg **token)
{
	t_arg	*current;
	t_arg	*previous;
	t_arg	*new_head;

	current = *token;
	previous = NULL;
	new_head = NULL;
	while (current)
	{
		if (!current->arg)
		{
		}
		else if ((current->type >= 2 && current->type <= 5)
			|| !ft_strcmp("export", current->arg))
			export_skip(&current, &new_head);
		else if (current->type == WORD && check_for_space(current))
			split_word_var(&current, &previous, &new_head);
		else if (!new_head)
			new_head = current;
		previous = current;
		current = current->next;
	}
	if (new_head)
		*token = new_head;
}
