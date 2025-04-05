/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:25:36 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/05 16:34:41 by abenzaho         ###   ########.fr       */
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
			|| (s[i] <= '9' && s[i] >= '0') || s[i] == '_' || s[i] == '?')
			i++;
		else
			break ;
	}
	str = ft_substr(s, *start + 1, i - *start - 1);
	*start = i;
	return (str);
}

char	*modify_str(char *s, char *var)
{
	char *str;
	char	*s1;
	
	str = getenv(var);
	if (!str)
		return (NULL);
	s1 = replace_var(s, var, str);
	return (s1);
}

t_list	*checking_variables(t_arg *token)
{
	t_arg	*start;
	int		i;
	t_list	*vars;
	char	*tmp;


	vars = NULL;
	start = token;
	while (start)
	{
		i = 0;
		if (start->type == WORD && start->arg[0] != '\'')
		{
			while (start->arg[i])
			{
				if (start->arg[i] == '$')
				{
					tmp = check_for_var(start->arg, &i);
					if (tmp)
					{
						start->arg = modify_str(start->arg, tmp);
						i = 0;
					}
				}
				else
					i++;
			}
		}
		start = start->next;
	}
	return (vars);
}
