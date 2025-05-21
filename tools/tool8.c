/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:12:35 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:15 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_word_field(char *s, char **str, int *i, int *c)
{
	int	j;

	j = *i;
	while (s[j])
	{
		if (s[j] == '"' || s[j] == '\'')
		{
			skip_quotes(s, &j, s[j]);
			j++;
		}
		else if (!is_delimiter(s[j]))
			j++;
		else
			break ;
	}
	str[*c] = (char *)ft_malloc(sizeof(char) * (j - *i + 1));
	if (!str[*c])
		allocation_fails();
	ft_memcpy(str[*c], s + *i, sizeof(char) * (j - *i));
	str[*c][j - *i] = '\0';
	*i = j;
	(*c)++;
}

void	fill_split_field(char **str, char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (!is_delimiter(s[i]))
			add_word_field(s, str, &i, &c);
		else if (is_delimiter(s[i]))
			i++;
	}
	str[c] = NULL;
}

static void	process_word_field(char *s, int *i, int *count, int *in_field)
{
	if (s[*i] == '"' || s[*i] == '\'')
	{
		if (!(*in_field))
		{
			(*count)++;
			*in_field = 1;
		}
		handle_quotes(s, i);
	}
	else if (!is_delimiter(s[*i]))
	{
		if (!(*in_field))
		{
			(*count)++;
			*in_field = 1;
		}
		(*i)++;
	}
	else
	{
		*in_field = 0;
		(*i)++;
	}
}

int	word_counter_field(char *s)
{
	int	i;
	int	count;
	int	in_field;

	i = 0;
	count = 0;
	in_field = 0;
	while (s[i])
		process_word_field(s, &i, &count, &in_field);
	return (count);
}

char	**split_token_field(char *s)
{
	char	**str;
	int		len;

	len = word_counter_field(s);
	if (!s || !len)
		return (NULL);
	str = (char **)ft_malloc(sizeof(char *) * (len + 1));
	fill_split(str, s);
	return (str);
}
