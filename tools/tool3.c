/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:44:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/28 20:05:01 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = (size_t)ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len < len + start)
		len = s_len - start;
	str = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**free_split(char **split, size_t i)
{
	while (i--)
		free(split[i]);
	free(split);
	return (NULL);
}

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	**process_splits(char const *s, char **split)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && is_delimiter(*s))
			s++;
		if (!*s)
			break ;
		if (is_special_char(*s))
		{
			if (!handle_special_chars(&s, split, &i))
				return (free_split(split, i));
		}
		else
		{
			if (!handle_words(&s, split, &i))
				return (free_split(split, i));
		}
	}
	split[i] = NULL;
	return (split);
}
