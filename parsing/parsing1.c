/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:51:57 by ybenchel          #+#    #+#             */
/*   Updated: 2025/03/18 15:19:9:06 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		exit (1);
	}
}

void	herdock_detected(void)
{
	printf("herdock_detect\n");
}

char	*extract_phrase(char *s, int *start, char c)
{
	int	i;
	int	j;
	char *str = NULL;

	i = -1;
	j = *start;
	while (s[j])
	{
		if (s[j] == c)
			i++;
		if (s[j] == c && i == 1)
			break ;
		j++;
	}
	printf("i%i *start%i j%i\n", i, *start, j);
	if (i == 1)
	{
		str = (char *)malloc(sizeof(char) * ((j - *start) + 2));
		ft_memcpy(str, s + *start, j - *start + 1);
		*start = j;
		printf("i%i *start%i\n", i, *start);
		//printf("%s\n", str);
		return (str);
	}
	return (NULL);
}

t_list	*split_phrase(char *s)
{
	int	i;
	t_list	*phrase;
	char *str;

	i = 0;
	phrase = (t_list *)malloc(sizeof(t_list *));
	while (s[i])
	{
		if (s[i] == '"')
		{
			str = extract_phrase(s, &i, '"');
			if (!str)
				herdock_detected();
			//else
			//	ft_lstadd_back(&phrase, ft_lstnew(str));
			printf("%s\n", str);
		}
		if (s[i] == '\'')
		{
			str = extract_phrase(s, &i, '\'');
			if (!str)
				herdock_detected();
			//else
			//	ft_lstadd_back(&phrase, ft_lstnew(str));
			printf("%s\n", str);
		}
		i++;
	}
	return (phrase);
}
/*we still need to hundle word outside the quotes 
get the linked list we creat splited and take it inside the token list while identifyinh it type*/