/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:30:54 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/04 18:31:58 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(char **str, t_arg **token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		argadd_back(token, new_arg(str[i]));
		i++;
	}
}
