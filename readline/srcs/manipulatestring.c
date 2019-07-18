/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatestring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:00:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/03 15:29:39 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	delete_element(char *string, int key)
{
	int		i;
	size_t	len;

	len = ft_strlen(string);
	i = 0;
	if ((int)len == key)
		string[len - 1] = '\0';
	while (i < key)
		i++;
	while (string[i])
	{
		string[i] = string[i + 1];
		i++;
	}
}

void	insert_element_1(char *string, char *ptr, int key, char ch)
{
	int i;
	int j;

	i = -1;
	while (++i < key && ptr[i])
		string[i] = ptr[i];
	string[i++] = ch;
	j = i - 1;
	while (ptr[j])
		string[i++] = ptr[j++];
	string[i] = '\0';
}

char	*insert_element(char *string, char ch, int key, int *lline)
{
	int		len;
	char	*ptr;
	
	len = ft_strlen(string);
	ptr = ft_strdup(string);
	if (len >= *lline)
	{
		*lline += (len > *lline) ? len + 20 : 20;
		*lline += (len > *lline) ? len + 20 : 20; 
		ft_strdel(&string);
		if (!(string = ft_strnew(*lline)))
			return (NULL);
		ft_strcpy(string, ptr);
	}
	if (key == len)
	{
		string[key] = ch;
		string[++key] = '\0';
	}
	else if (!(key < 0) && key < len)
		insert_element_1(string, ptr, key, ch);
	ft_strdel(&ptr);
	return (string);
}

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
