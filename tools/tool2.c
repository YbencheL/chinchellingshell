/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:00:00 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/10 15:33:35 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**split_token(char *s)
{
	char	**str;

	if (!s || !word_counter(s))
		return (NULL);
	str = (char **)ft_malloc(sizeof(char *) * (word_counter(s) + 1));
	fill_split(str, s);
	return (str);
}
