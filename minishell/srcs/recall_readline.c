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
//

/*
** check if any of metachar found;
*/

int		metacharacters(char ch, int flag)
{
	if (flag)
	{
		if (ch == SQUOTE ||\
				ch == DQUOTE)
			return (1);
	}
	else
	{
		if (ch == BACKSLACH ||\
				ch == PIPE)
			return (1);
	}
	return (0);
}

/*
** check before pipe if therse some characters;
*/

int		beforepipe(char *line, int index)
{
	int	j;

	if (index == 0)
		return (0);
	else
	{
		j = 0;
		while (j < index)
			if (!ft_isspace(line[j++]))
				return (1);
	}
	return (0);
}

int		get_needle(char *s, char **needle)
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

int		heredoc_is_found(char *s, char **needle, int *index)
{
	int i;

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

int		heredoc_handler_(t_holder *h, char **line, char *needle)
{
	char	*tmp;
	char	*s;

	while ((s = ft_readline("<<.", NULL, -2)))
	{
		ft_putchar_fd('\n', 1);
		if (!s)
			return (0);
		if (g_signal_num == 3)
		{
			*line = ft_strdup(s);
			ft_strdel(&s);
			return (0);
		}
		if ((ft_strncmp(s, needle, ft_strlen(needle)) == 0))
		{
			ft_strdel(&needle);
			return(1) ;
		}
		else
		{
			tmp = h->heredoc;
			h->heredoc = ft_strjoin(h->heredoc, s);
			ft_strdel(&tmp);
		}
	}
	return (1);
}

int 	get_len_before_heredoc(char *str, int counter)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (flag == counter)
				return (i += 2);
			flag++;
		}
		i++;
	}
	return (-1);
}

int   get_len_of_needle(char *s)
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
	return ((end > start) ? end  : 1);
}

char	*join_in_line(char *str, char *heredoc, int *counter)
{
	int		key;
	char	*tmp;
	char	*str2;
	int		len;
	int		i;
	char	*ptr;
	
	ptr = NULL;
	str2 = ft_strdup(str);
	key = get_len_before_heredoc(str2, *counter);
	i = key;
	if (str2[key] == ' ')
		key++;
	str2[key] = '\0';
	tmp = ft_strjoin(str2, heredoc);
	ft_strdel(&str2);
	len = get_len_of_needle(str + i);
	ptr = tmp;
	tmp = ft_strjoin(tmp, str + len + i);
	ft_strdel(&ptr);
	return (tmp);
}

int		heredoc_handler(t_holder *h, char **line)
{
	char	*needle;
	char	*s;
	int		counter;
	char	*tmp;

	needle = NULL;
	s = NULL;
	counter = 0;
	tmp = ft_strdup(*line);
	h->heredoc = ft_strnew(1);
	while (heredoc_is_found(*line, &needle, &counter))
	{
		if (!(heredoc_handler_(h, line, needle)))
			return (0);
		tmp = join_in_line(tmp, h->heredoc, &counter);
		ft_strdel(&h->heredoc);
		h->heredoc = ft_strnew(1);
		counter++;
	}
	*line = ft_strdup(tmp);
	ft_putstr_fd("here final line ", fd2);
	ft_putstr_fd(*line, fd2);
	return (1);
}

void	_meta_handler(t_var *v, char *line, int *flag)
{
	if (metacharacters(line[v->index], 1) && (v->a || v->b))
	{
		if ((line[v->index] == SQUOTE && v->a) ||\
				(line[v->index] == DQUOTE && line[v->index - 1] != BACKSLACH && v->b))
		{
			v->a = 0;
			v->b = 0;
			*flag = 0;
		}
	}
	else if (metacharacters(line[v->index], 0) && (v->c || v->d))
	{
		if ((v->c && line[v->index - 1] == BACKSLACH && line[v->index] == PIPE) ||\
				(v->d && line[v->index - 1] == PIPE && line[v->index] == BACKSLACH))
			*flag = 0;
	}
	else if (!metacharacters(line[v->index], 0) && ft_isprint(line[v->index]))
	{
		if ((v->c && (!v->a && !v->b)) || (v->d && (!v->a && !v->b)))
			*flag = 0;
	}
}

int		meta_handler(char *line, int *flag)
{
	t_var	*v;

	v = ft_memalloc(sizeof(t_var));
	while (line[v->index])
	{
		if (metacharacters(line[v->index], 1) && \
			   	(!v->a && !v->b))
		{
			if (line[v->index] == SQUOTE && \
				   	((!metacharacters(line[v->index - 1], 0)) || v->d))
				v->a = 1;
			else if (line[v->index] == DQUOTE && \
					((!metacharacters(line[v->index - 1], 0)) || v->d))
				v->b = 1;
			*flag = (v->a || v->b) ? 1 : 0;
		}
		else if (metacharacters(line[v->index], 0) &&\
			   	(!v->c) && (!v->a && !v->b))
		{
			if (line[v->index] == BACKSLACH && \
				   	!metacharacters(line[v->index + 1], 1))
				v->c = 1;
			else if (line[v->index] == PIPE && \
				   	beforepipe(line, v->index))
				v->d = 1;
			*flag = (v->c || v->d) ? 1 : 0;
		}
		else
			_meta_handler(v, line, flag);
		v->index++;
	}
	free(v);
	return (1);
}

/*
 ** recall readline in cases where qoutes or backslach or pipe found;
 */

char	*recall_readline(t_holder *h, char *homepath)
{
	int 	flag;
	char	*tmp;
	char	*s;

	flag = 0;
	s = NULL;
	if (!(heredoc_handler(h, &h->line)))
		return (h->line);
	while (meta_handler(h->line, &flag))
	{
		if (flag)
		{
			tmp = ft_strdup(h->line);
			if (!(s = ft_readline("...", homepath, -2)))
			{
				ft_putchar_fd('\n', 1);
				return (h->line);
			}
			ft_putchar('\n');
			ft_strdel(&h->line);
			if (g_signal_num == 3)
			{
				 h->line = ft_strdup(s);
				ft_strdel(&s);
				return (h->line);
			}
			h->line = ft_strjoin(tmp, s);
			ft_strdel(&tmp);
			ft_strdel(&s);
		}
		else 
			break ;
	}
	return (h->line);
}
