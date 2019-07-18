/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 08:40:45 by aariss            #+#    #+#             */
/*   Updated: 2019/07/12 19:53:03 by aariss           ###   ########.fr       */
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
	if (c == '>' || c == '<'
			|| c == '&')
		return (1);
	return (0);
}

int		alright_token(char *name)
{
	int	i;
	int	red;
	int	red_rev;

	i = 0;
	red = 0;
	red_rev = 0;
	while (name[i])
	{
		if (name[i] == '>')
			red++;
		else if (name[i] == '<')
			red_rev++;
		i++;
	}
	if (((red == 1 || red == 2) && red_rev == 0)
			|| ((red_rev == 1 || red_rev == 2) && red == 0))
		return ((red) ? red : red_rev);
	return (0);
}

int		is_one_of_them(char *name, t_defined *lst)
{
	while (lst)
	{
		if (ft_strstr(name, lst->data) && alright_token(lst->data))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int		got_token_after_digit(char *line)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if(ft_istoken(line[i]))
		return (1);
	return (0);
}
