/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:13 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/15 15:55:15 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}	t_list;

typedef struct s_lst
{
	void			*ptr;
	int				is;
	struct s_lst	*next;
}	t_lst;

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
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
t_list	*ft_lstnew_custom(void	*ptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
t_lst	*ft_lstnew_space(void *ptr, int is);
void	ft_lstadd_back_space(t_lst **lst, t_lst *new);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	**ft_split(char *str, char *charset);
void	ft_strncpy(char *dest, char *src, unsigned int n);
int		ft_atoi(const char *str);
int		ft_lstsize(t_list *lst);
char	*bc_strchr_fo_rv(const char *s, char c, char l);
#endif