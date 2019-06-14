/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowskeys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 15:55:21 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:21:47 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	forwardkey(t_package *p)
{
	while (ft_isalnum(p->line[p->index]) &&\
			p->line[p->index])
		right_key(p);
	while (!(ft_isalnum(p->line[p->index])) &&\
			p->line[p->index])
		right_key(p);
}

void	backwardkey(t_package *p)
{
	while (!(ft_isalnum(p->line[p->index - 1])) && p->index > 0)
		left_key(p);
	while ((ft_isalnum(p->line[p->index - 1])) && p->index > 0)
		left_key(p);
}

void	right_key(t_package *p)
{
	p->index++;
	p->posx++;
	if (p->line[p->index - 1] == '\n')
	{
		p->posx = 0;
		p->posy++;
		tputs(MCDOL, 1, my_putchar);
	}
	else
	{
		if (p->posx != p->w.ws_col)
			move_cursor(RIGHTKEY);
		else
		{
			p->posx = 0;
			p->posy++;
			tputs(MCDOL, 1, my_putchar);
		}
	}
}

void	left_key_with_history(int tmp, int x, int y, t_package *p)
{
	while (x >= 0 && p->line[x] != '\n')
	{
		if (y == p->w.ws_col - 1)
			y = -1;
		x--;
		y++;
	}
	if (y == 0 && p->line[tmp] == '\n')
		p->posx = y;
	else if (y == 0 && x == -1)
		p->posx = 3;
	else if (x == -1)
	{
		p->posx = y + 3;
		if (p->posx >= p->w.ws_col)
			p->posx -= p->w.ws_col;
	}
	else
		p->posx = y;
	p->posy--;
	get_pos(&y, &x);
	tputs(tgoto(CM_POS, p->posx, y - 2), 1, my_putchar);
}

void	left_key(t_package *p)
{
	int			b;

	p->index--;
	p->posx--;
	b = p->index - 1;
	if (p->line[p->index] == '\n')
		left_key_with_history(b, b, 0, p);
	else
	{
		if (p->posx >= 0)
			move_cursor(LEFTKEY);
		else
		{
			p->posx = p->w.ws_col - 1;
			p->posy--;
			tputs(MCUOL, 1, my_putchar);
			b = p->posx;
			while (b-- > 0)
				move_cursor(RIGHTKEY);
		}
	}
}
