/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expand_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:44:52 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/05 17:21:55 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*get_var(char *s, int start)
{
	int		i;
	char	*str;

	i = start;
	while (s[i])
	{
		if (ft_isdigit(s[i]) && start == i)
		{
			i++;
			break ;
		}
		else if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
			break ;
	}
	str = ft_substr(s, start, i - start);
	return (str);
}

char	*replace_var(char *s, char *var, char *value, int *k)
{
	int		len;
	char	*str;
	int		i;

	i = *k;
	len = ft_strlen(s) + ft_strlen(value) - ft_strlen(var) + 1;
	str = (char *)ft_malloc(sizeof(char) * (len));
	ft_strncpy(str, s, *k);
	ft_strncpy(str + *k, value, ft_strlen(value));
	*k = *k + ft_strlen(value);
	ft_strncpy(str + *k, s + i + ft_strlen(var), len - *k);
	return (str);
}

char	*expand(char *str, int *i, t_mp *pg)
{
	int		j;
	char	*var;
	char	*value;
	char	*s;

	var = NULL;
	value = NULL;
	j = *i + 1;
	if (str[j] == '?')
	{
		var = ft_strdup("$?");
		value = ft_itoa(pg->exit_status);
	}
	else
	{
		var = get_var(str, j);
		value =	my_getenv(pg->env, var);
		var = ft_strjoin(ft_strdup("$"), var);
	}
	if (!value)
		s = replace_var(str, var, ft_strdup(""), i);
	else
		s = replace_var(str, var, value, i);
	return (s);
}
