/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/10 18:52:32 by abenzaho         ###   ########.fr       */
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

void initialize_redirection_arrays(t_cmd *cmd)
{
    // cmd->infile = (char **)ft_malloc(sizeof(char *) * 1); 
    // cmd->outfile = (char **)ft_malloc(sizeof(char *) * 1);
    // cmd->appendfile = (char **)ft_malloc(sizeof(char *) * 1);

    // if (!cmd->infile || !cmd->outfile || !cmd->appendfile)
    //     allocation_fails();

    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->appendfile = NULL;
}

t_cmd *create_command(void)
{
    t_cmd *cmd;
    cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
    if (!cmd)
        allocation_fails();
    cmd->cmds = NULL;
    initialize_redirection_arrays(cmd);
    cmd->heredoc = 0;
    cmd->next = NULL;

    return cmd;
}

void    handle_word_token(t_cmd *cmd, t_arg *current, int *i)
{
    if (*i == 0)
    {
        cmd->cmds = (char **)ft_malloc(sizeof(char *) * 100);
        if (!cmd->cmds)
            allocation_fails();
    }
    cmd->cmds[(*i)++] = ft_strdup(current->arg);
}

void handle_redirection(t_cmd *cmd, t_arg *current, t_arg **curr_ptr)
{
    int current_size;

    if (current->next && current->next->type == WORD)
    {
        if (current->type == RED_IN)
        {
            current_size = ft_pcounter(cmd->infile);
            cmd->infile = ft_malloc(sizeof(char *) * (current_size + 2));
            if (!cmd->infile)
                allocation_fails();
            cmd->infile[current_size] = ft_strdup(current->next->arg);
            cmd->infile[current_size + 1] = NULL;
        }
        else if (current->type == RED_OUT)
        {
            current_size = ft_pcounter(cmd->outfile);
            cmd->outfile = ft_malloc(sizeof(char *) * (current_size + 2));
            if (!cmd->outfile)
                allocation_fails();
            cmd->outfile[current_size] = ft_strdup(current->next->arg);
            cmd->outfile[current_size + 1] = NULL;
        }
        else if (current->type == RED_APPEND)
        {
            current_size = ft_pcounter(cmd->appendfile);
            cmd->appendfile = ft_malloc(sizeof(char *) * (current_size + 2));
            if (!cmd->appendfile)
                allocation_fails();
            cmd->appendfile[current_size] = ft_strdup(current->next->arg);
            cmd->appendfile[current_size + 1] = NULL;
        }
        *curr_ptr = current->next;
    }
}

void handle_pipe(t_cmd *cmd, t_cmd **cmd_ptr, int *i)
{
    t_cmd *new_cmd;

    cmd->type = PIPELINE;
    if (*i > 0)
        cmd->cmds[*i] = NULL;
    new_cmd = create_command();
    cmd->next = new_cmd;
    *cmd_ptr = new_cmd;
    *i = 0;
}

t_cmd *tokens_to_cmds(t_arg *tokens)
{
	t_cmd 	*cmd;
	t_cmd 	*first_cmd;
	t_arg 	*current;
	int 	i;
	
	i = 0;
	cmd = create_command();
	first_cmd = cmd;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == WORD)
			handle_word_token(cmd, current, &i);
		else if (current->type == PIPE)
			handle_pipe(cmd, &cmd, &i);
		else if (current->type == RED_IN || current->type == RED_OUT
			|| current->type == RED_APPEND)
			handle_redirection(cmd, current, &current);
		else if (current->type == HEREDOC)
			cmd->heredoc = 1;
		current = current->next;
	}
	if (i > 0)
		cmd->cmds[i] = NULL;
	return (first_cmd);
}
