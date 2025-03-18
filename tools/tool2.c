/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:00:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/18 20:35:52 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **free_split(char **split, size_t i)
{
    while (i--)
        free(split[i]);
    free(split);
    return (NULL);
}

static int handle_special_chars(char const **s, char **split, size_t *i)
{
    int advance = 1;
    
    if ((**s == '>' && *(*s + 1) == '>')
        || (**s == '<' && *(*s + 1) == '<'))
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

static char **process_splits(char const *s, char **split)
{
    size_t i = 0;

    while (*s)
    {
        while (*s && is_delimiter(*s))
            s++;
        if (!*s)
            break;  
        if (is_special_char(*s))
        {
            if (!handle_special_chars(&s, split, &i))
                return (free_split(split, i));
        }
        else
        {
            size_t len = get_word_len(s);
            split[i] = ft_substr(s, 0, len);
            if (!split[i])
                return (free_split(split, i));
            i++;
            s += len;
        }
    }
    split[i] = NULL;
    return (split);
}

char **ft_split(char const *s)
{
    char **split;
    size_t total_splits;

    if (!s)
        return (NULL);
    total_splits = count_splits(s);
    split = (char **)malloc((total_splits + 1) * sizeof(char *));
    if (!split)
        return (NULL);
    return (process_splits(s, split));
}
