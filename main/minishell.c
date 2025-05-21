/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:13:52 by ybenchel          #+#    #+#             */
/*   Updated: 2025/05/15 13:48:43 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*g_gbc;

void	execution(t_cmds *cmds, t_mp *pg)
{
	int		cmd_count;
	t_cmds	*cmd_ptr;

	if (fill_herdoc(cmds, pg))
		return ;
	cmd_ptr = cmds;
	cmd_count = 0;
	while (cmd_ptr)
	{
		cmd_count++;
		cmd_ptr = cmd_ptr->next;
	}
	if (cmd_count == 1)
	{
		execute_one_cmd(cmds, pg);
		close_files(cmds->files);
		restor_fd(pg->std_in, pg->std_out);
	}
	else
	{
		execute_multiple_commands(cmds, cmd_count, pg);
		restor_fd(pg->std_in, pg->std_out);
	}
	return ;
}

t_cmds	*parsing(char *rl, t_mp *pg)
{
	t_arg	*token;
	t_token	*tokens;
	t_cmds	*cmds;

	if (!check_unclosed_quotes(rl, pg))
		return (NULL);
	token = tokenize(rl, pg);
	expand_variables(token, pg);
	handle_var_space(&token);
	if (check_files_red_err(token))
		return (NULL);
	skip_null(&token);
	if (!token)
		return (NULL);
	tokens = tokens_to_cmds(token);
	cmds = get_final_cmds(tokens);
	if (check_files(cmds, pg))
		return (NULL);
	remove_quotes(cmds);
	getback_quotes(cmds);
	return (cmds);
}

void	shell_loop(t_mp *pg)
{
	char	*rl;
	t_cmds	*cmds;

	while (1)
	{
		rl = readline("Minishell$ ");
		if (!rl)
			return ;
		if (ft_strlen(rl))
		{
			add_history(rl);
			cmds = parsing(rl, pg);
			if (!cmds)
				continue ;
			execution(cmds, pg);
			update_env(pg);
			pg->envs = sort_env(pg->envp);
		}
		free(rl);
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mp	pg;

	pg.exit_status = 0;
	pg.is_child = 0;
	g_gbc = ft_lstnew_custom(NULL);
	check_args(ac, av);
	pg.env = init_env(env);
	pg.envp = env;
	pwd_shvl(&pg);
	pg.envs = sort_env(pg.envp);
	print_banner();
	signal_setup();
	in_n_out_backup(&pg);
	shell_loop(&pg);
	print_exit();
	close(pg.std_in);
	close(pg.std_out);
	ft_lstclear(&g_gbc, free);
}
