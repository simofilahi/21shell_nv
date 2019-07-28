/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:26:35 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/20 14:48:05 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	ft_history_upkey()
{
	t_package *p;

	p = cloud(NULL);
	home_key();
	clear_screen();
	ft_strdel(&p->line);
	p->line = ft_strnew(1);
	if (!p->his_tail)
		return ;
	if (p->his_tail->prev != NULL)
	{
		p->his_tmp = p->his_tail;
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, p->his_tail->hline, ft_strlen(p->his_tail->hline));
		paste_of_mouse(p);
		p->his_tail = p->his_tail->prev;
		return ;
	}
	else if (p->his_tail->prev == NULL)
	{
		p->his_tmp = p->his_tail;
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, p->his_tail->hline, ft_strlen(p->his_tail->hline));
		paste_of_mouse(p);
		return ;
	}
 }

void	ft_history_downkey()
{
		t_package *p;

		p = cloud(NULL);
		home_key();
		clear_screen();
		ft_strdel(&p->line);
		p->line = ft_strnew(1);
		if (!p->his_tmp)
			return ;
		if (p->his_tmp->next == NULL)
		{
			p->his_tail = p->his_tmp;
			return ;
		}
		else if (p->his_tmp)
		{
			p->his_tail = p->his_tmp;
			p->his_tmp = p->his_tmp->next;
			ft_bzero(p->buffer, BUFFER_SIZE);
		 	ft_memcpy(p->buffer, p->his_tmp->hline, ft_strlen(p->his_tmp->hline));
		 	paste_of_mouse(p);
		}
}	
