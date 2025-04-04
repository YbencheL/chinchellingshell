/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:50:55 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/05 16:35:10 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_env(char *var, t_mp *ev)
{
	int		i;
	char	*new_var;
	char	*equal_sign;
	int		len;

	i = 0;
	new_var = ft_malloc(sizeof(char) * (ft_strlen(&var[1]) + 2));
	if (!new_var)
		allocation_fails();
	ft_strlcpy(new_var, &var[1], ft_strlen(&var[1]) + 1);
	len = ft_strlen(new_var);
	new_var[len] = '=';
	new_var[len + 1] = '\0';
	while (ev->envp[i])
	{
		if (ft_strncmp(ev->envp[i], new_var, ft_strlen(new_var)) == 0)
		{
			equal_sign = ft_strchr(ev->envp[i], '=');
			if (equal_sign)
				return (equal_sign + 1);
		}
		i++;
	}
	return (NULL);
}

char	*replace_var(char *token, char *var, char *value)
{
	char	*new_string;
	char	*var_pos;
	int		before_var_len;
	int		total_len;

	var_pos = ft_strstr(token, var);
	if (!var_pos)
		return (ft_strdup(token));
	before_var_len = var_pos - token;
	total_len = ft_strlen(token) - ft_strlen(var) + ft_strlen(value);
	new_string = ft_malloc(sizeof(char) * (total_len + 1));
	if (!new_string)
		allocation_fails();
	ft_strlcpy(new_string, token, before_var_len);
	ft_strcat(new_string, value);
	ft_strcat(new_string, var_pos + ft_strlen(var));
	return (new_string);
}

char	*get_variable_value(char *var_name, t_mp *ev)
{
	char	*exit_status;
	char	*value;

	if (!ft_strcmp(var_name, "$?"))
	{
		exit_status = ft_itoa(ev->exit_status);
		if (!exit_status)
			allocation_fails();
		return (exit_status);
	}
	else
	{
		value = search_env(var_name, ev);
		if (value)
			return (value);
		else
			return ("");
	}
}

int	expand_variables(t_arg *token, t_mp *ev)
{
	t_list	*var;
	t_list	*tmp;
	t_arg	*current;
	char	*value;

	var = checking_variables(token);
	if (!var)
		return (0);
	tmp = var;
	while (tmp)
	{
		value = get_variable_value(tmp->ptr, ev);
		current = token;
		while (current)
		{
			if (current->type == WORD && ft_strstr(current->arg, tmp->ptr))
				current->arg = replace_var(current->arg, tmp->ptr, value);
			current = current->next;
		}
		tmp = tmp->next;
	}
	return (0);
}


// t_cmd	*parse_tokens(t_token	*tokens)
// {
// 	//cmd
// }