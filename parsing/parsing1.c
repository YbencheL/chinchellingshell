/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:51:57 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/18 15:19:9:06 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unclosed_q_error(void)
{
	ft_putstr_fd("minishell: unclosed quotes\n", 2);
}

char	*extract_word(char *s, int *start)
{
	int	i;
	char	*str;

	i = *start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			break;
		i++;	
	}
	str = ft_substr(s, *start, i - *start);
	*start = i;
	return (str);
}

char	*extract_phrase(char *s, int *start, char c)
{
	int	j;
	char *str = NULL;

	j = *start + 1;
	while (s[j])
	{
		if (((s[j] == '\\' || s[j] == ';') && s[j + 1] == c) || (j == *start))
			j += 2;
		else if (s[j] == c)
			break;
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

t_list	*handle_quotes(char *s, int *i, t_list **phrase)
{
	char	*str;
	char	quote_type;

	quote_type = s[*i];
	str = extract_phrase(s, i, quote_type);
	if (!str)
	{
		unclosed_q_error();
		return (NULL);
	}
	ft_lstadd_back(phrase, ft_lstnew(str));
	return (*phrase);
}

t_list	*split_phrase(char *s)
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
			if (!handle_quotes(s, &i, &phrase))
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

/*we still need to hundle word outside the quotes 
get the linked list we creat splited and take it inside the token list while identifyinh it type*/