/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:20:47 by aariss            #+#    #+#             */
/*   Updated: 2019/06/19 14:21:47 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

int		count_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_count_falpha(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalpha(s[i]))
		i++;
	return (i);
}

int     ft_count_till(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}
