/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multip_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:07:10 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/13 14:10:45 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe_fds(int *pipe_fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
		close(pipe_fds[i++]);
}

void	setup_child_pipes(int *pipe_fds, int i, int cmd_count)
{
	if (i > 0)
		dup_in(pipe_fds[(i - 1) * 2]);
	if (i < cmd_count - 1)
		dup_out(pipe_fds[i * 2 + 1]);
	close_pipe_fds(pipe_fds, (cmd_count - 1) * 2);
}

void	execute_child_cmd(t_cmds *current, t_mp *pg)
{
	char	*cmd_dir;

	if (open_files_red(current->files))
		exit(EXIT_FAILURE);
	if (!current->cmds || !current->cmds[0])
		exit(EXIT_SUCCESS);
	if (builtins(current, pg) == 0)
		exit(pg->exit_status);
	cmd_dir = get_cmd_dir(current->cmds[0], pg);
	execve(cmd_dir, current->cmds, pg->envp);
	perror("execve error");
	exit(EXIT_FAILURE);
}

static void	wait_for_children(pid_t *pids, int cmd_count, t_mp *pg)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (i < cmd_count)
		waitpid(pids[i++], &status, 0);
	signal_setup();
	finalizing_exit_st(pg, &status);
}

void	execute_multiple_commands(t_cmds *cmds, int cmd_count, t_mp *pg)
{
	t_cmds	*current;
	int		*pipe_fds;
	pid_t	*pids;
	int		i;

	current = cmds;
	pipe_fds = (int *)ft_malloc(sizeof(int) * (2 * (cmd_count - 1)));
	pids = (pid_t *)ft_malloc(sizeof(pid_t) * cmd_count);
	i = 0;
	while (i < cmd_count - 1 && pipe(pipe_fds + i * 2) != -1)
		i++;
	i = 0;
	while (current && i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i++] == 0)
		{
			pg->is_child = 1;
			setup_child_pipes(pipe_fds, i - 1, cmd_count);
			execute_child_cmd(current, pg);
		}
		current = current->next;
	}
	close_pipe_fds(pipe_fds, (cmd_count - 1) * 2);
	wait_for_children(pids, cmd_count, pg);
}
