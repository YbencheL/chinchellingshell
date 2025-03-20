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

void	herdock_detected(void)
{
	printf("herdock_detect\n");
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

	j = *start;
	while (s[j])
	{
		if ((s[j] == '\\' && s[j + 1] == c) || (j == *start))
			j++;
		else if (s[j] == c)
			break;
		j++;
	}
	if (s[j] == c)
{		str = ft_substr(s, *start, j - *start + 1);
		*start = j + 1;
		//printf("%s\n", str);
		return (str);
}
*start = j + 1;
	return (NULL);
}

t_list	*split_phrase(char *s)
{
	int	i;
	t_list	*phrase;
	char *str;

	i = 0;
	phrase = (t_list *)malloc(sizeof(t_list *));
	while (s[i])
	{
		if (s[i] == '"')
		{
			str = extract_phrase(s, &i, '"');
			if (!str)
				herdock_detected();
			//else
			//	ft_lstadd_back(&phrase, ft_lstnew(str));
			printf("%s\n", str);
		}
		else if (s[i] == '\'')
		{
			str = extract_phrase(s, &i, '\'');
			if (!str)
				herdock_detected();
			//else
			//	ft_lstadd_back(&phrase, ft_lstnew(str));
			printf("%s\n", str);
		}
		else
		{
			str = extract_word(s, &i);
			printf("%s\n", str);
		}
	}
	return (phrase);
}
/*we still need to hundle word outside the quotes 
get the linked list we creat splited and take it inside the token list while identifyinh it type*/