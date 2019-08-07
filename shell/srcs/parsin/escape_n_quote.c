/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espace_n_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:47:13 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 17:05:38 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*quote_found(char *line, char *str, int *i, int *k)
{
	int		keeper;

	keeper = line[*i];
	if (line[(*i) + 1])
	{
		while (line[++(*i)] != keeper && line[*i])
		{
			if (line[*i] == -7)
			{
				(*i) = (*i) + 2;
				str[(*k)++] = keeper;
			}
			else
				str[(*k)++] = line[*i];
		}
	}
	return (str);
}

char	*ignore_quote(char *line)
{
	char	*str;
	int		i;
	int		k;

	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (0);
	i = -1;
	k = 0;
	while (line[++i])
	{
		(ft_iswhite(line[i])) ? line[i] = -1 : 1;
		if (ft_isquote(line[i]))
			str = quote_found(line, str, &i, &k);
		else
			str[k++] = line[i];
	}
	while (k < (int)ft_strlen(line) + 1)
		str[k++] = '\0';
	return (str);
}

void	escape_quote(char *line, char **str, int *i)
{
	(*i)++;
	if (line[*i] == '"')
	{
		*str = ft_joinchar(*str, 39);
		*str = ft_joinchar(*str, line[*i]);
		*str = ft_joinchar(*str, 39);
	}
	else if (line[*i] == 39)
	{
		*str = ft_joinchar(*str, '"');
		*str = ft_joinchar(*str, line[*i]);
		*str = ft_joinchar(*str, '"');
	}
	else
		*str = ft_joinchar(*str, line[*i]);
}

char	*escape_character(char *str, char *line, int *i, t_quote t)
{
	if (t.definer == 1)
	{
		(*i)++;
		if (line[*i] == 'n')
			str = ft_joinchar(str, '\n');
		else if (line[*i] == 't')
			str = ft_joinchar(str, '\t');
		else if (line[*i] == 'r')
			str = ft_joinchar(str, '\r');
		else if (line[*i] == 'v')
			str = ft_joinchar(str, '\v');
		else if (line[*i] == 'f')
			str = ft_joinchar(str, '\f');
		else if (line[*i] == t.keeper)
		{
			str = ft_joinchar(str, -7);
			str = ft_joinchar(str, line[*i]);
			str = ft_joinchar(str, -7);
		}
		else
			str = ft_joinchar(str, line[*i]);
	}
	else if (t.definer == 0)
		escape_quote(line, &str, &(*i));
	return (str);
}
