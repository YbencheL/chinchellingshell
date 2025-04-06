/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/06 12:16:08 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unclosed_q_error(t_mp *pg)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	pg->exit_status = 2;
}

char	*extract_word(char *s, int *start)
{
	int		i;
	char	*str;

	i = *start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			break ;
		i++;
	}
	str = ft_substr(s, *start, i - *start);
	*start = i;
	return (str);
}

char	*extract_phrase(char *s, int *start, char c)
{
	int		j;
	char	*str;

	str = NULL;
	j = *start + 1;
	while (s[j])
	{
		if (((s[j] == '\\' || s[j] == ';') && s[j + 1] == c))
			j += 2;
		if (s[j] == c)
			break ;
		j++;
	}
	if (s[j] == c)
	{
		str = ft_substr(s, *start, j - *start + 1);
		*start = j + 1;
		return (str);
	}
	return (NULL);
}

t_list	*handle_quotes(char *s, int *i, t_list **phrase, t_mp *pg)
{
	char	*str;
	char	quote_type;

	quote_type = s[*i];
	str = extract_phrase(s, i, quote_type);
	if (!str)
	{
		unclosed_q_error(pg);
		return (NULL);
	}
	ft_lstadd_back(phrase, ft_lstnew(str));
	return (*phrase);
}

t_list	*split_phrase(char *s, t_mp *pg)
{
	int		i;
	t_list	*phrase;
	char	*str;

	phrase = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!handle_quotes(s, &i, &phrase, pg))
				return (NULL);
		}
		else if (s[i] != ' ' && s[i] != '\t')
		{
			str = extract_word(s, &i);
			ft_lstadd_back(&phrase, ft_lstnew(str));
		}
		else
			i++;
	}
	return (phrase);
}
