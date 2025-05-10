/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:50:34 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:54:11 by abenzaho         ###   ########.fr       */
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
	while (env)
	{
		printf("declare -x %s\n", (char *)(env->ptr));
		env = env->next;
	}
}

int	check_form(char *s, int *es)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
			&& i != 0)
			break ;
		else if ((i == 0 && ft_isdigit(s[i]))
			|| (!ft_isalnum(s[i]) && s[i] != '_'))
		{
			print_export_err(s);
			*es = 1;
			return (1);
		}
		i++;
	}
	*es = 0;
	if (s[i] == '\0')
		return (2);
	else if (s[i] == '+')
		return (3);
	return (0);
}

int	check_exist(t_list *env, char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '+' && s[len] != '=')
		len++;
	while (env)
	{
		if (!strncmp(env->ptr, s, len))
			return (1);
		env = env->next;
	}
	return (0);
}

void	add_app_var(t_list *env, char *s)
{
	int		len;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	var = (char *)ft_malloc(sizeof(char) * len);
	while (s[i] && s[i] != '+')
		var[j++] = s[i++];
	i++;
	while (s[i])
		var[j++] = s[i++];
	var[j] = '\0';
	ft_lstadd_back(&env, ft_lstnew(var));
}
