/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:42:17 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/08 13:18:16 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_not_found(t_cmds *cmds, t_mp *pg)
{
	write(2, cmds->cmds[0], ft_strlen(cmds->cmds[0]));
	write(2, ": command not found\n", 20);
	close_files(cmds->files);
    restor_fd(pg->std_in, pg->std_out);
	ft_lstclear(&g_gbc, free);
	return (127);
}

void    child_procces(t_cmds *cmds, t_mp *pg)
{
	char	*cmd_dir;
	
	if (!cmds->cmds || !cmds->cmds[0] || !ft_strlen(cmds->cmds[0]))
	{
		close_files(cmds->files);
		exit(EXIT_SUCCESS);
	}
	cmd_dir = get_cmd_dir(cmds->cmds[0], pg);
	if (!cmd_dir)
		exit(cmd_not_found(cmds, pg));
	execve(cmd_dir, cmds->cmds, pg->envp);
	perror("execve");
    close_files(cmds->files);
    restor_fd(pg->std_in, pg->std_out);
	ft_lstclear(&g_gbc, free);
	exit(127);
}

void	execute_one_cmd(t_cmds *cmds, t_mp *pg)
{
	int	p_id;
	int	status;

	if (open_files_red(cmds->files))
	{
		pg->exit_status = 1;
		return ;
	}
	if (builtins(cmds, pg) == 0)// need to hundel exit status.
		return ;
	else
	{
		p_id = fork();
		if (p_id == 0)
			child_procces(cmds, pg);
		else if(p_id == -1)
		{
			perror("fork failed");
			pg->exit_status = 1;
			return ;
		}
	}
    waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		pg->exit_status = WEXITSTATUS(status);
}
