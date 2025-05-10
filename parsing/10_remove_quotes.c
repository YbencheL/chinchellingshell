/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:38:28 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:19:32 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_inside_quotes(char *src, char *dst, int *i, int *j)
{
	char	c;

	c = src[*i];
	(*i)++;
	while (src[*i])
	{
		if (src[*i] != c)
		{
			dst[*j] = src[*i];
			(*j)++;
			(*i)++;
		}
		else
			break ;
	}
	if (src[*i] != '\0')
		(*i)++;
}

char	*quote_remover_helper(char *s, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)ft_malloc(sizeof(char) * (len + 1));
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			copy_inside_quotes(s, str, &i, &j);
		else
		{
			str[j] = s[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

void	skip_qouted_content(char *s, int *i, int *len, char c)
{
	(*i)++;
	while (s[*i])
	{
		if (s[*i] == c)
			break ;
		else
			(*len)++;
		(*i)++;
	}
	if (s[*i] != '\0')
		(*i)++;
}

char	*quote_remover(char *s)
{
	int	i;
	int	len;
	int	s_len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			skip_qouted_content(s, &i, &len, s[i]);
		else
		{
			len++;
			i++;
		}
	}
	s_len = ft_strlen(s);
	if (s_len == len)
		return (s);
	return (quote_remover_helper(s, len));
}

void	remove_quotes(t_cmds *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->cmds[i])
		{
			cmds->cmds[i] = quote_remover(cmds->cmds[i]);
			i++;
		}
		cmds = cmds->next;
	}
}
