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
	int	i;
	int	start;


	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	start = i;
	while (s[i] && s[i] != ' ' && s[i] != '\n' &&\
		   	!metacharacters(s[i], 0) &&\
		   	!metacharacters(s[i], 1) &&\
			(s[i] != '<' && s[i + 1] != '<'))
		i++;
	if (s[i])
		i += 1;
	*needle = ft_strsub(s, start, i);
	if (ft_strlen(*needle) >= 1 && !(*needle[0] == '\n'))
		return (1);
	return (0);
}

int	last_heredoc(char *s)
{
	while (*s)
	{
		if (*s == '<' && *(s + 1) == '<')
			return (0);
		s++;
	}
	return (1);
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
				{
					if (last_heredoc(s + 2))
						*index = -1;
					return (1);
				}
				else
					return (0);
			}
			i++;
		}
		s++;
	}
	return (0);
}

int		heredoc_handler_(t_holder *h, char **line, char **s, char *needle)
{
	char	*tmp;

	while ((*s = ft_readline("<<.", NULL, -2)))
	{
		ft_putchar_fd('\n', 1);
		if (g_signal_num == 3)
		{
			*line = ft_strdup(*s);
			ft_strdel(s);
			return (0);
			g_signal_num = 1;
		}
		if ((ft_strncmp(*s, needle, ft_strlen(needle)) == 0))
		{
			ft_strdel(&needle);
			return(1) ;
		}
		else
		{
			tmp = h->heredoc;
			h->heredoc = ft_strjoin(h->heredoc, *s);
			ft_strdel(&tmp);
		}
	}
	return (1);
}

int		heredoc_handler(t_holder *h, char **line)
{
	char	*needle;
	char	*s;
	int		index;

	needle = NULL;
	s = NULL;
	index = 0;
	h->heredoc = ft_strnew(1);
	while (heredoc_is_found(*line, &needle, &index))
	{
		
		if (!(heredoc_handler_(h, line, &s, needle)))
			return (0);
		if (!s)
		{
			ft_putchar('\n');
			return (0);
		}
		if (index == -1)
			break;
		else
		{
		   index++;
		   ft_strdel(&h->heredoc);
		   h->heredoc = ft_strnew(1);
		}
	}
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

char	*recall_readline(t_holder *h, char *line, char *homepath)
{
	int 	flag;
	char	*tmp;
	char	*s;

	flag = 0;
	s = NULL;
	if (!(heredoc_handler(h, &line)))
		return (line);
	while (meta_handler(line, &flag))
	{
		if (flag)
		{
			tmp = ft_strdup(line);
			if (!(s = ft_readline("...", homepath, -2)))
			{
				ft_putchar_fd('\n', 1);
				return (line);
			}
			ft_putchar('\n');
			ft_strdel(&line);
			if (g_signal_num == 3)
			{
				line = ft_strdup(s);
				ft_strdel(&s);
				return (line);
				g_signal_num = 1;
			}
			line = ft_strjoin(tmp, s);
			ft_strdel(&tmp);
			ft_strdel(&s);
		}
		else 
			break ;
	}
	return (line);
}
