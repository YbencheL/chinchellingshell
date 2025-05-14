/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/14 14:04:38 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DQUOTE -1
# define SQUOTE -2

# include "utils.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef enum token_type
{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
}					t_token_type;

typedef enum t_type
{
	CMD,
	REDIRECTION,
	PIPELINE,
}					t_type;

typedef struct s_arg
{
	char			*arg;
	t_token_type	type;
	struct s_arg	*next;
}					t_arg;

typedef struct s_token
{
	char			**cmds;
	t_type			type;
	int				heredoc;
	struct s_token	*next;
}					t_token;

typedef struct s_file
{
	char			*file;
	t_token_type	type;
	int				fd;
	struct s_file	*next;
}					t_file;

typedef struct s_cmds
{
	char			**cmds;
	t_file			*files;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_mp
{
	t_list			*env;
	char			**envp;
	char			**envs;
	int				std_in;
	int				std_out;
	int				exit_status;
	int				is_child;
}					t_mp;

extern t_list		*g_gbc;

////////////////////----parsing----////////////////////

int					check_unclosed_quotes(char *s, t_mp *pg);
t_arg				*tokenize(char *line, t_mp *pg);
t_token				*tokens_to_cmds(t_arg *tokens);
void				expand_variables(t_arg *token, t_mp *pg);
void				handle_var_space(t_arg **token);
t_cmds				*get_final_cmds(t_token *token);
char				*expand(char *str, int *i, t_mp *pg);
void				inisialise_cmds(t_cmds *cmd);
void				handle_file_type(t_file *file, char *s);
void				remove_quotes(t_cmds *cmds);
char				*quote_remover(char *s);
int					check_files(t_cmds *cmds, t_mp *pg);
char				*expand_q(char *str, int *i, t_mp *pg);
void				getback_quotes(t_cmds *cmd);
void				skip_null(t_arg **token);
void				pwd_shvl(t_mp *pg);

////////////////////-----tools-----////////////////////

void				*ft_malloc(size_t size);
t_list				*init_env(char **envp);
void				check_args(int ac, char **av);
void				allocation_fails(void);
void				signal_setup(void);
void				print_banner(void);
void				print_exit(void);
char				**split_token(char *s);
t_arg				*new_arg(char *arg);
void				argadd_back(t_arg **arg, t_arg *new);
char				**split_only_spaces(char *s);
void				fill_split(char **str, char *s);
int					word_counter(char *s);
char				**split_token(char *s);
int					is_delimiter(char c);
int					is_special_char(char c);
char				*my_getenv(t_list *env, char *name);
void				skip_quotes(char *s, int *i, char c);
int					is_delimiter(char c);
int					is_special_char(char c);
int					word_counter(char *s);
void				close_files(t_file *files);
char				**sort_env(char **env);

////////////////////-----execution-----////////////////////

int					fill_herdoc(t_cmds *cmds, t_mp *pg);
void				dup_in(int fd);
void				dup_out(int fd);
void				in_n_out_backup(t_mp *pg);
int					check_redirection(t_file *files);
void				restor_fd(int stdin_b, int stdout_b);
char				*get_cmd_dir(char *cmd, t_mp *pg);
void				pwd(t_mp *pg);
void				cd(t_cmds *cmds, t_mp *pg);
void				export(t_cmds *cmds, t_list *env, t_mp *pg);
void				print_env(t_list *env);
int					env(t_cmds *cmds, t_list *env, t_mp *pg);
void				unset(t_cmds *cmds, t_list *env, t_mp *pg);
int					open_files_red(t_file *files);
void				echo(t_cmds *cmds, t_mp *pg);
void				execute_one_cmd(t_cmds *cmds, t_mp *pg);
int					builtins(t_cmds *cmds, t_mp *pg);
void				bin_exit(t_cmds *cmds, t_mp *pg);
void				execute_multiple_commands(t_cmds *cmds, int cmd_count,
						t_mp *pg);
void				update_env(t_mp *pg);
void				cd_error(t_mp *pg, char *msg, int status);
void				print_env_dec(char **env);
void				print_export_err(char *s);
void				add_app_var(t_list *env, char *s);
int					check_exist(t_list *env, char *s);
int					check_form(char *s, int *es);
void				add_var(t_list **env, char *s);
int					check_files_red_err(t_arg *token);
void				finalizing_exit_st(t_mp *pg, int *status);

#endif