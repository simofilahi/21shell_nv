/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recall_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:46:50 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/27 18:46:53 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_len_before_heredoc(char *str, int counter)
{
	int		i;
	int		flag;

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

int		get_len_of_needle(char *s)
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
	return ((end > start) ? end : 1);
}

/*
** - this one follow to bottom func
**	 this work with ctrl_c and ctrl_d
**   or if both not pressed;
*/

char	*meta_hander_ctrl_c_d(t_holder *h, int *flag)
{
	char	*tmp;
	char	*s;

	tmp = h->line;
	s = NULL;
	if (!(s = ft_readline("...", h->his_tail, 1)))
	{
		*flag = 1;
		ft_putchar_fd('\n', 1);
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_putchar_fd('\n', 1);
	if (g_signal_num == 3)
	{
		*flag = 2;
		(h->line = ft_strdup(s)) ? ft_strdel(&s) : 0;
		ft_strdel(&tmp);
		return (h->line);
	}
	(h->line = ft_strjoin(h->line, s)) ? ft_strdel(&s) : 0;
	ft_strdel(&tmp);
	return (NULL);
}

/*
** recall readline in cases where
** qoutes or backslach or pipe or heredoc found;
*/

char	*recall_readline(t_holder *h)
{
	int		flag;
	int		s_flag;

	flag = 0;
	s_flag = 0;
	if (!(heredoc_handler(h, &h->line)))
		return (NULL);
	while (meta_handler(h->line, &flag))
	{
		if (flag)
		{
			meta_hander_ctrl_c_d(h, &s_flag);
			if (s_flag == 0)
				continue ;
			else if (s_flag == 1)
				return (NULL);
			else if (s_flag == 2)
				return (h->line);
		}
		else
			break ;
	}
	return (h->line);
}
