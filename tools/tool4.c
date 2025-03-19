/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:25:20 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/19 17:47:11 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	token_type(char *str)
{
	t_token_type 	type;

	if(ft_strcmp(str, "|"))
		return type = PIPE;
	else if(ft_strcmp(str, "<"))
		return type = RED_IN;
	else if(ft_strcmp(str, ">"))
		return type = RED_OUT;
	else if(ft_strcmp(str, ">>"))
		return type = RED_APPEND;
	else if(ft_strcmp(str, "<<"))
		return type = HEREDOC;
	else
		return type = WORD;
}
