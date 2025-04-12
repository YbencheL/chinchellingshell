/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_char_to_token_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:26:46 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/12 18:06:45 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_syntaxe(t_arg *tokens)
{
	if (tokens->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
		return (0);
	}
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!tokens->next)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
				return (0);
			}
			else if (tokens->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token`||'\n", 2);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	check_redrection_syntaxe(t_arg *tokens)
{
	while (tokens)
	{
		if (tokens->type <= 5 && tokens->type >= 2)
		{
			if (!tokens->next)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token `redirection`\n", 2);
				return (0);
			}
			else if (tokens->next->type != WORD)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token `redirection`\n", 2);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

t_token_type	token_identifier(char *str)
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

t_arg	*add_token(char **str)
{
	int		i;
	t_arg	*token;

	token = NULL;
	i = 0;
	while (str[i])
	{
		argadd_back(&token, new_arg(str[i]));
		i++;
	}
	return (token);
}

t_arg   *tokenize(char *line, t_mp *pg)
{
    char    **lines;
    t_arg   *tokens;
	t_arg	*head;

    lines = split_token(line);
    tokens = add_token(lines);
	head = tokens;
	while (head)
	{
		head->type = token_identifier(head->arg);
		head = head->next;
	}
	if (!check_pipe_syntaxe(tokens) || !check_redrection_syntaxe(tokens))
	{
		pg->exit_status = 2;
		free(line);
		return(NULL);
	}
	return (tokens);
}
