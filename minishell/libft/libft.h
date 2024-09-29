/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:15:34 by mkadri            #+#    #+#             */
/*   Updated: 2024/05/15 09:49:02 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>

/* Struct s_list */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* LIBC Functions */

void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *dest, const void *source, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *str, size_t str_size);
void		*ft_memchr(const void *memory_block,
				int searched_char, size_t size);
void		*ft_memset(void *array, int value, size_t count);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strchr(const char *str, int searched_char);
char		*ft_strrchr(const char *str, int searched_char);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *str);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strjoin(char const *str1, char const *str2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int character);
int			ft_toupper(int character);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
int			ft_strncmp(const char *first, const char *second, size_t lenght);

/* BONUS Functions */

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));

#endif
