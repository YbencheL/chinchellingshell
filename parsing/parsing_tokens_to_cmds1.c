/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_to_cmds1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/20 15:08:41 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inisialize_cmds(t_token *cmds)
{
	cmds->cmds = NULL;
	cmds->heredoc = 0;
	cmds->next = NULL;
	cmds->type = 0;
}

void	handle_type_Word(t_arg **arg, t_token *cmds)
{
	t_arg	*head;
	int		i;
	char 	**str;
	
	head = *arg;
	i = 0;
	while (head && head->type == WORD)
	{
		head = head->next;
		i++;
	}
	str = (char **)ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*arg && (*arg)->type == WORD)
	{
		str[i] = (*arg)->arg;
		(*arg) = (*arg)->next;
		i++;
	}
	str[i] = NULL;
	cmds->cmds = str;
	cmds->next = NULL;
	cmds->type = CMD;
}

void	handle_redirections(t_arg **arg, t_token *cmds)
{
	char 	**str;
	t_arg	*head;
	
	head = *arg;
	str = (char **)ft_malloc(sizeof(char *) * (3));
	str[0] = (*arg)->arg;
	(*arg) = (*arg)->next;
	str[1] = (*arg)->arg;
	(*arg) = (*arg)->next;
	str[2] = NULL;
	cmds->cmds = str;
	cmds->next = NULL;
	if (head->type == HEREDOC)
		cmds->heredoc = 1;
	cmds->type = REDIRECTION;
}

void	handle_pipe(t_arg **arg, t_token *cmds)
{
	char 	**str;

	str = (char **)ft_malloc(sizeof(char *) * (2));
	str[0] = (*arg)->arg;
	(*arg) = (*arg)->next;
	str[1] = NULL;
	cmds->cmds = str;
	cmds->next = NULL;	
	cmds->type = PIPELINE;
}

t_token *tokens_to_cmds(t_arg *tokens)
{
    t_token *cmd_list;
    t_token *first;
    t_arg   *curr_token;
	t_token *tmp;
        
    curr_token = tokens;
    cmd_list = NULL;
    first = NULL;
    while (curr_token)
    {
		tmp = (t_token *)ft_malloc(sizeof(t_token));
		inisialize_cmds(tmp);
        if (curr_token->type == WORD)
            handle_type_Word(&curr_token, tmp);
        else if (curr_token->type == PIPE)
			handle_pipe(&curr_token, tmp);
        else if (curr_token->type == RED_IN || curr_token->type == RED_OUT || 
                curr_token->type == RED_APPEND || curr_token->type == HEREDOC)
			handle_redirections(&curr_token, tmp);
		if (!first)
		{
			first = tmp;
			cmd_list = tmp;
		}
		else
		{
			cmd_list->next = tmp;
			cmd_list = cmd_list->next;
		}
    }
	cmd_list = first;
    return (cmd_list);
}
