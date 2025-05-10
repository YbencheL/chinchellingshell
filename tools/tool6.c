/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:50 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:36:30 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_special_char(char *s, int *i)
{
	if ((s[*i] == '<' && s[*i + 1] == '<')
		|| (s[*i] == '>' && s[*i + 1] == '>'))
		*i += 2;
	else
		(*i)++;
	return (1);
}

int	handle_quotes(char *s, int *i)
{
	char	quote;

	quote = s[(*i)++];
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
	return (0);
}

int	count_word(char *s, int *i, int *f)
{
	int	c;

	c = 0;
	if (is_special_char(s[*i]))
	{
		c += handle_special_char(s, i);
		*f = 0;
	}
	else
	{
		if (!*f)
		{
			c++;
			*f = 1;
		}
		if (s[*i] == '"' || s[*i] == '\'')
			*f = handle_quotes(s, i);
		else
			(*i)++;
	}
	return (c);
}

int	word_counter(char *s)
{
	int		c;
	int		i;
	int		f;

	c = 0;
	i = 0;
	f = 0;
	while (s[i])
	{
		if (is_delimiter(s[i]))
		{
			i++;
			f = 0;
		}
		else
			c += count_word(s, &i, &f);
	}
	return (c);
}
