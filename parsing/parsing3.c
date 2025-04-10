/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/11 16:40:41 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*search_env(char *var, t_mp *ev)
// {
// 	int		i;
// 	char	*new_var;
// 	char	*equal_sign;
// 	int		len;

// 	i = 0;
// 	new_var = ft_malloc(sizeof(char) * (ft_strlen(&var[1]) + 2));
// 	if (!new_var)
// 		allocation_fails();
// 	ft_strlcpy(new_var, &var[1], ft_strlen(&var[1]) + 1);
// 	len = ft_strlen(new_var);
// 	new_var[len] = '=';
// 	new_var[len + 1] = '\0';
// 	while (ev->envp[i])
// 	{
// 		if (ft_strncmp(ev->envp[i], new_var, ft_strlen(new_var)) == 0)
// 		{
// 			equal_sign = ft_strchr(ev->envp[i], '=');
// 			if (equal_sign)
// 				return (equal_sign + 1);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*replace_var(char *token, char *var, char *value)
// {
// 	char	*new_string;
// 	char	*var_pos;
// 	int		before_var_len;
// 	int		total_len;

// 	var_pos = ft_strstr(token, var);
// 	if (!var_pos)
// 		return (ft_strdup(token));
// 	before_var_len = var_pos - token;
// 	total_len = ft_strlen(token) - ft_strlen(var) + ft_strlen(value);
// 	new_string = ft_malloc(sizeof(char) * (total_len + 1));
// 	if (!new_string)
// 		allocation_fails();
// 	ft_strlcpy(new_string, token, before_var_len);
// 	ft_strcat(new_string, value);
// 	ft_strcat(new_string, var_pos + ft_strlen(var));
// 	return (new_string);
// }

// C
t_red *create_redirection(t_token_type type, char *file)
{
	t_red *red;
	t_token_type *type_ptr;
	
	red = ft_malloc(sizeof(t_red));
	if (!red)
		allocation_fails();
	type_ptr = ft_malloc(sizeof(t_token_type));
	if (!type_ptr)
	allocation_fails();
	*type_ptr = type;
	red->type = type_ptr;
	red->file = ft_strdup(file);
	red->next = NULL;
	return red;
}

void append_redirection(t_red **head, t_token_type type, char *file)
{
	t_red *new;
	t_red *tmp;
	
	new = create_redirection(type, file);
    if (!*head)
        *head = new;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
		tmp->next = new;
    }
}

t_cmd *create_command(char *arg_str)
{
	t_cmd *cmd;
	
	cmd = ft_malloc(sizeof(t_cmd));
	if (!cmd)
		allocation_fails();
	cmd->arg = ft_malloc(sizeof(char *) * 2);
	if (!cmd->arg)
		allocation_fails();
	if (arg_str)
	cmd->arg[0] = ft_strdup(arg_str);
	else
		cmd->arg[0] = NULL;
	cmd->arg[1] = NULL;
	cmd->next = NULL;
	return cmd;
}

void append_command(t_cmd **head, char *arg)
{
	t_cmd *new;
	t_cmd *tmp;

	new = create_command(arg);
    if (!*head)
	*head = new;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void handle_redirection(t_token *token, t_arg *current, t_arg **curr_ptr)
{
    if (current->next && current->next->type == WORD)
    {
        append_redirection(&token->redi, current->type, current->next->arg);
        *curr_ptr = current->next;
    }
}

t_token *initialize_token_node(void)
{
	t_token *node;
	
	node = ft_malloc(sizeof(t_token));
	if (!node)
		allocation_fails();
	node->cmds = NULL;
	node->redi = NULL;
	node->heredoc = 0;
	node->next = NULL;
	return node;
}

void	new_pipeline(t_token *node)
{
	node->type = PIPELINE;
	node->next = initialize_token_node();
	if(!node->next)
		allocation_fails();
}

t_token *tokens_to_cmds(t_arg *tokens)
{
	t_token *node;
	t_token *first;
	t_arg   *current;

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
	node->type = CMD;
	return first;
}
