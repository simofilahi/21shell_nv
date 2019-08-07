/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:24:18 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 15:27:22 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		kill_pid(t_childs **child_lst, t_childs *c_head, int *keeper)
{
	if ((*child_lst)->child != 0)
	{
		g_signal_num = 0;
		waitpid((*child_lst)->child, 0, 0);
		g_signal_num = 1;
	}
	while (c_head)
	{
		if (c_head->child != 0)
			kill(c_head->child, 9);
		c_head = c_head->next;
	}
	cheap_trick(keeper, 1);
}

t_childs	*create_child(pid_t child_pid, int *t)
{
	t_childs *new;

	if (!(new = (t_childs*)malloc(sizeof(t_childs))))
		return (0);
	new->child = child_pid;
	new->next = NULL;
	(*t)++;
	return (new);
}
