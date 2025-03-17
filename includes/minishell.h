/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:16:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/17 13:53:54 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}	t_list;

typedef struct s_index
{
	int i;
	int	j;
}	t_index;

typedef struct s_mp
{
	char	**envp;
}	t_mp;

extern t_list *g_gbc;

////////////////////helper_function////////////////////

t_list	*ft_lstnew(void *ptr);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_pcounter(char **s);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);

////////////////////----parsing----////////////////////

void	check_args(int ac, char **av);

////////////////////-----tools-----////////////////////

char	**init_env(char **envp);
void	allocation_fails(void);
void    sig_handler(int sig);
void    signal_setup(void);

#endif