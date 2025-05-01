/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:45:13 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/01 18:17:45 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_file(t_file **fhead, t_file **files, t_file *tmp)
{
	if (!*fhead)
	{
		*fhead = tmp;
		*files = tmp;
	}
	else
	{
		(*files)->next = tmp;
		*files = (*files)->next;
	}
}

t_file	*get_file(t_token **token)
{
	t_file	*files;
	t_file	*fhead;
	t_file	*tmp;

	files = NULL;
	fhead = NULL;
	while (*token && (*token)->type != PIPELINE)
	{
		if ((*token)->type == REDIRECTION)
		{
			tmp = (t_file *)ft_malloc(sizeof(t_file));
			tmp->file = (*token)->cmds[1];
			handle_file_type(tmp, (*token)->cmds[0]);
			tmp->next = NULL;
			append_file(&fhead, &files, tmp);
		}
		*token = (*token)->next;
	}
	return (fhead);
}

int	count_cmd_words(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD)
			i += ft_pcounter(token->cmds);
		token = token->next;
	}
	return (i);
}

char	**get_cmd(t_token *token)
{
	t_token	*head;
	int		i;
	int		j;
	char	**cmds;

	head = token;
	i = count_cmd_words(token);
	token = head;
	cmds = (char **)ft_malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD)
		{
			i = 0;
			while (token->cmds[i])
				cmds[j++] = token->cmds[i++];
		}
		token = token->next;
	}
	cmds[j] = NULL;
	return (cmds);
}

t_cmds	*get_final_cmds(t_token *token)
{
	t_cmds	*cmds;
	t_cmds	*head;
	t_cmds	*tmp;

	head = NULL;
	while (token)
	{
		tmp = (t_cmds *)ft_malloc(sizeof(t_cmds));
		inisialise_cmds(tmp);
		tmp->cmds = get_cmd(token);
		tmp->files = get_file(&token);
		if (!head)
		{
			head = tmp;
			cmds = tmp;
		}
		else
		{
			cmds->next = tmp;
			cmds = cmds->next;
		}
		if (token)
			token = token->next;
	}
	return (head);
}
