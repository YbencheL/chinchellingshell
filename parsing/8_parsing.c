/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:14:36 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/01 18:36:21 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inisialise_cmds(t_cmds *cmd)
{
	cmd->cmds = NULL;
	cmd->files = NULL;
	cmd->next = NULL;
}

void	handle_file_type(t_file *file, char *s)
{
	if (!ft_strcmp(s, ">>"))
		file->type = RED_APPEND;
	else if (!ft_strcmp(s, "<<"))
		file->type = HEREDOC;
	else if (!ft_strcmp(s, "<"))
		file->type = RED_IN;
	else if (!ft_strcmp(s, ">"))
		file->type = RED_OUT;
	file->fd = 0;
}
