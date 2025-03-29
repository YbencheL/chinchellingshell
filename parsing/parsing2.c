/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:25:36 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/29 16:47:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(char **str, t_arg **token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		argadd_back(token, new_arg(str[i]));
		i++;
	}
}

t_arg	*split_tokens(t_list *s)
{
	t_arg	*token;
	char	**str;

	token = NULL;
	while (s)
	{
		if (((char *)s->ptr)[0] != '\'' && ((char *)s->ptr)[0] != '"')
		{
			str = ft_split((char *)s->ptr);
			add_token(str, &token);
		}
		else
			argadd_back(&token, new_arg(s->ptr));
		s = s->next;
	}
	return (token);
}

int	error_slayer(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->arg, "|") == 0
			&& ft_strcmp(tmp->next->arg, "|") == 0)
		{
			ft_putstr_fd("minishell: syntax error, unexpected token`||'\n", 2);
			return (0);
		}
		if (ft_strcmp(tmp->arg, "|") == 0 && !tmp->next)
		{
			ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
			return (0);
		}
		if (tmp->type <= 4 && tmp->type >= 2 && !tmp->next)
		{
			ft_putstr_fd("minishell: syntax error, unexpected token "
				"`redirection`\n", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*check_for_var(char *s, int *start)
{
	int		i;
	char	*str;

	i = *start + 1;
	while (s[i])
	{
		if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')
			|| (s[i] <= '9' && s[i] >= '0') || s[i] == '_')
			i++;
		else
			break ;
	}
	str = ft_substr(s, *start, i - *start);
	*start = i;
	return (str);
}

t_list	*checking_variables(t_arg *token)
{
	t_arg		*start;
	int			i;
	t_list		*vars;

	vars = NULL;
	start = token;
	while (start)
	{
		i = 0;
		if (start->type == WORD)
		{
			while (start->arg[i])
			{
				if (start->arg[i] == '$')
					ft_lstadd_back(&vars,
						ft_lstnew(check_for_var(start->arg, &i)));
				else
					i++;
			}
		}
		start = start->next;
	}
	return (vars);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*search_env(char *var, t_mp *ev)
{
	int i = 0;
	char *new_var;
	char *equal_sign;
	int len;
	
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
				return equal_sign + 1;
		}
		i++;
	}
	return NULL;
}

char	*replace_var(char *token, char *var, char *value)
{
    char *new_string;
    char *var_pos;
    int var_len;
    int token_len;
    int value_len;
    int total_len;
    int before$_len;
    
    var_len = ft_strlen(var);
    value_len = ft_strlen(value);
    token_len = ft_strlen(token);
    var_pos = ft_strstr(token, var);
    if (!var_pos)
        return ft_strdup(token);
    before$_len = var_pos - token;
    total_len = token_len - var_len + value_len;
    new_string = ft_malloc(sizeof(char) * (total_len + 1));
    if (!new_string)
        allocation_fails();
    ft_strlcpy(new_string, token, before$_len + 1);
    ft_strcat(new_string, value);
    ft_strcat(new_string, var_pos + var_len);
    return new_string;
}

int    expand_variables(t_arg *token, t_mp *ev)
{
	t_list	*var;
	t_list	*tmp;
	t_arg	*current;
	char	*value;

	if (!(var = checking_variables(token)))
		return (0);
	tmp = var;
	while (tmp)
	{
		value = search_env(tmp->ptr, ev);
		if (!value)
			value = "";
		current = token;
		while (current)
		{
			printf("Token before: %s\n", current->arg);
			if (current->type == WORD && ft_strstr(current->arg, tmp->ptr))
				current->arg = replace_var(current->arg, tmp->ptr, value);
			printf("After replacement: %s\n", current->arg);
			current = current->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
