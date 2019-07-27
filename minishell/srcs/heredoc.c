/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recall_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 18:45:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/06/24 10:21:15 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_needle(char *s, char **needle)
{
	int	end;
	int	start;

	start = 0;
	while (s[start] && s[start] == ' ')
		start++;
	end = start;
	while (s[end] &&\
			!(s[end] == ' ' || s[end] == '\n') &&\
			!metacharacters(s[end], 0) &&\
			!metacharacters(s[end], 1) &&\
			!(s[end] == '<' && s[end + 1] == '<'))
	{
		end++;
	}
	if (s[end] == ' ')
		end -= 1;
	*needle = ft_strsub(s, start, end);
	if (ft_strlen(*needle) >= 1 && !(*needle[0] == '\n'))
		return (1);
	return (0);
}

static int	heredoc_is_found(char *s, char **needle, int *index)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == '<' && *(s + 1) == '<')
		{
			if (i == *index)
			{
				if (get_needle(s + 2, needle))
					return (1);
				else
					return (0);
			}
			i++;
		}
		s++;
	}
	return (0);
}

static char	*join_in_line(char *str, char *heredoc, char *ptr, int *counter)
{
	int		key;
	char	*tmp;
	char	*str2;
	int		len;
	int		i;

	ptr = NULL;
	str2 = ft_strdup(str);
	key = get_len_before_heredoc(str2, *counter);
	i = key;
	if (str2[key] == ' ')
		key++;
	str2[key] = '\0';
	ptr = ft_joinchar(ft_strdup(""), -1);
	tmp = heredoc;
	(heredoc = ft_strjoin(ptr, heredoc)) ? ft_strdel(&ptr) : 0;
	ft_strdel(&tmp);
	tmp = heredoc;
	(heredoc = ft_joinchar(heredoc, -1)) ? ft_strdel(&tmp) : 0;
	(tmp = ft_strjoin(str2, heredoc)) ? ft_strdel(&str2) : 0;
	len = get_len_of_needle(str + i);
	ptr = tmp;
	(tmp = ft_strjoin(tmp, str + len + i)) ? ft_strdel(&ptr) : 0;
	return (tmp);
}

static int	heredoc_handler_(t_holder *h, char **line, char *tmp, char *needle)
{
	char	*s;

	while ((s = ft_readline("<<.", NULL, -2)))
	{
		ft_putchar_fd('\n', 1);
		if (g_signal_num == 3)
		{
			(*line = ft_strdup(s)) ? ft_strdel(&s) : 0;
			return (0);
		}
		if ((ft_strncmp(s, needle, ft_strlen(needle)) == 0))
		{
			ft_strdel(&needle);
			return (1);
		}
		else
		{
			tmp = h->heredoc;
			(h->heredoc = ft_strjoin(h->heredoc, s)) ? ft_strdel(&tmp) : 0;
			ft_strdel(&s);
		}
	}
	ft_putchar_fd('\n', 1);
	return (0);
}

int			heredoc_handler(t_holder *h, char **line)
{
	char	*needle;
	char	*s;
	int		counter;
	char	*tmp;

	needle = NULL;
	s = NULL;
	tmp = ft_strdup(*line);
	counter = 0;
	while (heredoc_is_found(*line, &needle, &counter))
	{
		h->heredoc = ft_strnew(1);
		if (!(heredoc_handler_(h, line, NULL, needle)))
			return (0);
		tmp = join_in_line(tmp, h->heredoc, NULL, &counter);
		counter++;
	}
	*line = ft_strdup(tmp);
	return (1);
}
