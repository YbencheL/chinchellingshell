/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_to_cmds1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/16 13:18:17 by ybenchel         ###   ########.fr       */
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

int count_commands(t_arg *tokens)
{
    int count = 1;
    t_arg *curr = tokens;
    
    if (!tokens)
        return 0;
    
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
    return count;
}

void handle_word_token(t_token *current, t_arg *token)
{

    if (!current->cmds)
        current->cmds = ft_malloc(sizeof(char*) * 2);
        
    if (!current->cmds[0])
    {
        current->cmds[0] = token->arg;
        current->cmds[1] = NULL;
    }
}

t_token **tokens_to_cmds(t_arg *tokens)
{
    t_token **cmd_list;
    t_token *first;
    t_token *current;
    t_arg   *curr_token;
    int     count = 0;
    int     cmd_idx = 1;

    if (!tokens)
        return (NULL);
        
    curr_token = tokens;
    count = count_commands(tokens);
    cmd_list = (t_token **)ft_malloc(sizeof(t_token *) * (count + 1));
    first = initialize_token_node();
    cmd_list[0] = first;
    current = first;

    while (curr_token)
    {
        if (curr_token->type == WORD)
        {
            if (!current->cmds[0])
            {
                handle_word_token(current, curr_token);
            }
            else
            {
                current->next = initialize_token_node();
                current = current->next;
                current->type = CMD;
                current->cmds[0] = curr_token->arg;
                current->cmds[1] = NULL;
                if (cmd_idx < count)
                    cmd_list[cmd_idx++] = current;
            }
            curr_token = curr_token->next;
        }
        else if (curr_token->type == PIPE)
        {
            current->next = initialize_token_node();
            current = current->next;
            current->cmds[0] = curr_token->arg;
            current->cmds[1] = NULL;
			current->type = PIPELINE;
            if (cmd_idx < count)
                cmd_list[cmd_idx++] = current;
            current->next = initialize_token_node();
            current = current->next;
            if (cmd_idx < count)
                cmd_list[cmd_idx++] = current;   
            curr_token = curr_token->next;
        }
        else if (curr_token->type == RED_IN || curr_token->type == RED_OUT || 
                curr_token->type == RED_APPEND)
        {
			current->next = initialize_token_node();
            current = current->next;
            current->type = REDIRECTION;
            current->cmds[0] = curr_token->arg;
            current->cmds[1] = NULL;
            if (cmd_idx < count)
                cmd_list[cmd_idx++] = current;
            current->next = initialize_token_node();
            current = current->next;
            current->type = FILE_ARG;
            current->cmds[0] = curr_token->next->arg;
            current->cmds[1] = NULL;
            if (cmd_idx < count)
                cmd_list[cmd_idx++] = current;
            curr_token = curr_token->next->next;
        }
        else if (curr_token->type == HEREDOC)
            current->heredoc = 1;
        else
            curr_token = curr_token->next;
    }
    cmd_list[count] = NULL;
    return (cmd_list);
}
