/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 08:40:45 by aariss            #+#    #+#             */
/*   Updated: 2019/06/18 09:00:22 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

int		ft_isquote(int c)
{
		if (c == 39 || c == '"')
			return (1);
		return (0);
}

int		ft_istoken(int c)
{
	if (c == '|' || c == '>' || c == '<'
			|| c == '&' || c == '1' || c == '2')
		return (1);
	return (0);
}

int		is_one_of_them(char *name, t_defined *lst)
{
	while (lst)
	{
		if (ft_strncmp(name, lst->data, ft_strlen(lst->data)) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}
