#include "get_next_line.h"
#include <stdio.h>

static int	fill_line(char **ptr, char **line)
{
	char	*ptrchr;
	size_t	i;
	size_t  pos;
	char    *d;

	i = 0;
	if ((ptrchr = ft_strchr(*ptr, '\n')))
	{
		i = ft_strlen(ptrchr);
		pos = ft_strlen(*ptr) - i;
		*line = ft_strsub(*ptr, 0, pos);
		d = ft_strsub(*ptr,pos + 1,ft_strlen(*ptr) - pos);
		free(*ptr);
		*ptr = d;
	}
	else
	{
		*line = ft_strdup(*ptr);
		free(*ptr);
		*ptr = NULL;
		if (*line[0] == '\0')
			return (0);
	}
	return (1);
}

static int			get_it(const int fd, char **line)
{
	int				red;
	static	char	*ptr[100];
	char			*buf;
	char *tmp;

	if (!(buf = ft_strnew(1)))
		return (-1);
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0
			|| read(fd, buf, 0) < 0 || fd > 4863)
		return (-1);
	if (!ptr[fd])
		ptr[fd] = ft_strnew(1);
	if (!(ft_strchr(ptr[fd], '\n')))
	{
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (-1);
		while ((red = read(fd, buf, BUFF_SIZE)))
		{
			buf[red] = '\0';
			tmp = ft_strjoin(ptr[fd], buf);
			free(ptr[fd]);
			ptr[fd] = tmp;
			if (ft_strchr(buf, '\n'))
				break ;
		}
		free(buf);
	}
	return (fill_line(&ptr[fd], line));
}

int			gline(const int fd, char **line_target, int delimiter)
{
	char	*tiempo;
	char	*itoa;

	if (delimiter == 0)
		return (0);
	tiempo = ft_strdup("");
	itoa = ft_itoa(delimiter);
	while (get_it(fd, &tiempo))
	{
		if (ft_strncmp(tiempo, itoa, ft_strlen(itoa)) == 0)
		{
			if (ft_strchr(tiempo, ':'))
			{
				*line_target = ft_strdup(ft_strchr(tiempo, ':') + 1);
				ft_strdel(&tiempo);
				ft_strdel(&itoa);
				return (1);
			}
		}
		ft_strdel(&tiempo);
	}
	ft_strdel(&itoa);
	ft_strdel(&tiempo);
	return (0);
}