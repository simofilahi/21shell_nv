/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_paste.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:53:59 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/29 15:53:50 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** - take a copy of line;
** - shorthand : alt+c;
*/

void	copy_line_key(char **buffer_ref, char *line)
{
	char	*tmp;

	tmp = *buffer_ref;
	if (!(*buffer_ref = ft_strdup(line)))
		return ;
	free(tmp);
}

/*
** - copy partie before cursor from line;
** - shorthand : alt+>;
*/

void	copy_before_cursor_key(char **buffer_ref, char *line, int index)
{
	char	*tmp;

	tmp = *buffer_ref;
	if (!((*buffer_ref) = ft_strsub(line, 0, index)))
		return ;
	free(tmp);
}

/*
** - copy partie after cursor from line;
** - shorthand : alt+<;
*/

void	copy_after_cursor_key(char **buffer_ref, char *line, int index)
{
	char	*tmp;

	tmp = *buffer_ref;
	if (!((*buffer_ref) = ft_strsub(line, index, ft_strlen(line))))
		return ;
	free(tmp);
}

/*
** - cut line;
** - shorthand : alt+x;
*/

void	cut_line_key(char **buffer_ref, char **line)
{
	char	*tmp;

	tmp = *buffer_ref;
	if (!(*buffer_ref = ft_strdup(*line)))
		return ;
	free(tmp);
	home_key();
	clear_screen();
	ft_strdel(line);
	*line = ft_strnew(1);
}

/*
** - cut partie before cursor from line;
** - shorthand : alt+shift+<;
*/

void	cut_before_cursor_key(char **buffer_ref, char **line, int index)
{
	t_package	*p;
	char		*tmp;
	char		*tmp_2;

	tmp = *buffer_ref;
	tmp_2 = *line;
	p = cloud(NULL);
	if (p->index > 0)
	{
		if (!((*buffer_ref) = ft_strsub((*line), 0, index)))
			return ;
		if (!((*line) = delrange_of_elem((*line), 0, index - 1)))
			return ;
		home_key();
		clear_screen();
		p->posx = 3;
		p->index = 0;
		p->posy = p->init_y;
		tputs(SC, 1, my_putchar);
		print_line(*(line), 0);
		tputs(RC, 1, my_putchar);
		free(tmp);
		free(tmp_2);
	}
}
