#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# define BUFF_S 4096

int		gline(const int fd, char **line_target, int delimiter);
char	*ft_jchar(char *s, char c);

#endif
