/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:21 by aariss            #+#    #+#             */
/*   Updated: 2019/06/20 10:59:12 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*skip_quote(char *line)
{
	char	*str;
	int		keeper;
	int		i;
	int		k;

	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (0);
	i = -1;
	k = 0;
	while (line[++i])
	{
		(ft_isspace(line[i])) ? line[i] = -1 : 1;
		if (ft_isquote(line[i]))
		{
			keeper = line[i];
			if (line[i + 1])
				while (line[++i] != keeper)
				{
					if (line[i] == -7)
					{
						i = i + 2;
						str[k++] = keeper;
					}
					else
						str[k++] = line[i];
				}
		}
		else
			str[k++] = line[i];
	}
	while (k < (int)ft_strlen(line))
		str[k++] = '\0';
	return (str);
}

char	*skip_token(char *toto, char *line, int *t)
{
	int	i;

	i = 0;
	while (ft_istoken(line[i]))
	{
		toto = ft_joinchar(toto, line[i]);
		i++;
	}
	*t = i;
	return (toto);
}

char	*skip_char(char *toto, char *line, int *i, int definer, int quote)
{
	if (definer == 1)
	{
		(*i)++;
		if (line[*i] == 'n')
			toto = ft_joinchar(toto, '\n');
		else if (line[*i] == 't')
			toto = ft_joinchar(toto, '\t');
		else if (line[*i] == 'r')
			toto = ft_joinchar(toto, '\r');
		else if (line[*i] == 'v')
			toto = ft_joinchar(toto, '\v');
		else if (line[*i] == 'f')
			toto = ft_joinchar(toto, '\f');
		else if (line[*i] == quote)
		{
			toto = ft_joinchar(toto, -7);
			toto = ft_joinchar(toto, line[*i]);
			toto = ft_joinchar(toto, -7);
		}

		else
			toto = ft_joinchar(toto, line[*i]);
	}
	else if (definer == 0)
	{
		(*i)++;
		if (line[*i] == '"')
		{
			toto = ft_joinchar(toto, 39);
			toto = ft_joinchar(toto, line[*i]);
			toto = ft_joinchar(toto, 39);
		}
		else if (line[*i] == 39)
		{
			toto = ft_joinchar(toto, '"');
			toto = ft_joinchar(toto, line[*i]);
			toto = ft_joinchar(toto, '"');
		}
		else
			toto = ft_joinchar(toto, line[*i]);
	}
	return (toto);
}

char	*parsin(char *line, t_env *env)
{
	int			i;
	int			keeper;
	int			t;
	char		*toto;
	t_defined	*lst;

	i = 0;
	t = 0;
	toto = ft_strdup("");
	lst = init_cases();
	if (line)
	{
		while (i < (int)ft_strlen(line))
		{
			if (line[i] == 92)
				toto = skip_char(toto, line, &i, 0, 0);
			else if (ft_isquote(line[i]))
			{
				keeper = line[i];
				toto = ft_joinchar(toto, line[i]);
				i++;
				while (line[i] != keeper)
				{
					if (line[i] == 92)
						toto = skip_char(toto,line, &i, 1, keeper);
					else if (line[i] == '$' && ft_strlen(line + i + 1) > 2)
						toto = dollar_handle_quoted(toto, line, &i, keeper, env);
					else
						toto = ft_joinchar(toto, line[i]);
					i++;
				}
				toto = ft_joinchar(toto, line[i]);
			}
			else if (ft_istoken(line[i]) && is_one_of_them(line + i, lst))
			{
				toto = ft_joinchar(toto, -1);
				toto = skip_token(toto, line + i, &t);
				toto = ft_joinchar(toto, -1);
				i = i + t;
			}
			else if (line[i]  == ';')
			{
				toto = ft_joinchar(toto, -3);
				i++;
			}
			else if (line[i] == '$' && ft_strlen(line + i + 1) > 1)
				toto = dollar_handle_simple(toto, line, &i, env);
			else if (line[i] == '~')
				toto = ft_strjoin(toto, get_var("HOME=", &env));
			else
				toto = ft_joinchar(toto, line[i]);
			i++;
		}
		return (skip_quote(toto));
	}
	return (NULL);
}

t__mc	*mc_lst(char **mc)
{
	t__mc	*lst;
	t__mc	*head;
	int		i;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	i = 0;
	while (i < count_tab(mc))
	{
		lst->cmd = ft_strsplit(mc[i], -1);
		i++;
		if (i == 1)
			head = lst;
		if (i < count_tab(mc))
		{
			if (!(lst->next = (t__mc*)malloc(sizeof(t__mc))))
				return (NULL);
			lst = lst->next;
		}
	}
	lst->next = NULL;
	return (head);
}

t__mc	*mc_maker(char *line, t_env *env)
{
	char	**slice;
	char	*parsed;
	t__mc	*lst;

	parsed = parsin(line, env);
	if (parsed[ft_strlen(parsed)] == '\n')
		parsed[ft_strlen(parsed)] = '\0';
	slice = ft_strsplit(parsed, -3);
	lst = mc_lst(slice);
	return (lst);
}
