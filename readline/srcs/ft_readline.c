/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:41:28 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/29 16:02:55 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** check any key pressed;
*/

void		get_input_3(t_package *p, int sum, t_his **his_tail)
{
	if (sum == PASTEKEY)
	{
		p->flag_hislastline = 1;
		paste_key(p);
	}
	else if (sum >= 32 && sum <= 126)
	{
		p->flag_hislastline = 1;
		print_readablechar(p);
	}
	else if (sum == BACKSPACE && checking(p->line, p->index, 2))
	{
		p->flag_hislastline = 1;
		backspace_key(p);
	}
	else if (sum == KEYDOWN)
		ft_history_downkey(p, his_tail);
	else if ((p->buffer[0] >= 32 && p->buffer[0] <= 126) &&\
			(p->buffer[1] >= 32 && p->buffer[1] <= 126))
	{
		p->flag_hislastline = 1;
		paste_of_mouse(p);
	}
}

/*
** check any key pressed;
*/

void		get_input_2(t_package *p, int sum, t_his **his_tail)
{
	char *tmp;

	tmp = NULL;
	if (sum == COPYKEY_BC)
		copy_before_cursor_key(&p->holdcopy, p->line, p->index);
	else if (sum == COPYKEY_AC)
		copy_after_cursor_key(&p->holdcopy, p->line, p->index);
	else if (sum == CUTKEY)
		cut_line_key(&p->holdcopy, &p->line);
	else if (sum == CUTKEY_BC)
		cut_before_cursor_key(&p->holdcopy, &p->line, p->index);
	else if (sum == CUTKEY_AC)
		cut_after_cursor_key(&p->holdcopy, &p->line, p->index);
	else if (sum == KEYUP)
	{
		if ((ft_strlen(p->line) > 0 ) && p->flag_hislastline)
		{
			tmp = p->hisline_tmp;
			p->hisline_tmp = ft_strdup(p->line);
			(tmp != NULL) ? ft_strdel(&tmp) : 0;
		}
		p->flag_hislastline = 0;
		ft_history_upkey(p, his_tail);
	}
	else
		get_input_3(p, sum, his_tail);
}

/*
** check any key pressed;
*/

void		get_input_1(t_package *p, int sum, t_his **his_tail)
{
	if (sum == RIGHTKEY && checking(p->line, p->index, 1))
		right_key(p);
	else if (sum == LEFTKEY && checking(p->line, p->index, 2))
		left_key(p);
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
	if (sum == COPYKEY)
		copy_line_key(&p->holdcopy, p->line);
	else
		get_input_2(p, sum, his_tail);
}

/*
** read data from stdin & check any key pressed;
*/

t_package	*get_input(char *s, t_package *p, t_his *his_tail, t_his *tail_ptr)
{
	int	sum;

	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\033[0m", 1);
	while ((read(0, p->buffer, BUFFER_SIZE)) > 0)
	{
		if (g_signal_num == 2)
			p = handler_ctrl_c(&his_tail, tail_ptr);
		sum = *((int *)p->buffer);
		if (sum == 10)
			break ;
		else if (sum == CTRL_D)
		{
			if (!(ctrl_d(p)))
				break ;
		}
		else if (sum == CTRL_L)
			p = ctrl_l(s, p, his_tail);
		else
			get_input_1(p, sum, &his_tail);
		ft_bzero(p->buffer, BUFFER_SIZE);
	}
	return (joinnewline(p, sum));
}

/*
** main function;
*/

char		*ft_readline(char prompt[3], t_his *his_tail, int his_flag)
{
	t_package	*p;
	t_his		*tail_ptr;
	char		*line;

	line = NULL;
	tail_ptr = his_tail;
	p = init_structure_members(tail_ptr, his_flag);
	if (termcap_config())
		p = get_input(&prompt[0], p, his_tail, tail_ptr);
	normal_mode();
	if (ft_strlen(p->line) > 0)
		line = ft_strdup(p->line);
	free_structure_rl(p);
	return (line);
}
