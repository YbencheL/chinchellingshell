/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:11:22 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 18:28:32 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export_err(char *s)
{
	write(2, "minishell : export : ", 21);
	write(2, s, ft_strlen(s));
	write(2, ": not a valid identifier\n", 24);
}

void	print_env_dec(t_list *env)
{
	while(env)
	{
		printf("declare -x %s\n", (char *)(env->ptr));
		env = env->next;
	}
}
int	check_form(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && i != 0)
			break;
		else if ((i == 0 && ft_isdigit(s[i])) || (!ft_isalnum(s[i]) && s[i] != '_') || s[i + 1] == '\0')
		{
			print_export_err(s);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_cmds *cmds, t_list *env)
{
	int	i;
	int	exit_st;
	
	i = 1;
	exit_st = 0;
	if (!cmds->cmds[1])
		print_env_dec(env);
	else
	{
		while (cmds->cmds[i])
		{
			if (!check_form(cmds->cmds[i]))
				ft_lstadd_back(&env, ft_lstnew(cmds->cmds[i]));
			else
				exit_st = 1;
			i++;
		}
	}
	return (exit_st);
}
