/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:26:35 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/06 20:57:14 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	ft_history_upkey(t_package *p, t_his **his_tail)
{
	if (p->his_flag)
		return ;
	home_key();
	clear_screen();
	if (!(*his_tail))
		return ;
	if ((*his_tail)->prev != NULL)
	{
		p->his_tmp = (*his_tail);
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, (*his_tail)->hline, ft_strlen((*his_tail)->hline));
		ft_strdel(&p->line);
		p->line = ft_strnew(ft_strlen((*his_tail)->hline));
		paste_of_mouse(p);
		(*his_tail) = (*his_tail)->prev;
	}
	else if ((*his_tail)->prev == NULL)
	{
		p->his_tmp = (*his_tail);
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, (*his_tail)->hline, ft_strlen((*his_tail)->hline));
		ft_strdel(&p->line);
		p->line = ft_strnew(ft_strlen((*his_tail)->hline));
		paste_of_mouse(p);
	}
}

int		ft_history_downkey_2(t_package *p)
{
	if (p->hisline_tmp)
	{
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, p->hisline_tmp, ft_strlen(p->hisline_tmp));
		ft_strdel(&p->line);
		p->line = ft_strnew(ft_strlen(p->hisline_tmp));
		paste_of_mouse(p);
		return (1);
	}
	return (0);
}

void	ft_history_downkey_3(t_package *p, t_his **his_tail)
{
	(*his_tail) = p->his_tmp;
	p->his_tmp = p->his_tmp->next;
	ft_bzero(p->buffer, BUFFER_SIZE);
	ft_memcpy(p->buffer, p->his_tmp->hline, ft_strlen(p->his_tmp->hline));
	ft_strdel(&p->line);
	p->line = ft_strnew(ft_strlen(p->his_tmp->hline));
	paste_of_mouse(p);
}

void	ft_history_downkey(t_package *p, t_his **his_tail)
{
	if (p->his_flag)
		return ;
	home_key();
	clear_screen();
	if (!p->his_tmp)
	{
		if (ft_history_downkey_2(p))
			return ;
	}
	else if (p->his_tmp->next == NULL)
	{
		(*his_tail) = p->his_tmp;
		if (ft_history_downkey_2(p))
			return ;
	}
	else if (p->his_tmp)
	{
		ft_history_downkey_3(p, his_tail);
		return ;
	}
	ft_strdel(&p->line);
	p->line = ft_strnew(p->len);
}
