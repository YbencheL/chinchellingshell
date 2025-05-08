/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_multip_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:07:10 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/08 11:28:21 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void close_pipe_fds(int *pipe_fds, int count) 
{
	int i = 0;
	while (i < count)
		close(pipe_fds[i++]);
}

void setup_child_pipes(int *pipe_fds, int i, int cmd_count) 
{
	if (i > 0)
		dup_in(pipe_fds[(i - 1) * 2]);
	if (i < cmd_count - 1)
		dup_out(pipe_fds[i * 2 + 1]);
	close_pipe_fds(pipe_fds, (cmd_count - 1) * 2);
}

void execute_child_cmd(t_cmds *current, t_mp *pg) 
{
	char *cmd_dir;

	if (open_files_red(current->files))
		exit(EXIT_FAILURE);
	if (!current->cmds || !current->cmds[0])
		exit(EXIT_SUCCESS);
	if (builtins(current, pg) == 0)
		exit(0);
	cmd_dir = get_cmd_dir(current->cmds[0], pg);
	execve(cmd_dir, current->cmds, pg->envp);
	perror("execve error");
	exit(EXIT_FAILURE);
}

void execute_multiple_commands(t_cmds *cmds, int cmd_count, t_mp *pg)
{
	t_cmds *current = cmds;
	int pipe_fds[2 * (cmd_count - 1)];
	pid_t pids[cmd_count];
	int i = 0, status;

	while (i < cmd_count - 1 && pipe(pipe_fds + i++ * 2) != -1);
	i = 0;
	while (current && i < cmd_count)
	{
		if ((pids[i] = fork()) == 0) {
			pg->is_child = 1;
			setup_child_pipes(pipe_fds, i, cmd_count);
			execute_child_cmd(current, pg);
		}
		current = current->next;
		i++;
	}
	close_pipe_fds(pipe_fds, (cmd_count - 1) * 2);
	i = 0;
	while (i < cmd_count) 
		if (waitpid(pids[i++], &status, 0) > 0 && WIFEXITED(status))
			pg->exit_status = WEXITSTATUS(status);
}
