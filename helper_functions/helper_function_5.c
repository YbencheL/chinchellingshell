/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:30:54 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst	*ft_lstnew_space(void *ptr, int is)
{
	t_lst	*new_node;

	new_node = (t_lst *)ft_malloc(sizeof(t_lst));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	new_node->is = is;
	return (new_node);
}

void	ft_lstadd_back_space(t_lst **lst, t_lst *new)
{
	t_lst	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		allocation_fails();
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9'
			&& c >= '0'))
		return (1);
	return (0);
}

char	*bc_strchr_fo_rv(const char *s, char c, char l)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c && s[i] != l)
		i++;
	if (s[i] == c || s[i] == l)
		i++;
	str = (char *)ft_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
		if (s[i] == c || s[i] == l)
			break ;
	}
	str[i] = '\0';
	return (str);
}
