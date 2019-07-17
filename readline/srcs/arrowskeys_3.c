/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 22:19:09 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/17 12:26:17 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** - delete one char from line;
** - clear screen
** - reprint line from current index;
*/

void	backspace_key(t_package *p)
{
	int			i;

	left_key(p);
	delete_element(p->line, p->index);
	tputs(SC, 1, my_putchar);
	clear_screen();
	print_line(p->line, p->index);
	tputs(RC, 1, my_putchar);
	i = (((int)ft_strlen(p->line) + 2) / (p->w.ws_col)) + p->init_y;
	p->last_y = i;
}

/*
** - go to end of line;
*/

void	end_key(t_package *p)
{
	while (p->line[p->index])
	{
		if (p->line[p->index] == '\n' || p->posx == p->w.ws_col - 1)
		{
			p->posx = -1;
			p->posy++;
			tputs(MCDOL, 1, my_putchar);
		}
		else
			move_cursor(RIGHTKEY);
		p->posx++;
		p->index++;
	}
	p->index = (int)ft_strlen(p->line);
}

/*
** - cut the partie before cursor from line;
** - clear screen;
** - reprint line from index 0;
*/

void	cut_after_cursor_key(char **buffer_ref, char **line, int index)
{
	char		*tmp;
	char		*tmp_2;
	t_package	*p;

	tmp = *buffer_ref;
	tmp_2 = *line;
	p = cloud(NULL);
	if (!((*buffer_ref) = ft_strsub(*line, index, (int)ft_strlen(*line))))
		return ;
	if (!(*line = delrange_of_elem((*line), index,\
					(int)ft_strlen(*line))))
		return ;
	clear_screen();
	free(tmp);
	free(tmp_2);
}
