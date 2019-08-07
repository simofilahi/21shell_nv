/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:40:48 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 19:41:14 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse_error(t_index *l)
{
	ft_putendl_fd("21sh: parse error near `\\n'", 2);
	l->v = 777;
}

void	add_casual(t_cmd **lst, t_info **head, char **kratos, t_index *l)
{
	t_index	def;

	def.i = 1;
	def.j = 0;
	if (l->v == 0)
	{
		(*lst)->red = create_info(kratos[l->i], NULL, &(*l), def);
		*head = (*lst)->red;
	}
	else
	{
		(*lst)->red->next = create_info(kratos[l->i], NULL, &(*l), def);
		(*lst)->red = (*lst)->red->next;
	}
}

void	add_file(t_cmd **lst, t_info **head, char **cmd, t_index *l)
{
	int		k;
	int		p;
	t_index	def;

	k = l->i;
	p = l->i + 1;
	if (cmd[p])
	{
		l->i++;
		def.i = 1;
		def.j = 1;
		if (l->v == 0)
		{
			(*lst)->red = create_info(cmd[k], cmd[l->i], &(*l), def);
			*head = (*lst)->red;
		}
		else
		{
			(*lst)->red->next = create_info(cmd[k], cmd[l->i], &(*l), def);
			(*lst)->red = (*lst)->red->next;
		}
	}
	else
		parse_error(&(*l));
}
