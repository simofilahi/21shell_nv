/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:29:21 by aariss            #+#    #+#             */
/*   Updated: 2019/06/18 14:09:11 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_jchar(char *s, char c)
{
	char	*str;
	int		s_size;
	int		i;

	s_size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_size + 2))))
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char		*digitsrch(char *buf, char *key)
{
	char	*ptr;
	char	*str;
	int		i;

	if ((ptr = ft_strstr(buf, key)))
	{
		i = 0;
		while (ft_isdigit(ptr[i]))
			i++;
		if (ptr[i] == ':')
		{
			str = ft_strdup(ptr + i + 1);
			return (str);
		}
	}
	return (NULL);
}
static int	fill_line(char **ptr, char **line, int delimiter)
{
	char	*ptrchr;
	size_t	i;
	char	*str;
	char	*itoa;
	char	*key;
	char	*itoa1;
	char	*key1;

	i = 0;
	itoa = ft_itoa(delimiter);
	key = ft_strjoin(itoa, ":");
	itoa1 = ft_itoa(delimiter + 1);
	key1 = ft_strjoin(itoa1, ":");
	str = ft_strdup("");
	if((ptrchr = digitsrch(*ptr, key)))
	{
		while (ptrchr[i])
		{	
			if (ft_strncmp(ptrchr + i, key1, ft_strlen(key)) == 0 || ft_strcmp(ptrchr + i, "\0") == 0)
				break ;
			str = ft_jchar(str, ptrchr[i]);
			i++;
		}
		*line = ft_strdup(str);
	}
	free(*ptr);
	if (*line[0] == '\0')
		return (0);
	return (1);
}

static int			get_it(const int fd, char **line, int delimiter)
{
	int		red;
	char	*ptr;
	char	*buf;
	char *tmp;

	if (!(buf = ft_strnew(1)))
		return (-1);
	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0
			|| fd > 4863)
		return (-1);
	ptr = ft_strnew(1);
	if (!(buf = ft_strnew(BUFF_S)))
		return (-1);
	red = read(fd, buf, BUFF_S);
	buf[red] = '\0';
	tmp = ft_strjoin(ptr, buf);
	free(ptr);
	ptr = tmp;
	free(buf);
	return (fill_line(&ptr, line, delimiter));
}

int			gline(const int fd, char **line_target, int delimiter)
{
	char	*tiempo;
	char	*itoa;

	if (delimiter == 0 || delimiter < 0)
		return (0);
	tiempo = ft_strdup("");
	itoa = ft_itoa(delimiter);
	while (get_it(fd, &tiempo, delimiter))
	{
		*line_target = ft_strtrim(ft_strdup(tiempo));
		ft_strdel(&tiempo);
		ft_strdel(&itoa);
		return (1);
	}
	ft_strdel(&itoa);
	ft_strdel(&tiempo);
	return (0);
}
