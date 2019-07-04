/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 22:18:39 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:31:33 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	clear_screen(void)
{
	tputs(CL_SCREEN, 1, my_putchar);
}

void	move_cursor(int ch)
{
	write(1, &ch, 4);
}

t_package	*handler_ctrl_c()
{
	t_package *p;
	char	  *path;
	char	  *tmp[BUFFER_SIZE];
	int		  ll_index;

	p = cloud(NULL);
	normal_mode();
	path = ft_strdup(p->path);
	ll_index = p->ll_index;
	ft_memcpy(tmp, p->buffer, BUFFER_SIZE);
	ft_strdel(&p->line);
	ft_strdel(&p->holdcopy);
	ft_strdel(&p->path);
	free(p);
	p = init_structure_members(path, ll_index);
	ft_memcpy(p->buffer, tmp, BUFFER_SIZE);
	g_signal_num = 1;
	return (p);
}
