/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:00:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/28 20:05:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_word_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !is_delimiter(s[len]) && !is_special_char(s[len]))
		len++;
	return (len);
}

int	handle_special_chars(char const **s, char **split, size_t *i)
{
	int	advance;

	advance = 1;
	if ((**s == '>' && *(*s + 1) == '>') || (**s == '<' && *(*s + 1) == '<'))
	{
		split[*i] = ft_substr(*s, 0, 2);
		advance = 2;
	}
	else
		split[*i] = ft_substr(*s, 0, 1);
	if (!split[*i])
		return (0);
	(*i)++;
	*s += advance;
	return (1);
}

int	handle_words(char const **s, char **split, size_t *i)
{
	int	len;

	len = get_word_len(*s);
	split[*i] = ft_substr(*s, 0, len);
	if (!split[*i])
		return (0);
	(*i)++;
	*s += len;
	return (1);
}

size_t	count_splits(char const *s)
{
	size_t	count;
	int		in_split;

	count = 0;
	in_split = 0;
	while (*s)
	{
		if (is_special_char(*s))
		{
			count++;
			if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
						+ 1) == '<'))
				s++;
			in_split = 0;
		}
		else if (!is_delimiter(*s) && !in_split)
		{
			in_split = 1;
			count++;
		}
		else if (is_delimiter(*s))
			in_split = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s)
{
	char	**split;
	size_t	total_splits;

	if (!s)
		return (NULL);
	total_splits = count_splits(s);
	split = (char **)ft_malloc((total_splits + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (process_splits(s, split));
}
