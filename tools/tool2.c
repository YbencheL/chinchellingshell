/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:00:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/13 14:15:08 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_quotes(char *s, int *i, char c)
{
	int	j;

	j = *i + 1;
	while (s[j])
	{
		if (s[j] == c)
			break ;
		j++;
	}
	if (s[j] != '\0')
		*i = j;
	else if (s[j] == '\0')
		*i = j - 1;
}

void	hundel_spe_char(char *s, char **str, int *i, int *c)
{
	int	j;

	j = 1;
	if ((s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '>' && s[*i
				+ 1] == '>'))
		j++;
	str[*c] = (char *)ft_malloc(sizeof(char) * (j + 1));
	ft_memcpy(str[*c], s + *i, sizeof(char) * j);
	str[*c][j] = '\0';
	*i = *i + j;
	(*c)++;
}

void	add_word(char *s, char **str, int *i, int *c)
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
		else if (!is_delimiter(s[j]) && !is_special_char(s[j]))
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

void	fill_split(char **str, char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (!is_delimiter(s[i]) && !is_special_char(s[i]))
			add_word(s, str, &i, &c);
		else if (is_special_char(s[i]))
			hundel_spe_char(s, str, &i, &c);
		else if (is_delimiter(s[i]))
			i++;
	}
	str[c] = NULL;
}

int	word_counter(char *s)
{
	int		c;
	int		i;
	int		f;
	char	quote;

	c = 0;
	i = 0;
	f = 0;
	while (s[i])
	{
		if (is_delimiter(s[i]))
		{
			i++;
			f = 0;
			continue ;
		}
		if (is_special_char(s[i]))
		{
			if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i
					+ 1] == '>'))
				i += 2;
			else
				i++;
			c++;
			f = 0;
			continue ;
		}
		if (!f)
		{
			c++;
			f = 1;
		}
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
			i++;
	}
	return (c);
}

char	**split_token(char *s)
{
	char	**str;

	if (!s || !word_counter(s))
		return (NULL);
	str = (char **)ft_malloc(sizeof(char *) * (word_counter(s) + 1));
	fill_split(str, s);
	return (str);
}
