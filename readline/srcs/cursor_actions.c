/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 22:18:39 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/17 16:40:42 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** - clear screen from current position of cursor;
*/

void		clear_screen(void)
{
	tputs(CL_SCREEN, 1, my_putchar);
}

/*
** - move cursor up/down/left/right;
*/

void		move_cursor(int ch)
{
	write(1, &ch, 4);
}

/*
** - handler of ctrl_c when catched;
** - init new structure that hold new information
**   about position cursor(x,y) and other things;
*/

t_package	*handler_ctrl_c(void)
{
	char		*tmp[BUFFER_SIZE];
	t_package	*p;	
	t_his		**his_tail;

	p = cloud(NULL);
	normal_mode();
	his_tail = &p->his_tail;
	ft_memcpy(tmp, p->buffer, BUFFER_SIZE);
	ft_strdel(&p->line);
	ft_strdel(&p->holdcopy);
	free(p);
	p = init_structure_members(*his_tail);
	ft_memcpy(p->buffer, tmp, BUFFER_SIZE);
	g_signal_num = 3;
	return (p);
}

/*
** - move the cursor to the upper left corner of the screen;
** - reprint line if not null;
*/

t_package	*ctrl_l(char *prompt, t_package *p)
{
	char	*tmp;
	t_his   **his_tail;

	end_key(p);
	normal_mode();
	tmp = (p->line[0] != '\0') ? ft_strdup(p->line) : NULL;
	ft_strdel(&p->line);
	ft_strdel(&p->holdcopy);
	his_tail = &p->his_tail;
	free(p);
	tputs(HC, 1, my_putchar);
	clear_screen();
	p = init_structure_members(*his_tail);
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("\033[0m", 1);
	if (!tmp)
		return (p);
	while (*tmp)
		(p->buffer[0] = *tmp++) ? print_readablechar(p) : 0;
	return (p);
}

/*
** - when pressed enter;
*/

t_package	*joinnewline(t_package *p, int sum)
{
	char	*tmp;

	tmp = NULL;
	end_key(p);
	if (sum == 10)
	{
		tmp = p->line;
		p->line = ft_strjoin(p->line, "\n");
		ft_strdel(&tmp);
	}
	return (p);
}
