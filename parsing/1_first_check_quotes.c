/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_first_check_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/01 13:40:25 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unclosed_quotes_error(t_mp *pg)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	pg->exit_status = 2;
}

int	skip_quote(char *s, int *i, char c)
{
	int	j;

	j = *i;
	while (s[j])
	{
		if (s[j] == c && j != *i)
			break ;
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
			if (!skip_quote(s, &i, s[i]))
			{
				unclosed_quotes_error(pg);
				free(s);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
