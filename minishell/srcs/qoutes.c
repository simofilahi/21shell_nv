/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:02:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/27 19:02:48 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check if any of metachar found;
*/

int			metacharacters(char ch, int flag)
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

static int	beforepipe(char *line, int index)
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

static void	meta_handler_2(t_var *v, char *line, int *flag)
{
	if (metacharacters(line[v->index], 1) && (v->a || v->b))
	{
		if ((line[v->index] == SQUOTE && v->a) ||\
			(line[v->index] == DQUOTE &&\
			line[v->index - 1] != BACKSLACH && v->b))
		{
			v->a = 0;
			v->b = 0;
			*flag = 0;
		}
	}
	else if (metacharacters(line[v->index], 0) && (v->c || v->d))
	{
		if ((v->c && line[v->index - 1] == BACKSLACH &&\
			line[v->index] == PIPE) ||\
			(v->d && line[v->index - 1] == PIPE &&\
			line[v->index] == BACKSLACH))
			*flag = 0;
	}
	else if (!metacharacters(line[v->index], 0) && ft_isprint(line[v->index]))
	{
		if ((v->c && (!v->a && !v->b)) ||\
		(v->d && (!v->a && !v->b)))
			*flag = 0;
	}
}

static int	meta_handler_1(t_var *v, char *line, int *flag)
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
		return (1);
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
		return (1);
	}
	return (0);
}

int			meta_handler(char *line, int *flag)
{
	t_var	*v;

	v = ft_memalloc(sizeof(t_var));
	v->index = -1;
	while (line[++v->index])
	{
		if (meta_handler_1(v, line, flag))
			continue;
		else
			meta_handler_2(v, line, flag);
	}
	free(v);
	return (1);
}
