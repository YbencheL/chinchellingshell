/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:25:20 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/19 17:56:23 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	token_type(char *str)
{
	if(ft_strcmp(str, "|") == 0)
		return PIPE;
	else if(ft_strcmp(str, "<") == 0)
		return RED_IN;
	else if(ft_strcmp(str, ">") == 0)
		return RED_OUT;
	else if(ft_strcmp(str, ">>") == 0)
		return RED_APPEND;
	else if(ft_strcmp(str, "<<") == 0)
		return HEREDOC;
	else
		return WORD;
}
