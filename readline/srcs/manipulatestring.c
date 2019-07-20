/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatestring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:00:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/18 21:15:12 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** delete char from line;
*/

void	delete_element(t_package *p)
{
	int		i;
	int		length;

	length = (int)ft_strlen(p->line) - 1;
	if (length == p->index)
	{
		p->line[length] = '\0';
		return ;
	}
	i = 0;
	while (i < p->index)
		i++;
	while (p->line[i])
	{
		p->line[i] = p->line[i + 1];
		i++;
	}
}

/*
** - followed to insert_element;
*/

void	insert_element_1(t_package *p, char *ptr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ptr[i] && i <= p->index)
	{
		if (i == p->index)
		{
			p->line[j] = p->buffer[0];
			j++;
			break ;
		}
		p->line[j++] = ptr[i++];
	}
	while (ptr[i])
		p->line[j++] = ptr[i++];
	p->line[j] = '\0';
}

/*
** - insert char into line;
*/

void	insert_element(t_package *p)
{
	int		length;
	int		i;
	char	*ptr;

	length = ft_strlen(p->line);
	ptr = ft_strdup(p->line);
	if (length >= p->len)
	{
		p->len = (length > p->len) ? length + 50 : p->len + 50;
		ft_strdel(&p->line);
		if (!(p->line = ft_strnew(p->len)))
			return ;
		i = -1;
		while (ptr[++i])
			p->line[i] = ptr[i];
		p->line[i] = '\0';
	}
	if (p->index == length)
	{
		p->line[p->index] = p->buffer[0];
		p->line[p->index + 1] = '\0';
	}
	else
		insert_element_1(p, ptr);
}

/*
** - delete range of chars from line;
*/

char	*delrange_of_elem(char *string, int startindex, int endindex)
{
	t_package	*p;
	char		*tmp;
	size_t		len;
	int			i;

	p = cloud(NULL);
	len = ft_strlen(string) - (endindex - startindex);
	if (!(tmp = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < startindex)
		tmp[i] = string[i];
	while (string[endindex++])
		tmp[i++] = string[endindex];
	tmp[i] = '\0';
	return (tmp);
}

/*
** - insert range of chars into line;
*/

char	*addrange_of_elem(char *s1, char *s2, int key)
{
	char	*tmp;
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	int		j;

	len_s1 = (int)ft_strlen(s1);
	len_s2 = (int)ft_strlen(s2);
	if (!(tmp = ft_strnew(len_s1 + len_s2)))
		return (NULL);
	i = -1;
	while (++i < key)
		tmp[i] = s1[i];
	j = 0;
	while (s2[j])
		tmp[i++] = s2[j++];
	while (s1[key])
		tmp[i++] = s1[key++];
	tmp[i] = '\0';
	return (tmp);
}
