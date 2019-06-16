/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:15:10 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:32:57 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	change_pos(t_package *p, int check)
{
	int	flag;
	int	flag_1;

	flag = 0;
	flag_1 = 0;
	if (new_line_is_found(p->line))
		flag_1 = increment_row_1(p);
	else
		flag = increment_row(p, 1);
	tputs(RC, 1, my_putchar);
	if (flag > 0 ||\
		(flag_1 > 0 && check) ||\
		(flag_1 > 0 && p->line[p->index] == '\n'))
		move_cursor(KEYUP);
	if (p->posx == p->w.ws_col || p->line[p->index] == '\n')
	{
		tputs(MCDOL, 1, my_putchar);
		p->posy++;
		p->posx = 0;
	}
	else
		move_cursor(RIGHTKEY);
}

int		print(t_package *p, int index, int col)
{
	int	check;

	check = 0;
	while (p->line[++index])
	{
		ft_putchar_fd(p->line[index], 1);
		if (p->line[index] == '\n' || col == p->w.ws_col - 1)
		{
			if (col == p->w.ws_col - 1 && \
					(p->line[index + 1] == '\n' || p->line[index + 1] == '\0'))
			{
				if (!(p->line[index] == '\n') && new_line_is_found(p->line))
				{
					tputs(MCDOL, 1, my_putchar);
					check = 1;
				}
			}
			col = 0;
		}
		else
			col++;
	}
	return (check);
}

void	print_readablechar(t_package *p)
{
	int			last_line;
	int			check;

	p->line = insert_element(p->line, p->buffer[0], p->index, &p->len);
	p->posx++;
	tputs(SC, 1, my_putchar);
	clear_screen();
	tputs(SVC, 1, my_putchar);
	check = print(p, p->index - 1, p->posx - 1);
	change_pos(p, check);
	p->index++;
	tputs(EVC, 1, my_putchar);
	last_line = (((int)ft_strlen(p->line) + 2) / (p->w.ws_col))\
				+ p->init_y;
	p->last_y = last_line;
}