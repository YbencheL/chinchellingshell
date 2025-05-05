/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:05:52 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/01 19:39:19 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

void	ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
}
