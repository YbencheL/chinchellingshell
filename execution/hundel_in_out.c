/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundel_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:28:52 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/19 12:02:20 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inisialise_stdin_stdout(t_mp *pg)
{
	pg->stdin = dup(STDERR_FILENO);
	pg->stdout = dup(STDOUT_FILENO);
}



void	hundel_redirection(t_token	*token)
{
	int	fd;

	if (ft_strcmp(token->cmds[0], "<"))
	if (ft_strcmp(token->cmds[0], ">"))
	if (ft_strcmp(token->cmds[0], ">>"))
	if (ft_strcmp(token->cmds[0], "<<"))
		return ;
}