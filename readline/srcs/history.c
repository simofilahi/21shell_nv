/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:26:35 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/17 15:14:27 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** - print line after get line from history file;
*/

void	print_history_line(t_package *p)
{
	while (p->line[p->index])
	{
		(p->posx == p->w.ws_col - 1 || p->line[p->index] == '\n') ?\
			p->posx = 0 : p->posx++;
		if (p->posx == 0)
			p->posy++;
		if (p->posy + 1 > p->w.ws_row)
			p->w.ws_row++;
		ft_putchar_fd(p->line[p->index++], 1);
	}
	if (p->posx == 0)
		tputs(MCDOL, 1, my_putchar);
}

void	ft_history_upkey(t_package *p)
{
	int fd;

	if (p->ll_index > -1)
	{
		home_key();
		clear_screen();
		ft_strdel(&p->line);
		p->line = ft_strnew(1);
		fd = open(p->path, O_RDONLY);
		if (!gline(fd, &p->line, p->ll_index--))
		{
			p->ll_index++;
			close(fd);
			return ;
		}
		close(fd);
		home_key();
		clear_screen();
		print_history_line(p);
	}
}

void	ft_history_downkey(t_package *p)
{
	int fd;

	if (p->ll_index > -1)
	{
		home_key();
		clear_screen();
		ft_strdel(&p->line);
		p->line = ft_strnew(1);
		fd = open(p->path, O_RDONLY);
		if (!gline(fd, &p->line, ++p->ll_index))
		{
			--p->ll_index;
			close(fd);
			return ;
		}
		close(fd);
		home_key();
		clear_screen();
		print_history_line(p);
	}
}
