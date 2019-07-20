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


void	ft_history_upkey(t_package *p)
{
	int		fd;
	char	*tmp;

	if (p->ll_index > -1)
	{
		home_key();
		clear_screen();
		ft_strdel(&p->line);
		p->line = ft_strnew(1);
		fd = open(p->path, O_RDONLY);
		if (!gline(fd, &tmp, p->ll_index--))
		{
			p->ll_index++;
			close(fd);
			return ;
		}
		close(fd);
		home_key();
		clear_screen();
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		paste_of_mouse(p);
	}
}

void	ft_history_downkey(t_package *p)
{
	int		fd;
	char	*tmp;

	if (p->ll_index > -1)
	{
		home_key();
		clear_screen();
		ft_strdel(&p->line);
		p->line = ft_strnew(1);
		fd = open(p->path, O_RDONLY);
		if (!gline(fd, &tmp, ++p->ll_index))
		{
			--p->ll_index;
			close(fd);
			return ;
		}
		close(fd);
		home_key();
		clear_screen();
		ft_bzero(p->buffer, BUFFER_SIZE);
		ft_memcpy(p->buffer, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		paste_of_mouse(p);
	}
}
