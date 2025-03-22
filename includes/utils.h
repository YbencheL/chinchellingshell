/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:13 by abenzaho          #+#    #+#             */
/*   Updated: 2025/03/22 12:16:15 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_index
{
	int i;
	int	j;
}	t_index;

typedef struct s_list
{
    void    *ptr;
    struct s_list   *next;
} t_list;

////////////////////-----tools-----////////////////////

void    *ft_malloc(size_t size);
void 	print_banner(void);
void	print_exit(void);
char	**init_env(char **envp);
void	allocation_fails(void);
void    sig_handler(int sig);
void    signal_setup(void);
char	**ft_split(char const *s);

/////////////////////helper_function/////////////////////
t_list	*ft_lstnew(void *ptr);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_pcounter(char **s);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t 	count_splits(char const *s);
size_t 	get_word_len(const char *s);
int 	is_delimiter(char c);
int 	is_special_char(char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
t_list	*ft_lstnew_custom(void	*ptr);


#endif