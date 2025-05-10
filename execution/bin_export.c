/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:11:22 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 13:44:27 by abenzaho         ###   ########.fr       */
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
int	check_form(char *s, int *es)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '=' || (s[i] == '+' && s[i + 1] == '=')) && i != 0)
			break;
		else if ((i == 0 && ft_isdigit(s[i])) || (!ft_isalnum(s[i]) && s[i] != '_'))
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

void	append_var(t_list *env, char *s)
{
	int		len;
	char	*var;

	len = 0;
	while (s[len] && s[len] != '+')
		len++;
	while (env)
	{
		if (!strncmp(env->ptr, s, len))
			break;
		env = env->next;
	}
	var = ft_strjoin(env->ptr, s + len + 2);
	env->ptr = var;
}

void	app_var(t_list *env, char *s)
{
	if (!check_exist(env, s))
		add_app_var(env, s);
	else
		append_var(env, s);	
}

void	add_var(t_list **env, char *s)
{
	t_list	*prv;
	t_list	*head;
	int	len;
	t_list	*new;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	prv = NULL;
	head = *env;
	if (!check_exist(*env, s))
	{
		ft_lstadd_back(env, ft_lstnew(s));
		return ;
	}
	else
	{
		while (*env)
		{
			
			if (!strncmp((*env)->ptr, s, len))
			{
				new = ft_lstnew(s);
				if (!prv)
				{
					head = new;
					new->next = (*env)->next;
				}
				else
				{
					prv->next = new;
					new = (*env)->next;	
				}
				break ;
			}
			prv = *env;
			*env = (*env)->next;
		}
	}
	*env = head;
}

void	export(t_cmds *cmds, t_list *env, t_mp *pg)
{
	int	i;
	int	mode;
	int	exit_st;
	
	i = 1;
	exit_st = 0;
	if (!cmds->cmds[1])
		print_env_dec(env);
	else
	{
		while (cmds->cmds[i])
		{
			mode = check_form(cmds->cmds[i], &exit_st);
			if (mode == 0)
				add_var(&env, cmds->cmds[i]);
			else if (mode == 2 && !check_exist(env, cmds->cmds[i]))
				ft_lstadd_back(&env, ft_lstnew(cmds->cmds[i]));
			else if (mode == 3)
				app_var(env, cmds->cmds[i]);
			i++;
		}
	}
	pg->exit_status = exit_st;
}
