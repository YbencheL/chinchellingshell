/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:44:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/22 12:16:58 by abenzaho         ###   ########.fr       */
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

size_t get_word_len(const char *s)
{
    size_t len;

    len = 0;
    while (s[len] && !is_delimiter(s[len]) && !is_special_char(s[len]))
        len++;
    return (len);
}

int is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}

int is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

size_t count_splits(char const *s)
{
    size_t count;
    int in_split;

    count = 0;
    in_split = 0;
    while (*s)
    {
        if (is_special_char(*s))
        {
            count++;
            if ((*s == '>' && *(s + 1) == '>')
                || (*s == '<' && *(s + 1) == '<'))
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
