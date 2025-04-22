/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:45:13 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/22 16:36:56 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inisialise_cmds(t_cmds *cmd)
{
	cmd->cmds = NULL;
	cmd->files =NULL;
	cmd->next = NULL;
}
void	handle_file_type(t_file *file, char *s)
{
	if (!ft_strcmp(s, ">>"))
		file->type = RED_APPEND;
	else if(!ft_strcmp(s, "<<"))
		file->type = HEREDOC;
	else if(!ft_strcmp(s, "<"))
		file->type = RED_IN;
	else if(!ft_strcmp(s, ">"))
		file->type = RED_OUT;
	file->fd = 0;
}

t_file	*get_file(t_token **token)
{
	t_token	*head;
	t_file	*files;
	t_file	*fhead;
	t_file	*tmp;

	head = *token;
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
			if (!fhead)
			{
				fhead = tmp;
				files = tmp;
			}
			else 
			{
				files->next = tmp;
				files = files->next;
			}
		}
		*token = (*token)->next;
	}
	return (fhead);
}

char	**get_cmd(t_token *token)
{
	t_token	*head;
	int		i;
	int		j;
	char	**cmds;

	i = 0;
	j = 0;
	head = token;
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD)
			i = i + ft_pcounter(token->cmds);
		token = token->next;
	}
	token = head;
	cmds = (char **)ft_malloc(sizeof(char *) * (i + 1));
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD)
		{
			i = 0;
			while (token->cmds[i])
			{
				cmds[j] = token->cmds[i];
				j++;
				i++;
			}
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
