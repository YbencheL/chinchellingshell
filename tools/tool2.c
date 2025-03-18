/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:00:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/18 17:18:28 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exit(void)
{
	printf("\033[2K\r");
	printf("\033[1;32m");
	printf("███████╗██╗  ██╗██╗████████╗\n");
	printf("██╔════╝╚██╗██╔╝██║╚══██╔══╝\n");
	printf("█████╗   ╚███╔╝ ██║   ██║   \n");
	printf("██╔══╝   ██╔██╗ ██║   ██║   \n");
	printf("███████╗██╔╝ ██╗██║   ██║   \n");
	printf("╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝    \n");
	printf("\033[0m");
}

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
	str = (char *)malloc(sizeof(char) * (len + 1));
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

static int is_delimiter(char c)
{
    return (c == ' ' || c == '\t');
}

static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static size_t count_splits(char const *s)
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
            if ((*s == '>' && *(s + 1) == '>') || ((*s == '<' && *(s + 1) == '<')))
            {
                s++;
                count++;
            }
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

static char **free_split(char **split, size_t i)
{
    while (i--)
        free(split[i]);
    free(split);
    return (NULL);
}

static size_t get_word_len(const char *s)
{
    size_t len;

    len = 0;
    while (s[len] && !is_delimiter(s[len]) && !is_special_char(s[len]))
        len++;
    return (len);
}

static char **process_splits(char const *s, char **split)
{
    size_t i;
    size_t len;

    i = 0;
    while (*s)
    {
        while (*s && is_delimiter(*s))
            s++;
        
        if (*s)
        {
            if (is_special_char(*s))
            {
                if ((*s == '>' && *(s + 1) == '>') || ((*s == '<' && *(s + 1) == '<')))
                {
                    split[i] = ft_substr(s, 0, 2);
                    if (!split[i])
                        return (free_split(split, i));
                    i++;
                    s += 2;
                }
                else
                {
                    split[i] = ft_substr(s, 0, 1);
                    if (!split[i])
                        return (free_split(split, i));
                    i++;
                    s++;
                }
            }
            else
            {
                len = get_word_len(s);
                split[i] = ft_substr(s, 0, len);
                if (!split[i])
                    return (free_split(split, i));
                i++;
                s += len;
            }
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
