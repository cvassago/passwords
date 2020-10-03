#ifndef PAS_H
# define PAS_H
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

size_t	ft_strlen(const char *str);
void		ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void		ft_putstr(const char *s);
int			ft_atoi(const char *str);
void	ft_putstr_fd(const char *s, int fd);
void	ft_bzero(void *str, size_t n);
void	*ft_memalloc(size_t size);
#endif
