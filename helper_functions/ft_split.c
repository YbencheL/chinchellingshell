/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:41:44 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 09:45:38 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep(char c, char *sep)
{
	int	j;

	j = 0;
	while (sep[j])
	{
		if (c == sep[j])
			return (1);
		j++;
	}
	return (0);
}

int	word_counter_1(char *str, char *sep)
{
	int	i;
	int	l;
	int	s;

	i = 0;
	l = 0;
	s = 1;
	while (str[i])
	{
		if (!(is_sep(str[i], sep)))
		{
			if (s == 1)
				l++;
			s = 0;
		}
		else
			s = 1;
		i++;
	}
	return (l);
}

int	find_end(int i, char *str, char *sep)
{
	int	end;

	end = 0;
	while (str[i])
	{
		if (!(is_sep(str[i], sep)))
			end++;
		else
			return (end);
		i++;
	}
	return (end);
}

char	*copy_word(int start, int end, char *str)
{
	int		i;
	char	*fstr;

	fstr = (char *)ft_malloc(sizeof(char) * (end + 1));
	if (!fstr)
		return (NULL);
	i = 0;
	while (str[start] && start < end)
	{
		fstr[i] = str[start];
		i++;
		start++;
	}
	fstr[i] = '\0';
	return (fstr);
}

char	**ft_split(char *str, char *charset)
{
	char	**fstr;
	int		i;
	int		k;

	fstr = (char **)ft_malloc(sizeof(char *) * (word_counter_1(str, charset) + 1));
	if (!fstr)
		return (NULL);
	k = 0;
	i = 0;
	while (str[i])
	{
		if (!(is_sep(str[i], charset)))
		{
			fstr[k++] = copy_word(i, (find_end(i, str, charset) + i), str);
			i = i + find_end(i, str, charset);
		}
		else
			i++;
	}
	fstr[k] = (NULL);
	return (fstr);
}