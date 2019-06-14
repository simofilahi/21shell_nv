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
