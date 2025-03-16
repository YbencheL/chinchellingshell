/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:51:57 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/16 17:27:50 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_args(int ac)
{
	if (ac != 1)
	{
		printf("\n\n");
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃                                           ┃\n");
		printf("┃        ");
		printf("       \033[1;31m⚠️\033[0m");
		printf(" \033[1;33mWARNING\033[0m");
		printf(" \033[1;31m⚠️\033[0m");
		printf("                 ┃\n");
		printf("┃                                           ┃\n");
		printf("┃  ");
		printf("\033[1;36mNo arguments allowed\033[0m");
		printf("                     ┃\n");
		printf("┃                                           ┃\n");
		printf("┃  Type: ");
		printf("\033[1;32m./minishell\033[0m");
		printf("                        ┃\n");
		printf("┃                                           ┃\n");
		printf("┃  Enjoy 😁                                 ┃\n");
		printf("┃                                           ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("\n\n");
		exit(1);
	}
}
