/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:49:00 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:29:19 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	reset_posxy(t_package *p, int index)
{
	int	count;

	p->index = (int)ft_strlen(p->line);
	while (p->index > index)
	{
		move_cursor(LEFTKEY);
		if (p->index[p->line - 1] == '\n')
			left_key(p);
		else
		{
			if (p->posx == 0)
			{
				p->posx = p->w.ws_col - 1;
				p->posy--;
				count = p->posx;
				while (count--)
					move_cursor(RIGHTKEY);
			}
			else
				p->posx--;
			p->index--;
		}
	}
}

int		increment_row(t_package *p, int flag)
{
	int ret;
	int resolution;

	resolution = (p->w.ws_row - p->init_y) * p->w.ws_col - 3;
	ret = 0;
	while ((int)ft_strlen(p->line) >= resolution)
	{
		p->w.ws_row++;
		resolution = (p->w.ws_row - p->init_y) * p->w.ws_col - 3;
		ret++;
	}
	if (ret > 0 && flag)
	{
		tputs(tgoto(CM_POS, 0, p->last_y), 1, my_putchar);
		tputs(MCDOL, 1, my_putchar);
		tputs(RC, 1, my_putchar);
		move_cursor(KEYUP);
	}
	return (ret);
}

int		increment_row_1(t_package *p)
{
	int resolution;
	int number_of_chars;
	int ret;

	resolution = (p->w.ws_row - p->init_y) * p->w.ws_col - 3;
	number_of_chars = count_lines(p->line, p->w.ws_col) * p->w.ws_col - 3;
	ret = 0;
	while (number_of_chars > resolution)
	{
		p->w.ws_row++;
		resolution = (p->w.ws_row - p->init_y) * p->w.ws_col - 3;
		ret++;
	}
	return (ret);
}

void	func(t_package *p)
{
	int i;
	int len;

	p->posx = 3;
	p->posy = p->init_y;
	i = 0;
	len = (int)ft_strlen(p->line);
	while (i < len)
	{
		if (p->line[i] == '\n' || p->posx == p->w.ws_col - 1)
		{
			p->posy++;
			p->posx = 0;
		}
		else
			p->posx++;
		i++;
	}
}

void	paste_key(t_package *p)
{
	char		*tmp;
	int			index;

	index = 0;
	if (p->holdcopy[0] != '\0')
	{
		tmp = p->line;
		p->line = addrange_of_elem(p->line, p->holdcopy, p->index);
		free(tmp);
		clear_screen();
		print(p, p->index - 1, p->posx - 1);
		p->index += (int)ft_strlen(p->holdcopy);
		func(p);
		reset_posxy(p, p->index);
		if (new_line_is_found(p->line))
			increment_row_1(p);
		else
			increment_row(p, 0);
	}
}
