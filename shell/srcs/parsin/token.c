/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 08:21:29 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 08:49:22 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	right_redirection(char *line, char **str, int *i, int *v)
{
	*str = ft_joinchar(*str, line[*i]);
	(*i)++;
	if (line[*i] == '>' || line[*i] == '&')
	{
		*v = (line[*i] == '&') ? 1 : 0;
		*str = ft_joinchar(*str, line[*i]);
		(*i)++;
	}
	if (*v == 1)
	{
		if (ft_isdigit(line[*i]))
		{
			while (ft_isdigit(line[*i]) && line[*i])
			{
				*str = ft_joinchar(*str, line[*i]);
				(*i)++;
			}
		}
		else if (line[*i] == '-')
		{
			*str = ft_joinchar(*str, line[*i]);
			(*i)++;
		}
	}
	*str = ft_joinchar(*str, -1);
}

void	digit_included(char *line, char **str, int *i)
{
	*str = ft_joinchar(*str, line[*i]);
	(*i)++;
	if (ft_isdigit(line[*i]) && line[*i])
	{
		while (ft_isdigit(line[*i]))
		{
			*str = ft_joinchar(*str, line[*i]);
			(*i)++;
		}
	}
	else if (line[*i] == '-')
	{
		*str = ft_joinchar(*str, line[*i]);
		(*i)++;
	}
}

void	left_redirection(char *line, char **str, int *i, int *t)
{
	*str = ft_joinchar(*str, line[*i]);
	(*i)++;
	if (line[*i] == '<')
	{
		*str = ft_joinchar(*str, line[*i]);
		(*i)++;
	}
	else if (line[*i] == '&' && *t == 1)
		digit_included(line, &(*str), &(*i));
	else if (line[*i] == '&' && t == 0)
	{
		*str = ft_joinchar(*str, line[*i]);
		(*i)++;
		if (line[*i] == '-')
		{
			*str = ft_joinchar(*str, line[*i]);
			(*i)++;
		}
	}
	*str = ft_joinchar(*str, -1);
}

void	end_redirection(char *line, char **str, int *i)
{
	if (line[(*i) + 1] != '<')
		*str = ft_joinchar(*str, line[*i]);
	(*i)++;
	if (line[*i] == '>')
	{
		*str = ft_joinchar(*str, line[*i]);
		(*i)++;
	}
	else
	{
		while (line[*i] == '<' && line[*i])
			(*i)++;
	}
	*str = ft_joinchar(*str, -1);
}

char	*token_manager(char *str, char *line, int *i)
{
	int	t;
	int	v;

	t = 0;
	v = 0;
	str = ft_joinchar(str, -1);
	while (ft_isdigit(line[*i]) && line[*i])
	{
		str = ft_joinchar(str, line[*i]);
		(*i)++;
		t = 1;
	}
	if (line[*i] == '&')
		end_redirection(line, &str, &(*i));
	else if (line[*i] == '<')
		left_redirection(line, &str, &(*i), &v);
	else if (line[*i] == '>')
		right_redirection(line, &str, &(*i), &v);
	return (str);
}
