/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:15:10 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/18 19:48:30 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	free_structure_rl(t_package *p)
{
	ft_strdel(&p->line);
	ft_strdel(&p->holdcopy);
	if (p->hisline_tmp)
		ft_strdel(&p->holdcopy);
	free(p);
}
/*
** - increment row (that mean when terminal scrolling in last line);
** - recover position of cursor after saving in print_readablechar;
** - if posx equal to (p->w.ws_col ==> (last column in line)) move \
**   cursor down one line and increment posy (that meaning row);
*/

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

/*
** -print character by character and check if new line is found;
*/

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

/*
** - insert a character into line by index;
** - save position of cursor;
** - clear screen;
** - make cursor invisible;
** - print line by call print function;
** - change position of cursor after print line;
** - make cursor visible;
** - calcul last_line index;
*/

void	print_readablechar(t_package *p)
{
	int			last_line;
	int			check;

	insert_element(p);
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
