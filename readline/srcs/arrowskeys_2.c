/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowskeys_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:12:54 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:21:45 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int		get_index(int randomindex, int tmpy, int tmpx)
{
	t_package	*p;
	int			index;

	p = cloud(NULL);
	index = 0;
	p->posx = 3;
	while (index < randomindex && p->line[index])
	{
		if ((tmpy == p->posy && p->posx == tmpx) ||\
				(tmpy == p->posy && p->line[index] == '\n'))
			return (index);
		if (p->line[index] == '\n' || p->posx == p->w.ws_col - 1)
		{
			p->posx = 0;
			tmpy++;
			if (tmpy == p->posy && p->line[index + 1] == '\n')
				return (++index);
		}
		else
			p->posx++;
		index++;
	}
	return (index);
}

void	ft_alt_upkey(t_package	*p)
{
	int			previndex;
	int			x;
	int			y;

	if (p->posy > p->init_y)
	{
		p->posy--;
		previndex = p->index - p->w.ws_col;
		if ((new_line_is_found(p->line)))
			previndex = p->index - (p->posx + 1);
		if ((p->posy == p->init_y) && (p->posx == 0 || p->posx == 1 ||\
					p->posx == 2))
		{
			p->posx = 3;
			p->index = 0;
		}
		else
			p->index = get_index(previndex, p->init_y, p->posx);
		get_pos(&y, &x);
		tputs(tgoto(CM_POS, p->posx, y - 2), 1, my_putchar);
	}
}

int		ft_alt_downkey_2(t_package *p, int randomindex, int *sub)
{
	int	x;
	int	y;

	if (randomindex > (int)ft_strlen(p->line) && !(new_line_is_found(p->line)))
	{
		*sub = randomindex - (int)ft_strlen(p->line);
		if (*sub > p->w.ws_col ||\
				count_lines(p->line, p->w.ws_col) + p->init_y - 1 == p->posy)
			return (0);
		randomindex -= *sub;
	}
	p->posy++;
	p->index = get_index(randomindex, p->init_y, p->posx);
	get_pos(&y, &x);
	tputs(tgoto(CM_POS, p->posx, y), 1, my_putchar);
	return (1);
}

void	ft_alt_downkey(t_package *p)
{
	int			randomindex;
	int			sub;
	int			i;

	randomindex = p->index + p->w.ws_col;
	if ((new_line_is_found(p->line)))
	{
		i = p->index;
		sub = p->posx;
		while (p->line[i] != '\n' && p->line[i])
		{
			i++;
			if (++sub == p->w.ws_col - 1)
				break ;
		}
		randomindex = p->index + (sub + 1);
		if (count_lines(p->line, p->w.ws_col) + p->init_y - 1 == p->posy)
			return ;
	}
	if (!(ft_alt_downkey_2(p, randomindex, &sub)))
		return ;
}

void	home_key()
{
	t_package	*p;
	int			y;
	int			x;
	int			tmp;

	p = cloud(NULL);
	if (p->index > 0)
	{
		tmp = p->posy;
		while (tmp > p->init_y)
		{
			ft_alt_upkey(p);
			tmp--;
		}
		p->posx = 3;
		p->posy = p->init_y;
		p->index = 0;
		get_pos(&y, &x);
		tputs(tgoto(CM_POS, p->posx, y - 1), 1, my_putchar);
	}
}
