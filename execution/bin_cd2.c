/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:45:43 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:46:32 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_error(t_mp *pg, char *msg, int status)
{
	write(2, "minishell cd: ", 14);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	pg->exit_status = status;
}
