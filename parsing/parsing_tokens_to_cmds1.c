/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_to_cmds1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/15 21:45:39 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *initialize_token_node(void)
{
	t_token *node;

	node = ft_malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->cmds = ft_malloc(sizeof(char*) * 2);
	node->cmds[0] = NULL;
	node->cmds[1] = NULL;
	node->type = CMD;
	node->heredoc = 0;
	node->next = NULL;
	return (node);
}

int	count_commands(t_arg *tokens)
{
	int		count;
	t_arg	*curr;

	count = 1;
	curr = tokens;
	if (!tokens)
		return (0);
	while (curr)
	{
		if (curr->type == PIPE)
			count += 2;
		else if ((curr->type == RED_IN || curr->type == RED_OUT ||
			curr->type == RED_APPEND || curr->type == HEREDOC) &&
			curr->next && curr->next->type == WORD)
			count += 2;
		curr = curr->next;
	}
	return (count);
}

void	process_word_token(t_token *current, t_arg **curr_token)
{
	char	*temp;

	if (!current->cmds)
		current->cmds = ft_malloc(sizeof(char*) * 2);
	if (current->cmds[0])
	{
		temp = current->cmds[0];
		current->cmds[0] = ft_strjoin(temp, " ");
		temp = current->cmds[0];
		current->cmds[0] = ft_strjoin(temp, (*curr_token)->arg);
	}
	else
	{
		current->cmds[0] = ft_strdup((*curr_token)->arg);
		current->cmds[1] = NULL;
	}
	*curr_token = (*curr_token)->next;
}

void	process_pipe_token(t_token **current, t_token ***cmd_list, 
						int *cmd_idx, t_arg **curr_token)
{
	(*current)->next = initialize_token_node();
	*current = (*current)->next;
	(*current)->cmds[0] = ft_strdup("|");
	(*current)->cmds[1] = NULL;
	(*current)->type = PIPELINE;
	if (*cmd_idx < count_commands(*curr_token))
		(*cmd_list)[(*cmd_idx)++] = *current;
	(*current)->next = initialize_token_node();
	*current = (*current)->next;
	if (*cmd_idx < count_commands(*curr_token))
		(*cmd_list)[(*cmd_idx)++] = *current;
	*curr_token = (*curr_token)->next;
}

void	setup_redirection(t_token *current, int type)
{
	current->type = REDIRECTION;
	if (type == RED_IN)
		current->cmds[0] = ft_strdup("<");
	else if (type == RED_OUT)
		current->cmds[0] = ft_strdup(">");
	else if (type == RED_APPEND)
		current->cmds[0] = ft_strdup(">>");
	current->cmds[1] = NULL;
}

void	process_redirection(t_token **current, t_token ***cmd_list, 
						int *cmd_idx, t_arg **curr_token)
{
	int	type;

	type = (*curr_token)->type;
	(*current)->next = initialize_token_node();
	*current = (*current)->next;
	setup_redirection(*current, type);
	if (*cmd_idx < count_commands(*curr_token))
		(*cmd_list)[(*cmd_idx)++] = *current;
	if ((*curr_token)->next && (*curr_token)->next->type == WORD)
	{
		(*current)->next = initialize_token_node();
		*current = (*current)->next;
		(*current)->type = FILE_ARG;
		(*current)->cmds[0] = ft_strdup((*curr_token)->next->arg);
		(*current)->cmds[1] = NULL;
		if (*cmd_idx < count_commands(*curr_token))
			(*cmd_list)[(*cmd_idx)++] = *current;
		*curr_token = (*curr_token)->next->next;
	}
	else
		*curr_token = (*curr_token)->next;
}

void process_token(t_token **current, t_token ***cmd_list, 
				  int *cmd_idx, t_arg **curr_token)
{
	if ((*curr_token)->type == WORD)
		process_word_token(*current, curr_token);
	else if ((*curr_token)->type == PIPE)
		process_pipe_token(current, cmd_list, cmd_idx, curr_token);
	else if ((*curr_token)->type == RED_IN || (*curr_token)->type == RED_OUT || 
			(*curr_token)->type == RED_APPEND)
		process_redirection(current, cmd_list, cmd_idx, curr_token);
	else if ((*curr_token)->type == HEREDOC)
		(*current)->heredoc = 1;
	else
		*curr_token = (*curr_token)->next;
}

t_token **tokens_to_cmds(t_arg *tokens)
{
	t_token **cmd_list;
	t_token *first;
	t_token *current;
	t_arg   *curr_token;
	int     count, cmd_idx;

	if (!tokens)
		return (NULL);
	count = count_commands(tokens);
	cmd_list = (t_token **)ft_malloc(sizeof(t_token *) * (count + 1));
	first = initialize_token_node();
	cmd_list[0] = first;
	current = first;
	cmd_idx = 1;
	curr_token = tokens;
	while (curr_token)
		process_token(&current, &cmd_list, &cmd_idx, &curr_token);
	cmd_list[count] = NULL;
	return (cmd_list);
}
