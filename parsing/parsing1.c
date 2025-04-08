/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/08 17:42:44 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unclosed_q_error(t_mp *pg)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	pg->exit_status = 2;
}

int	skip_q(char *s, int *i, char c)
{
	int	j;

	j = *i;
	while (s[j])
	{
		if (s[j] == c && j != *i)
			break;
		j++;
	}
	if (s[j] == '\0')
		return (0);
	*i = j;
	return (1);
}

int	check_unclosed_quotes(char *s, t_mp *pg)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!skip_q(s, &i, s[i]))
			{
				unclosed_q_error(pg);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

t_arg	*add_token(char **str)
{
	int		i;
	t_arg	*token;

	token = NULL;
	i = 0;
	while (str[i])
	{
		argadd_back(&token, new_arg(str[i]));
		i++;
	}
	return (token);
}



// char	*extract_word(char *s, int *start, t_lst **phrase)
// {
// 	int		i;
// 	char	*str;
// 	int		is;
	
// 	is = 0;
// 	i = *start;
// 	while (s[i])
// 	{
// 		if (s[i] == ' ' || s[i] == '\t')
// 		{
// 			is = 1;
// 			break;
// 		}
// 		else if (s[i] != '"' && s[i] != '\'')
// 			is = 0;
// 		if (s[i] == '\'' || s[i] == '"')
// 			break ;
// 		i++;
// 	}
// 	printf("%i\n", is);
// 	str = ft_substr(s, *start, i - *start);
// 	*start = i;
// 	ft_lstadd_back_space(phrase, ft_lstnew_space(str, is));
// 	return (str);
// }

// char	*extract_phrase(char *s, int *start, char c)
// {
// 	int		j;
// 	char	*str;

// 	str = NULL;
// 	j = *start + 1;
// 	while (s[j])
// 	{
// 		if (((s[j] == '\\' || s[j] == ';') && s[j + 1] == c))
// 			j += 2;
// 		if (s[j] == c)
// 			break ;
// 		j++;
// 	}
// 	if (s[j] == c)
// 	{
// 		str = ft_substr(s, *start, j - *start + 1);
// 		*start = j + 1;
// 		return (str);
// 	}
// 	return (NULL);
// }

// t_lst	*handle_quotes(char *s, int *i, t_lst **phrase, t_mp *pg)
// {
// 	char	*str;
// 	char	quote_type;
// 	int		is;

// 	is = 0;
// 	quote_type = s[*i];
// 	str = extract_phrase(s, i, quote_type);
// 	if (!str)
// 	{
// 		unclosed_q_error(pg);
// 		return (NULL);
// 	}
// 	if (s[*i] == ' ' || s[*i] == '\t')
// 		is = 1;
// 	printf("%i\n", is);
// 	ft_lstadd_back_space(phrase, ft_lstnew_space(str, is));
// 	return (*phrase);
// }

// t_lst	*split_phrase(char *s, t_mp *pg)
// {
// 	int		i;
// 	t_lst	*phrase;

// 	phrase = NULL;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 		{
// 			if (!handle_quotes(s, &i, &phrase, pg))
// 				return (NULL);
// 		}
// 		else if (s[i] != ' ' && s[i] != '\t')
// 			extract_word(s, &i, &phrase);
// 		else
// 			i++;
// 	}
// 	return (phrase);
// }
