/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/06 18:42:37 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unclosed_q_error(t_mp *pg)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	pg->exit_status = 2;
}

char	*extract_word(char *s, int *start, t_lst **phrase)
{
	int		i;
	char	*str;
	int		is;
	
	is = 0;
	i = *start;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			is = 1;
		else if (s[i] != '"' && s[i] != '\'')
			is = 0;
		if (s[i] == '\'' || s[i] == '"')
			break ;
		i++;
	}
	printf("%i\n", is);
	str = ft_substr(s, *start, i - *start);
	*start = i;
	ft_lstadd_back_space(phrase, ft_lstnew_space(str, is));
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

t_lst	*handle_quotes(char *s, int *i, t_lst **phrase, t_mp *pg)
{
	char	*str;
	char	quote_type;
	int		is;

	is = 0;
	quote_type = s[*i];
	str = extract_phrase(s, i, quote_type);
	if (!str)
	{
		unclosed_q_error(pg);
		return (NULL);
	}
	if (s[*i] == ' ' || s[*i] == '\t')
		is = 1;
	printf("%i\n", is);
	ft_lstadd_back_space(phrase, ft_lstnew_space(str, is));
	return (*phrase);
}

t_lst	*split_phrase(char *s, t_mp *pg)
{
	int		i;
	t_lst	*phrase;

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
			extract_word(s, &i, &phrase);
		else
			i++;
	}
	return (phrase);
}
