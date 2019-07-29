/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:26:35 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/29 15:04:25 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	ft_history_upkey(t_package *p, t_his **his_tail)
{
	if (p->his_flag)
		return ;
	home_key();
	clear_screen();
	ft_strdel(&p->line);
	p->line = ft_strnew(1);
	if (!(*his_tail))
		return ;
	if ((*his_tail)->prev != NULL)
	{
		p->his_tmp = (*his_tail);
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, (*his_tail)->hline, ft_strlen((*his_tail)->hline));
		paste_of_mouse(p);
		(*his_tail) = (*his_tail)->prev;
		return ;
	}
	else if ((*his_tail)->prev == NULL)
	{
		p->his_tmp = (*his_tail);
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, (*his_tail)->hline, ft_strlen((*his_tail)->hline));
		paste_of_mouse(p);
		return ;
	}
}

void	ft_history_downkey(t_package *p, t_his **his_tail)
{
	if (p->his_flag)
		return ;
	home_key();
	clear_screen();
	ft_strdel(&p->line);
	p->line = ft_strnew(1);
	if (!p->his_tmp)
		return ;
	if (p->his_tmp->next == NULL)
	{
		(*his_tail) = p->his_tmp;
		return ;
	}
	else if (p->his_tmp)
	{
		(*his_tail) = p->his_tmp;
		p->his_tmp = p->his_tmp->next;
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, p->his_tmp->hline, ft_strlen(p->his_tmp->hline));
		paste_of_mouse(p);
	}
}
