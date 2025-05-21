/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:42:17 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 18:10:58 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	finalizing_exit_st(t_mp *pg, int *status)
{
	if (WIFSIGNALED(*status))
	{
		pg->exit_status = WTERMSIG(*status) + 128;
		if (WTERMSIG(*status) == SIGINT
			|| WTERMSIG(*status) == SIGQUIT)
			write(1, "\n", 1);
	}
	if (WIFEXITED(*status))
		pg->exit_status = WEXITSTATUS(*status);
}

int	cmd_not_found(t_cmds *cmds, t_mp *pg)
{
	close_files(cmds->files);
	restor_fd(pg->std_in, pg->std_out);
	ft_lstclear(&g_gbc, free);
	return (pg->exit_status);
}

static void	fork_error(t_mp *pg)
{
	perror("fork failed");
	pg->exit_status = 1;
}

void	child_procces(t_cmds *cmds, t_mp *pg)
{
	char	*cmd_dir;

	signal(SIGQUIT, SIG_DFL);
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
	if (builtins(cmds, pg) == 0)
		return ;
	p_id = fork();
	if (p_id == -1)
		return (fork_error(pg));
	if (p_id == 0)
		child_procces(cmds, pg);
	signal(SIGINT, SIG_IGN);
	waitpid(p_id, &status, 0);
	signal_setup();
	finalizing_exit_st(pg, &status);
}
