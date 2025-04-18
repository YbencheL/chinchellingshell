/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:41:44 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/13 14:16:12 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	word_counter(const char *s)
{
    int	i;
    int	w;

    i = 0;
    w = 0;
    if (s[0] != ' ' && s[0] != '\t' && s[0] != '\0')
        w++;
    while (s[i])
    {
        if ((s[i] == ' ' || s[i] == '\t') && s[i + 1] != ' ' && s[i + 1] != '\t' && s[i + 1] != '\0')
            w++;
        i++;
    }
    return (w);
}

static char	*ft_cpy(int *start, int end, const char *s)
{
    char	*str;

    while ((s[*start] == ' ' || s[*start] == '\t') && s[*start])
        *start = *start + 1;
    str = (char *)ft_malloc(end - *start + 1);
    if (!str)
        return (NULL);
    ft_memcpy(str, s + *start, end - *start);
    str[end - *start] = '\0';
    if (s[end])
        *start = end + 1;
    else
        *start = end;
    while ((s[*start] == ' ' || s[*start] == '\t') && s[*start])
        *start = *start + 1;
    return (str);
}

static void	ft_free(char **str, int words)
{
    int	i;

    i = 0;
    while (i < words)
        free(str[i++]);
    free(str);
}

static int	check_end(const char *s, int i)
{
    int	k;

    k = 0;
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    while (s[i] != ' ' && s[i] != '\t' && s[i])
    {
        i++;
        k++;
    }
    if (k > 0)
        return (i);
    else
        return (-i - 5);
}

char	**ft_split(char *s)
{
    char	**str;
    int		i;
    int		j;

    if (!s || !word_counter(s))
        return (NULL);
    str = (char **)ft_malloc((word_counter(s) + 1) * sizeof(char *));
    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i++])
    {
        if (check_end(s, i - 1) >= 0)
        {
            str[j] = ft_cpy(&i, check_end(s, --i), s);
            if (!str[j++])
            {
                ft_free(str, j);
                return (NULL);
            }
        }
    }
    str[j] = NULL;
    return (str);
}