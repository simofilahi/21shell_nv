/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:50:13 by aariss            #+#    #+#             */
/*   Updated: 2019/07/17 15:31:03 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deathly_hallows(t_info *lst_demi)
{
	int	fd;
	t_info	*lst;
	int		t;
//	int		tmp;
	int		keeper;
	int		fds;
//	struct stat	buffer;

	t = 0;
	keeper = 0;
	lst = lst_demi;
	while (lst)
	{
		if (ft_strcmp(lst->file, "no_file") == 0 && ft_strcmp(lst->file, "-1") != 0)
		{
			if (lst->sfd && lst->dfd)
			{
				fds = dup2(lst->dfd, lst->sfd);
				if (fds == -1)
				{
					ft_putendl_fd(ft_strjoin(ft_strjoin("21sh: ", ft_itoa(lst->dfd)),": bad file descriptor"), 2);
					return (0);
				}
			}
		}
		lst = lst->next;
	}
	while (lst_demi)
	{
		if (ft_strcmp(lst_demi->file, "no_file") != 0 && ft_strcmp(lst_demi->file, "-1") != 0)
		{
			if (lst_demi->read_meth == 1)
			{
				fd = open(lst_demi->file, O_CREAT|O_RDWR|O_TRUNC, 0644);
				t = 1;
			}
			else if (lst_demi->read_meth == 2)
			{
				fd = open(lst_demi->file, O_CREAT|O_RDWR|O_APPEND, 0644);
				t = 1;
			}
			else if (lst_demi->read_meth == -2)
			{
				fd = open(lst_demi->file, O_RDONLY, 0644);
				t = 2;
			}
			if (t == 1)
				(lst_demi->sfd) ? dup2(fd, lst_demi->sfd) :	dup2(fd, 1);
			else if (t == 2)
			{
				/* NOT YET DONE */
				dup2(fd, 0);
			}
		}
		lst_demi = lst_demi->next;
	}
	return (1);
}

void	master_of_death(t_holder *h)
{
	t_god *lst;

	lst = h->lst;
	while (lst)
	{
		child_pid(lst->cmd, lst, &h->head_ref, 1);
		lst = lst->next;
	}
//	ft_putendl("The true master does not seek to run away from Death. He accepts that he must die, and understands that there are far, far worse things in the living world than dying.");
}

void	darlin_g(t_holder *h)
{
	int	j;

	j = 0;
	if (count_lstgod(h->lst) == 1 && (h->lst->demi_god->sfd == -1))
	{
		if ((j = own_commands(h->lst->cmd[0])))
			builtin_cmds(h, j);
		else
			child_pid(h->lst->cmd, h->lst, &h->head_ref, 0);
	}
	else
		master_of_death(h);
}
