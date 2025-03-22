/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/22 16:20:26 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum token_type {
    WORD,
    PIPE, 
    RED_IN,
    RED_OUT,
    RED_APPEND,
    HEREDOC
}   t_token_type;

typedef enum t_type {
    CMD,
	PIPELINE,
    REDIRECTION,
    FILE_ARG
}   t_type;

typedef struct s_arg
{
    char			*arg;
    t_token_type	type;
    struct s_arg	*next;
}   t_arg;

typedef struct s_token
{
	t_arg   **args;
    t_type	type;
    int     heredoc;
}   t_token;


typedef struct s_mp
{
	char	**envp;
	t_token	token;
}	t_mp;

extern t_list *g_gbc;

////////////////////----parsing----////////////////////

void	check_args(int ac, char **av);
t_list	*split_phrase(char *s);
t_arg	*split_tokens(t_list *s);

////////////////////-----tools-----////////////////////

void    *ft_malloc(size_t size);
void 	print_banner(void);
void	print_exit(void);
char	**init_env(char **envp);
void	allocation_fails(void);
void    sig_handler(int sig);
void    signal_setup(void);
char	**ft_split(char const *s);
t_arg	*new_arg(char *arg);
void	argadd_back(t_arg **arg, t_arg *new);
void	typeof_token(t_arg	*arg);
int     error_slayer(t_arg *arg);



#endif