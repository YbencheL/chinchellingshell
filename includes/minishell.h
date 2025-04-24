/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/24 16:29:21 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct	s_file
{
	char			*file;
	t_token_type	type;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmds
{
	char	**cmds;
	t_file	*files;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_mp
{
	char	**envp;
	int		exit_status;
}	t_mp;

extern t_list	*g_gbc;

////////////////////----parsing----////////////////////


int		check_unclosed_quotes(char *s, t_mp *pg);
t_arg   *tokenize(char *line, t_mp *pg);
t_token *tokens_to_cmds(t_arg *tokens);
void	expand_variables(t_arg *token, t_mp *pg);
void	handle_var_space(t_arg **token);
t_cmds	*get_final_cmds(t_token *token);
// void	add_token(char **str, t_arg **token);
// void	unclosed_q_error(t_mp *pg);
// char	*extract_word(char *s, int *start, t_lst **phrase);
// char	*extract_phrase(char *s, int *start, char c);
// t_lst	*handle_quotes(char *s, int *i, t_lst **phrase, t_mp *pg);
// t_lst	*split_phrase(char *s,  t_mp *pg);
// t_arg	*split_tokens(t_lst *s);
// int		error_slayer(t_arg *arg, t_mp *pg);
// t_list	*checking_variables(t_arg *token, t_mp *pg);
// char	*check_for_var(char *s, int *start);
// char	*get_variable_value(char *var_name, t_mp *ev);
// char	*replace_var(char *token, char *var, char *value);

////////////////////-----tools-----////////////////////

void	*ft_malloc(size_t size);
char	**init_env(char **envp);
void	check_args(int ac, char **av);
void	allocation_fails(void);
void	signal_setup(void);
void	print_banner(void);
void	print_exit(void);
char	**split_token(char *s);
t_arg	*new_arg(char *arg);
void	argadd_back(t_arg **arg, t_arg *new);
char	**split_only_spaces(char *s);
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
void 	check_herdoc(t_file *files);
int		fill_herdoc(t_cmds *cmds, t_mp *pg);
void	dup_in(int fd);
void	dup_out(int fd);
void	in_n_out_backup(int *stdin_b, int *stdout_b);
int	check_redirection(t_file *files);
void	restor_fd(int stdin_b, int stdout_b);


#endif