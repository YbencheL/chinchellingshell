/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:25:36 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/23 20:26:35 by ybenchel         ###   ########.fr       */
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
	while(tmp)
	{
		if(tmp->next && ft_strcmp(tmp->arg, "|") == 0 && ft_strcmp(tmp->next->arg, "|") == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
			return 0;
		}
		else if (ft_strcmp(tmp->arg, "|") == 0 && !tmp->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return 0;
		}
		else if (tmp->type <= 4 && tmp->type >= 2 && !tmp->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `redirection`\n", 2);
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}
char	*check_for_var(char *s, int *start)
{
	int		i;
	char	*str;
	
	i = *start + 1;
	while (s[i])
	{
		if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || (s[i] <= '9' && s[i] >= '0') || s[i] == '_')
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
	t_arg	*start;
	int		i;
	t_list	*vars;
	char	* str;
	
	vars = NULL;
	start = token;
	while (start)
	{
		i = 0;
		if (start->type == WORD)
		{
			while (start->arg[i])
			{
				if(start->arg[i] == '$')
				{				
					str = check_for_var(start->arg, &i);
					ft_lstadd_back(&vars, ft_lstnew(str));
				}
				else
					i++;
			}
		}
		start = start->next;
	}
	return vars;
}

// int    expand_variables(t_arg *token)
// {
// 	t_list	*var;
// 	t_list	*tmp;
// 	// char *getenv_v;
	
// 	var = checking_variables(token);
// 	tmp = var;
// 	while(tmp)
// 	{
// 		// Get the list of variables

// 		// You've already done this with var = checking_variables(token)
// 		// This gives you a list of all variables (like $HOME, $USER, etc.)
// 		// Create a replace_substring function
		
// 		// Takes original string, substring to replace, and replacement value
// 		// Returns a new string with all occurrences replaced
// 		// Create a replace_variables function
		
// 		// For each token containing variables:
// 		// Extract variable name (skip the $ character)
// 		// Get environment value using getenv()
// 		// Use replace_substring to swap the variable for its value
// 		// Process each token
		
// 		// Loop through all tokens
// 		// For each token of type WORD, check if it contains variables
// 		// Apply variable replacement where needed
// 		// Memory management
		
// 		// Allocate memory for new strings after replacement
// 		// Free original strings after replacement
// 		// Free the variable list when done
// 		// Special cases
		
// 		// Handle $? for exit status
// 		// Handle variables within quotes correctly
// 		// Handle non-existent variables (replace with empty string)
// 		tmp = tmp->next;
// 	}
// 	return 0;
// }
