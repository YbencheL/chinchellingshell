/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expand_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:44:52 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/01 18:07:34 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_var_dquote(t_arg *token, int *j, t_mp *pg)
{
	while (token->arg[*j])
	{
		if (token->arg[*j] == '$' && (ft_isalnum(token->arg[*j + 1])
				|| token->arg[*j + 1] == '_' || token->arg[*j + 1] == '?'))
			token->arg = expand(token->arg, j, pg);
		else if (token->arg[*j] == '"')
		{
			(*j)++;
			break ;
		}
		else
			(*j)++;
	}
}

void	handle_var_quote(t_arg *token, int *j)
{
	while (token->arg[*j])
	{
		if (token->arg[*j] == '\'')
		{
			(*j)++;
			break ;
		}
		(*j)++;
	}
}

void	handle_quotes_var(t_arg *token, int *i, t_mp *pg)
{
	int	j;

	j = *i + 1;
	if (token->arg[*i] != '\'')
		handle_var_dquote(token, &j, pg);
	else
		handle_var_quote(token, &j);
	*i = j;
}

void	handle_var(t_arg *token, int *i, t_mp *pg)
{
	int	j;

	j = *i;
	while (token->arg[j])
	{
		if (token->arg[j] == '"' || token->arg[j] == '\'')
			break ;
		else if (token->arg[j] == '$' && (ft_isalnum(token->arg[j + 1])
				|| token->arg[j + 1] == '_' || token->arg[j + 1] == '?'))
			token->arg = expand(token->arg, &j, pg);
		else
			j++;
	}
	*i = j;
}

void	expand_variables(t_arg *token, t_mp *pg)
{
	int		i;
	t_arg	*head;

	head = token;
	while (token)
	{
		i = 0;
		if (token->type == HEREDOC)
			token = token->next->next;
		else
		{
			while (token->arg[i])
			{
				if (token->arg[i] == '"' || token->arg[i] == '\'')
					handle_quotes_var(token, &i, pg);
				else if (token->arg[i] != '"' || token->arg[i] != '\'')
					handle_var(token, &i, pg);
				else
					i++;
			}
			token = token->next;
		}
	}
}
