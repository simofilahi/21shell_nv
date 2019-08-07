/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:50:13 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 15:24:10 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	pipe_master(t_cmd *lst, int *keeper, int *backup_zero)
{
	int			fds[2];

	dup2(*backup_zero, 0);
	close(*backup_zero);
	if (lst->next)
	{
		pipe(fds);
		*backup_zero = fds[0];
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else
	{
		dup2(keeper[1], 1);
		dup2(keeper[2], 2);
	}
}

void	cheap_trick(int *keeper, int trick)
{
	if (trick == 0)
	{
		keeper[0] = dup(0);
		keeper[1] = dup(1);
		keeper[2] = dup(2);
	}
	if (trick == 1)
	{
		dup2(keeper[0], 0);
		dup2(keeper[1], 1);
		dup2(keeper[2], 2);
		close(keeper[0]);
		close(keeper[1]);
		close(keeper[2]);
	}
}

void	pid_keeper(t_childs **child_lst, t_childs **c_head, int get, int *t)
{
	if (*t == 0)
	{
		(*child_lst) = create_child(get, &(*t));
		(*c_head) = (*child_lst);
	}
	else
	{
		(*child_lst)->next = create_child(get, &(*t));
		(*child_lst) = (*child_lst)->next;
	}
}

void	master_of_death(t_holder *h, int *keeper, t_childs **child_lst, int *t)
{
	int			backup_zero;
	t_cmd		*lst;
	t_info		*head;
	t_childs	*c_head;
	pid_t		get;

	backup_zero = dup(0);
	lst = h->lst;
	while (lst)
	{
		pipe_master(lst, keeper, &backup_zero);
		if (!deathly_hallows(lst->red, &head))
			return ;
		if (is_a_builtin(lst->cmd[0]) && (h->lst = lst))
			builtin_cmds(h, own_commands(lst->cmd[0]));
		else
			child_pid(lst->cmd, lst, &h->head_ref, &get);
		pid_keeper(&(*child_lst), &c_head, (is_a_builtin(lst->cmd[0]))
				? 0 : get, &(*t));
		lst = lst->next;
	}
	kill_pid(&(*child_lst), c_head, keeper);
	h->lst->red = head;
}

void	darlin_g(t_holder *h)
{
	int			t;
	int			keeper[3];
	t_childs	*child_lst;

	t = 0;
	cheap_trick(keeper, 0);
	master_of_death(h, keeper, &child_lst, &t);
}
