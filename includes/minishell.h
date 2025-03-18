/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/18 16:50:46 by ybenchel         ###   ########.fr       */
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
    char            *arg;
    t_token_type    type;
}   t_arg;

typedef struct s_token
{
    t_arg          **args;
    t_type         type;
    char          *heredoc;
}   t_token;


typedef struct s_mp
{
	char	**envp;
	t_token	token;
}	t_mp;

extern t_list *g_gbc;

////////////////////----parsing----////////////////////

void	check_args(int ac, char **av);

////////////////////-----tools-----////////////////////

void 	print_banner(void);
void	print_exit(void);
char	**init_env(char **envp);
void	allocation_fails(void);
void    sig_handler(int sig);
void    signal_setup(void);


#endif