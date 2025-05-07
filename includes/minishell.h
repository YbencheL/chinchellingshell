/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/07 12:53:17 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef enum token_type
{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	WORD2
}	t_token_type;

typedef enum t_type
{
	CMD,
	REDIRECTION,
	PIPELINE,
}	t_type;

typedef struct s_arg
{
	char			*arg;
	t_token_type	type;
	struct s_arg	*next;
}	t_arg;

typedef struct s_token
{
	char			**cmds;
	t_type			type;
	int				heredoc;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char			*file;
	t_token_type	type;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmds
{
	char			**cmds;
	t_file			*files;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_mp
{
	t_list	*env;
	char	**envp;
	int		std_in;
	int		std_out;
	int		exit_status;
}	t_mp;

extern t_list	*g_gbc;

////////////////////----parsing----////////////////////

int		check_unclosed_quotes(char *s, t_mp *pg);
t_arg	*tokenize(char *line, t_mp *pg);
t_token	*tokens_to_cmds(t_arg *tokens);
void	expand_variables(t_arg *token, t_mp *pg);
void	handle_var_space(t_arg **token);
t_cmds	*get_final_cmds(t_token *token);
char	*expand(char *str, int *i, t_mp *pg);
void	inisialise_cmds(t_cmds *cmd);
void	handle_file_type(t_file *file, char *s);

////////////////////-----tools-----////////////////////

void	*ft_malloc(size_t size);
t_list	*init_env(char **envp);
void	check_args(int ac, char **av);
void	allocation_fails(void);
void	signal_setup(void);
void	print_banner(void);
void	print_exit(void);
char	**split_token(char *s);
t_arg	*new_arg(char *arg);
void	argadd_back(t_arg **arg, t_arg *new);
char	**split_only_spaces(char *s);
void	fill_split(char **str, char *s);
int		word_counter(char *s);
char	**split_token(char *s);
int		is_delimiter(char c);
int		is_special_char(char c);
char	*my_getenv(t_list *env, char *name);
void	skip_quotes(char *s, int *i, char c);
// void	check_args(int ac, char **av);
// void	*ft_malloc(size_t size);
// void	print_banner(void);
// void	print_exit(void);
// char	**init_env(char **envp);
// void	allocation_fails(void);
// void	sig_handler(int sig);
// void	signal_setup(void);
// int		is_delimiter(char c);
// int		is_special_char(char c);
// size_t	count_splits(char const *s);
// size_t	get_word_len(const char *s);

// void	typeof_token(t_arg	*arg);
// char	**process_splits(char const *s, char **split);
// int		handle_special_chars(char const **s, char **split, size_t *i);
// int		handle_words(char const **s, char **split, size_t *i);
// t_arg	*ft_arglast(t_arg *lst);

////////////////////-----execution-----////////////////////

void	check_herdoc(t_file *files);
int		fill_herdoc(t_cmds *cmds, t_mp *pg);
void	dup_in(int fd);
void	dup_out(int fd);
void	in_n_out_backup(t_mp *pg);
int		check_redirection(t_file *files);
void	restor_fd(int stdin_b, int stdout_b);
char	*get_cmd_dir(char *cmd, t_mp *pg);
void	pwd(void);
void	cd(t_cmds *cmds);
int		export(t_cmds *cmds, t_list *env);
void	print_env(t_list *env);
int		env(t_cmds *cmds, t_list *env);
void	unset(t_cmds *cmds, t_list *env);
int		open_files_red(t_file *files);
void	close_files(t_file *files);
void	echo(t_cmds *cmds);
void	execute_one_cmd(t_cmds *cmds, t_mp *pg);
int builtins(t_cmds *cmds, t_mp *pg);

#endif