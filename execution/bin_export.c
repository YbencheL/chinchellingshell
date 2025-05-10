/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:11:22 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/10 15:54:41 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			break ;
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

void	update_existing_var(t_list **env, t_list **prv, char *s, int len)
{
	t_list	*new;

	while (*env)
	{
		if (!strncmp((*env)->ptr, s, len))
		{
			new = ft_lstnew(s);
			if (!*prv)
			{
				new->next = (*env)->next;
				*env = new;
			}
			else
			{
				(*prv)->next = new;
				new->next = (*env)->next;
			}
			return ;
		}
		*prv = *env;
		*env = (*env)->next;
	}
}

void	add_var(t_list **env, char *s)
{
	t_list	*prv;
	t_list	*head;
	int		len;

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
	update_existing_var(env, &prv, s, len);
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
