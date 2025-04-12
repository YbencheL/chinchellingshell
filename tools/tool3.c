/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:44:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/04/12 18:39:25 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = (size_t)ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len < len + start)
		len = s_len - start;
	str = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_arg	*new_arg(char *arg)
{
	t_arg	*new;

	new = (t_arg *)ft_malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->arg = arg;
	new->next = NULL;
	return (new);
}

void	argadd_back(t_arg **arg, t_arg *new)
{
	t_arg	*temp;

	if (!arg || !new)
		return ;
	if (!*arg)
	{
		*arg = new;
		return ;
	}
	temp = *arg;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
