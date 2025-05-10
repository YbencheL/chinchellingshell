/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:25:20 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/10 15:36:20 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_quotes(char *s, int *i, char c)
{
	int	j;

	j = *i + 1;
	while (s[j])
	{
		if (s[j] == c)
			break ;
		j++;
	}
	if (s[j] != '\0')
		*i = j;
	else if (s[j] == '\0')
		*i = j - 1;
}

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
