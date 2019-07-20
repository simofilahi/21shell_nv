/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:26:05 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/17 15:08:59 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void	get_pos_1(int *y, int *x, int *i, char *buf)
{
	int	pow;

	*i -= 2;
	pow = 1;
	*x = 0;
	*y = 0;
	while (buf[(*i)] != ';')
	{
		*x = *x + (buf[(*i)] - '0') * pow;
		(*i)--;
		pow *= 10;
	}
	*i -= 1;
	pow = 1;
	while (buf[(*i)] != '[')
	{
		*y = *y + (buf[(*i)] - '0') * pow;
		(*i)--;
		pow *= 10;
	}
}

int		get_pos(int *y, int *x)
{
	char	buf[30];
	char	ch;
	int		ret;
	int		i;

	ft_bzero(buf, 30);
	tputs("\033[6n", 1, my_putchar);
	ch = 0;
	i = 0;
	while (ch != 'R')
	{
		ch = 0;
		ret = read(0, &ch, 1);
		if (!ret)
			return (-1);
		buf[i] = ch;
		i++;
	}
	get_pos_1(y, x, &i, &buf[0]);
	return (0);
}

int		count_lines(char *line, int ws_col)
{
	int	count;
	int	posx;
	int	i;

	i = 0;
	count = 0;
	posx = 3;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			count++;
			posx = -1;
		}
		if (posx + 1 == ws_col)
		{
			posx = -1;
			count++;
		}
		i++;
		posx++;
	}
	return (++count);
}

int		new_line_is_found(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '\n')
			return (1);
	return (0);
}
