/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/08 19:59:53 by ybenchel         ###   ########.fr       */
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
t_cmd *create_command(void)
{
    t_cmd *cmd;

    cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
    if (!cmd)
        allocation_fails();
    cmd->cmds = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->appendfile = NULL;
    cmd->heredoc = 0;
    cmd->next = NULL;
    return (cmd);
}

void    handle_word_token(t_cmd *cmd, t_arg *current, int *i)
{
    if (*i == 0)
    {
        cmd->cmds = ft_malloc(sizeof(char *) * 100);
        if (!cmd->cmds)
            allocation_fails();
    }
    cmd->cmds[(*i)++] = ft_strdup(current->arg);
    if (!cmd->cmds[*i - 1])
        allocation_fails();
}

void    finalize_command(t_cmd *cmd, int i)
{
    if (i > 0)
    {
        cmd->cmds[i] = NULL;
        cmd->heredoc = 0;
    }
    cmd->next = NULL;
}

t_cmd    *tokens_to_cmds(t_arg *tokens)
{
    t_cmd    *cmd;
    t_cmd    *first_cmd;
    t_arg    *current;
    int        i = 0;

    cmd = create_command();
    first_cmd = cmd;
    current = tokens;
    while (current != NULL)
    {
        if (current->type == WORD)
            handle_word_token(cmd, current, &i);
        else if (current->type == PIPE)
        {
            cmd->type = PIPELINE;
            finalize_command(cmd, i);
            cmd->next = create_command();
            cmd = cmd->next;
            i = 0;
        }
		else if ((current->type == RED_IN || current->type == RED_OUT || current->type == RED_APPEND)
			&& current->next && current->next->type == WORD)
		{
 	 		if (current->type == RED_IN)
	  			cmd->infile = ft_strdup(current->next->arg);
  			else if (current->type == RED_OUT)
	 	 		cmd->outfile = ft_strdup(current->next->arg);
  			else if (current->type == RED_APPEND)
	  			cmd->appendfile = ft_strdup(current->next->arg);
  			current = current->next;
		}
        else if (current->type == HEREDOC)
            cmd->heredoc = 1;
        current = current->next;
    }
    finalize_command(cmd, i);
    return (first_cmd);
}
