/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:00:58 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 12:21:32 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int		ctrl_d(void)
{
	t_package *p;

	p = cloud(NULL);
	if (!(p->index == (int)ft_strlen(p->line) &&\
		 ft_strlen(p->line) > 0) ||\
		 p->line[p->index - 1] == '\n')
	{
		if (ft_strlen(p->line) == 0)
			return (0);
		delete_element(p->line, p->index);
		tputs(SC, 1, my_putchar);
		clear_screen();
		print_line(p->line, p->index);
		tputs(RC, 1, my_putchar);
	}
	return (1);
}

int		checking(char *line, int index, int key)
{
	if (key == 1)
	{
		if (ft_strlen(line) != 0 && index >= 0 &&\
				!((int)ft_strlen(line) == index))
			return (TRUE);
		return (FALSE);
	}
	else if (key == 2)
	{
		if (index > 0 && ft_strlen(line) != 0)
			return (TRUE);
		return (FALSE);
	}
	else if (key == 3)
	{
		if (index != (int)ft_strlen(line))
			return (TRUE);
		return (FALSE);
	}
	return (FALSE);
}

void	init_structure_members(char *path, int ll_index)
{
	t_package		*p;

	p = ft_memalloc(sizeof(struct s_package));
	p->len = 20;
	p->line = ft_strnew(p->len);
	p->holdcopy = ft_strnew(1);
	p->path = path;
	p->ll_index = ll_index;
	p->oldconf = termios_config();
	get_pos(&p->posy, &p->posx);
	if (p->posx > 1)
	{
		tputs(SRV, 1, my_putchar);
		ft_putchar_fd('%', 1);
		tputs(ERV, 1, my_putchar);
		ft_putchar_fd('\n', 1);
	}
	p->posy -= 1;
	p->posx = 3;
	p->init_y = p->posy;
	p->last_y = p->init_y;
	ft_bzero(p->buffer, BUFFER_SIZE);
	ioctl(0, TIOCGWINSZ, &p->w);
	cloud(p);
}

void	print_line(char *line, int index)
{
	while (line[index])
		ft_putchar_fd(line[index++], 1);
}

void paste_of_mouse(t_package *p)
{
	int i;
	char *string;

	string = ft_strdup(p->buffer);
	i = -1;
	while (string[++i])
	{
		ft_bzero(p->buffer, BUFFER_SIZE);
		if ((string[i] >= 32 && string[i] <= 126) || string[i] == '\n')
		{
			p->buffer[0] = string[i];
			print_readablechar(p);
		}
	}
	free(string);
}

