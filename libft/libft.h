/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:24:06 by bmassot           #+#    #+#             */
/*   Updated: 2026/03/22 10:54:56 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H 
# define LIBFT_H 

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

// -------- GET_NEXT_LINE --------//

char	*get_next_line(int fd);

// -------- FT_PRINTF --------//

int		ft_format(va_list *args, const char spec);
int		ft_print_ptr(void *ptr);
int		ft_len_ptr(uintptr_t num);
int		ft_print_hex(unsigned int num, const char format);
void	ft_put_hex(unsigned int num, const char format);
void	ft_put_ptr(uintptr_t ptr);
int		ft_print_str(char *str);
int		ft_print_chr(int c);
void	ft_putstr(char *str);
int		ft_print_num(int n);
char	*ft_uitoa(unsigned int n);
int		ft_print_unsigned(unsigned int n);
int		ft_printf(const char *spec, ...);

// -------- LINKED LISTS --------//

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_node);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// -------- CHARS --------//

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// -------- STRINGS --------//

void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(char const *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char	*src);

// -------- FDS --------//

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

// -------- MEMORY --------//

void	ft_bzero(void *dest, size_t len);
void	*ft_calloc(size_t n, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *dest, int c, size_t len); // why const void?

// -------- NUMBERS --------//

int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif
