/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_to_cmds1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/13 18:25:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redirection(t_token *token, t_arg *current, t_arg **curr_ptr)
{
	if (current->next && current->next->type == WORD)
	{
		append_redirection(&token->redi, current->type, current->next->arg);
		*curr_ptr = current->next;
	}
}

t_token	*initialize_token_node(void)
{
	t_token	*node;

	node = ft_malloc(sizeof(t_token));
	node->cmds = NULL;
	node->redi = NULL;
	node->heredoc = 0;
	node->type = CMD;
	node->next = NULL;
	return (node);
}

void	new_pipeline(t_token *node)
{
	node->type = PIPELINE;
	node->next = initialize_token_node();
}

t_token	*tokens_to_cmds(t_arg *tokens)
{
	t_token	*node;
	t_token	*first;
	t_arg	*current;

	node = initialize_token_node();
	first = node;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == WORD)
			append_command(&node->cmds, current->arg);
		else if (current->type == RED_IN || current->type == RED_OUT
			|| current->type == RED_APPEND)
			handle_redirection(node, current, &current);
		else if (current->type == HEREDOC)
			node->heredoc = 1;
		else if (current->type == PIPE)
		{
			new_pipeline(node);
			node = node->next;
		}
		current = current->next;
	}
	return (first);
}
