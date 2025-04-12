/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:48:31 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/12 17:53:22 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_banner(void)
{
	printf("\033[2K\r");
	printf("\033[1;32m");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗"
		"██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝"
		"██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗"
		"███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██"
		"║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║"
		"██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝"
		"╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0m");
}

void	print_exit(void)
{
	printf("\033[2K\r");
	printf("\033[1;32m");
	printf("███████╗██╗  ██╗██╗████████╗\n");
	printf("██╔════╝╚██╗██╔╝██║╚══██╔══╝\n");
	printf("█████╗   ╚███╔╝ ██║   ██║   \n");
	printf("██╔══╝   ██╔██╗ ██║   ██║   \n");
	printf("███████╗██╔╝ ██╗██║   ██║   \n");
	printf("╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝    \n");
	printf("\033[0m");
}

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("\n\n");
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃                                           ┃\n");
		printf("┃        ");
		printf("       \033[1;31m⚠️  WARNING\033[0m");
		printf(" \033[1;31m⚠️\033[0m");
		printf("                ┃\n");
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

void	*ft_malloc(size_t size)
{
	void	*ptr;
	t_list	*tmp;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error : malloc fail to allocate", 2);
		ft_lstclear(&g_gbc, free);
		exit(1);
	}
	tmp = ft_lstnew_custom(ptr);
	if (!tmp)
	{
		ft_putstr_fd("Error : malloc fail to allocate", 2);
		free(ptr);
		ft_lstclear(&g_gbc, free);
		exit(1);
	}
	ft_lstadd_back(&g_gbc, tmp);
	return (ptr);
}
