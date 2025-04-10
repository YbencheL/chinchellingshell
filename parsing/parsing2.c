/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:25:36 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/10 19:47:41 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (RED_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (RED_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (RED_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else
		return (WORD);
}

int	check_syntaxe(t_arg *arg)
{
	if (arg->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
		return (0);
	}
	while (arg)
	{
		if (arg->type == PIPE)
		{
			if (!arg->next)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
				return (0);
			}
			else if (arg->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token`||'\n", 2);
				return (0);
			}
		}
		else if (arg->type <= 5 && arg->type >= 2)
		{
			if (!arg->next)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token `redirection`\n", 2);
				return (0);
			}
			else if (arg->next->type != WORD)
			{
				ft_putstr_fd("minishell: syntax error, unexpected token `redirection`\n", 2);
				return (0);
			}
		}
		arg = arg->next;
	}
	return (1);
}

int	typeof_token(t_arg *arg, t_mp *pg)
{
	t_arg	*head;

	head = arg;
	while (head)
	{
		head->type = token_type(head->arg);
		head = head->next;
	}
	if (!check_syntaxe(arg))
	{
		pg->exit_status = 2;
		return (0);
	}
	return (1);
}

void	replace_var(t_arg *token, char *var, char *value, int *k)
{
	int		len;
	char	*str;
	int		j;
	int		i;
	int		s;

	j = 0;
	len = ft_strlen(token->arg) + ft_strlen(value) - ft_strlen(var) + 1;
	str = (char *)ft_malloc(sizeof(char) * (len));
	while (j < *k)
	{
		str[j] = token->arg[j];
		j++;
	}
	s = j;
	i = 0;
	while (value[i])
	{
		str[j] = value[i];
		i++;
		j++;
	}
	*k = j;
	i = j;
	j = s + ft_strlen(var);
	while(token->arg[j])
	{
		str[i] = token->arg[j];
		j++;
		i++;
	}
	str[i] = '\0';
	token->arg = str;
}

char	*get_var(char *s, int start)
{
	int i;
	char *str;

	i = start;
	while (s[i])
	{
		if (ft_isdigit(s[i]) && start == i)
		{
			i++;
			break;
		}
		else if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
			break;
	}
	str = ft_substr(s, start, i - start);
	printf("%s--->",str);
	return (str);
}

char	*expand(t_arg *token, int *i, t_mp *pg)
{
	int		j;
	char	*var;
	char	*value;

	var = NULL;
	value = NULL;
	j = *i + 1;
	if (token->arg[j] == '?')
	{
		var = ft_strdup("$?");
		value = ft_itoa(pg->exit_status);
	}
	else
	{
		var = get_var(token->arg, j);
		value = getenv(var);
		var = ft_strjoin(ft_strdup("$") , var);
	}
	if (!value)
	 	replace_var(token, var, ft_strdup(""), i);
	else	
		replace_var(token, var, value, i);
	return (NULL);
}

void	hundel_quotes_var(t_arg **token, int *i, t_mp *pg)
{
	int	j;

	if ((*token)->arg[*i] != '\'')
	{
		j = *i + 1; 
		while ((*token)->arg[j])
		{
			if ((*token)->arg[j] == '$' && (ft_isalnum((*token)->arg[j + 1]) || (*token)->arg[j + 1] == '_' || (*token)->arg[j + 1] == '?'))
					expand(*token, &j, pg);
			else if ((*token)->arg[j] == '"')
			{
				j++;
				break;
			}
			else
				j++;
		}
	}
	else
	{
		j = *i + 1;
		while ((*token)->arg[j])
		{
			if ((*token)->arg[j] == '\'')
			{
				j++;
				break;
			}
			j++;	
		}
	}
	*i = j;
}

void	expand_variables(t_arg *token, t_mp *pg)
{
	int	i;
	t_arg *head;
	head = token;
	while (token)
	{	
		i = 0;
		while (token->arg[i])
		{
			if (token->arg[i] == '"' || token->arg[i] == '\'')
				hundel_quotes_var(&token, &i, pg);
			// else if ()
			// {
				
			// }
			else
				i++;
		}
		token = token->next;
	}
}

// t_arg *split_tokens(t_lst *s)
// {
// 	t_arg *token;
// 	char **str;
// 	t_arg *last;
// 	int space;

// 	token = NULL;
// 	last = NULL;
// 	space = 0;
// 	while (s)
// 	{
// 		if (last != NULL && space == 0 &&
// 			last->arg[0] != '|' && last->arg[0] != '<' && last->arg[0] != '>')
// 			last->arg = ft_strjoin(last->arg, (char *)(s->ptr));
// 		else if (((char *)s->ptr)[0] != '\'' && ((char *)s->ptr)[0] != '"')
// 		{
// 			str = ft_split((char *)s->ptr);
// 			add_token(str, &token);
// 		}
// 		else
// 			argadd_back(&token, new_arg(s->ptr));
// 		space = s->is;
// 		s = s->next;
// 		last = ft_arglast(token);
// 	}
// 	return (token);
// }

// int error_slayer(t_arg *arg, t_mp *pg)
// {
// 	t_arg *tmp;

// 	tmp = arg;
// 	while (tmp)
// 	{
// 		if (tmp->next && ft_strcmp(tmp->arg, "|") == 0 && ft_strcmp(tmp->next->arg, "|") == 0)
// 		{
// 			ft_putstr_fd("minishell: syntax error, unexpected token`||'\n", 2);
// 			pg->exit_status = 2;
// 			return (0);
// 		}
// 		if (ft_strcmp(tmp->arg, "|") == 0 && !tmp->next)
// 		{
// 			ft_putstr_fd("minishell: syntax error, unexpected token`|'\n", 2);
// 			pg->exit_status = 2;
// 			return (0);
// 		}
// 		if (tmp->type <= 4 && tmp->type >= 2 && !tmp->next)
// 		{
// 			ft_putstr_fd("minishell: syntax error, unexpected token "
// 						 "`redirection`\n",
// 						 2);
// 			pg->exit_status = 2;
// 			return (0);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

// char *check_for_var(char *s, int *start)
// {
// 	int i;
// 	char *str;

// 	i = *start + 1;
// 	while (s[i])
// 	{
// 		if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || (s[i] <= '9' && s[i] >= '0') || s[i] == '_' || s[i] == '?')
// 			i++;
// 		else
// 			break;
// 	}
// 	str = ft_substr(s, *start + 1, i - *start - 1);
// 	*start = i;
// 	return (str);
// }

// char *modify_str(char *s, char *var, t_mp *pg)
// {
// 	char *str;
// 	char *s1;

// 	if (!ft_strcmp(var, "?"))
// 		str = ft_strdup(ft_itoa(pg->exit_status));
// 	else
// 		str = getenv(var);
// 	if (!str)
// 		return (s);
// 	s1 = replace_var(s, var, str);
// 	return (s1);
// }

// t_list *checking_variables(t_arg *token, t_mp *pg)
// {
// 	t_arg *start;
// 	int i;
// 	t_list *vars;
// 	char *tmp;

// 	vars = NULL;
// 	start = token;
// 	while (start)
// 	{
// 		i = 0;
// 		if (start->type == WORD && start->arg[0] != '\'')
// 		{
// 			while (start->arg[i])
// 			{
// 				if (start->arg[i] == '$')
// 				{
// 					tmp = check_for_var(start->arg, &i);
// 					if (tmp)
// 						start->arg = modify_str(start->arg, tmp, pg);
// 				}
// 				else
// 					i++;
// 			}
// 		}
// 		start = start->next;
// 	}
// 	return (vars);
// }
