/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1_export_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:43:19 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:22 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_export_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (s[i] == '"' || s[i] == '\'')
			skip_quotes(s, &i, s[i]);
		else if (s[i] == ' ' || s[i] == '\t')
			return (1);
		else
			i++;
	}
	return (0);
}

void	split_export_f(t_arg **token, char *s)
{
	t_arg	*head;
	t_arg	*next;
	char	**str;
	int		i;

	i = 1;
	next = (*token)->next;
	str = split_token_field(bc_strchr_fo_rv(s, '=', '+'));
	head = new_arg(str[0]);
	head->type = WORD;
	*token = head;
	while (str[i])
	{
		head->next = new_arg(str[i]);
		head = head->next;
		head->type = WORD;
		i++;
	}
	head->next = next;
}

void	hundle_export_field(t_arg *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type >= 2 && token->type <= 5)
			token = token->next;
		else if (check_export_spaces(token->arg))
			split_export_f(&token, token->arg);
		token = token->next;
	}
}
