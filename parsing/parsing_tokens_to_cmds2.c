/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_to_cmds2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:44:11 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/12 17:49:56 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_red	*create_redirection(t_token_type type, char *file)
{
	t_red			*red;
	t_token_type	*type_ptr;

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
	return (red);
}

void	append_redirection(t_red **head, t_token_type type, char *file)
{
	t_red	*new;
	t_red	*tmp;

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

t_cmd	*create_command(char *arg_str)
{
	t_cmd	*cmd;

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
	return (cmd);
}

void	append_command(t_cmd **head, char *arg)
{
	t_cmd	*new;
	t_cmd	*tmp;

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
