/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:41:28 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 15:47:50 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** check any key pressed
*/

void	get_input_2(t_package *p, int sum)
{
	if (sum == COPYKEY)
		copy_line_key(&p->holdcopy, p->line);
	else if (sum == COPYKEY_BC)
		copy_before_cursor_key(&p->holdcopy, p->line, p->index);
	else if (sum == COPYKEY_AC)
		copy_after_cursor_key(&p->holdcopy, p->line, p->index);
	else if (sum == CUTKEY)
		cut_line_key(&p->holdcopy, &p->line);
	else if (sum == CUTKEY_BC)
		cut_before_cursor_key(&p->holdcopy, &p->line, p->index);
	else if (sum == CUTKEY_AC)
		cut_after_cursor_key(&p->holdcopy, &p->line, p->index);
	else if (sum == PASTEKEY)
		paste_key(p);
	else if (sum == KEYUP)
		ft_history_upkey(p);
	else if (sum == KEYDOWN)
		ft_history_downkey(p);
	else if ((p->buffer[0] >= 32 && p->buffer[0] <= 126) &&\
			(p->buffer[1] >= 32 && p->buffer[1] <= 126))
	{
		paste_of_mouse(p);
	}
}

/*
** check any key pressed
*/

void	get_input_1(t_package *p, int sum)
{
	if (sum >= 32 && sum <= 126)
		print_readablechar(p);
	else if (sum == RIGHTKEY && checking(p->line, p->index, 1))
		right_key(p);
	else if (sum == LEFTKEY && checking(p->line, p->index, 2))
			left_key(p);
	else if (sum == BACKSPACE && checking(p->line, p->index, 2))
		backspace_key(p);
	else if (sum == HOMEKEY && p->index > 0)
		home_key();
	else if (sum == ENDKEY && checking(p->line, p->index, 3))
		end_key(p);
	else if (sum == FORWARDKEY && checking(p->line, p->index, 3))
		forwardkey(p);
	else if (sum == BACKWARDKEY && p->index > 0)
		backwardkey(p);
	else if (sum == ALT_UPKEY)
		ft_alt_upkey(p);
	else if (sum == ALT_DOWNKEY)
		ft_alt_downkey(p);
	else
		get_input_2(p, sum);
}

/*
** read data from stdin & check any key pressed
*/

t_package	*get_input(char *s, t_package *p)
{
	int		sum;
	char	*tmp;

	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\033[0m", 1);
	while ((read(0, p->buffer, BUFFER_SIZE)) > 0)
	{
		if (g_signal_num == 2)
			p = handler_ctrl_c(p);
		sum = *((int *)p->buffer);
		if (sum == 10)
			break ;
		else if (sum == CTRL_D)
		{
			if (!(ctrl_d(p)))
				break ;
		}
		else
			get_input_1(p, sum);
		ft_bzero(p->buffer, BUFFER_SIZE);
	}
	end_key(p);
	if (sum == 10)
	{
		tmp = p->line;
		p->line = ft_strjoin(p->line, "\n");
		ft_strdel(&tmp);
	}
	return (p);
}

char	*ft_readline(char prompt[3], char *path, int ll_index)
{
	t_package	*p;
	char		*line;

	line = NULL;
	p = init_structure_members(path, ll_index);
	if (termcap_config())
		p = get_input(&prompt[0], p);
	normal_mode();
	if (ft_strlen(p->line) > 0)
		line = ft_strdup(p->line);
	ft_strdel(&p->line);
	ft_strdel(&p->holdcopy);
	ft_strdel(&p->path);
	free(p);
	return (line);
}