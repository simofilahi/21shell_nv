/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_master.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:39:38 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 11:41:34 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		open_file(t_info *lst)
{
	int	fd;

	fd = 0;
	if (lst->read_meth != 2 && lst->read_meth > 0)
		fd = open(lst->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (lst->read_meth == 2)
		fd = open(lst->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (lst->read_meth == -2)
		fd = open(lst->file, O_RDONLY, 0644);
	return (fd);
}

void	heredoc_broker(int *fds, t_info *lst)
{
	pipe(fds);
	dup2(fds[0], 0);
	close(fds[0]);
	ft_putstr_fd(lst->file, fds[1]);
	close(fds[1]);
}

void	redirect_to_file(t_info *lst, int fd)
{
	int	fds[2];

	if (lst->read_meth == 1 || lst->read_meth == 2)
	{
		(lst->sfd) ? dup2(fd, lst->sfd) : dup2(fd, 1);
		close(fd);
	}
	else if (lst->read_meth == 3 || lst->read_meth == 4)
	{
		if (lst->sfd == 2)
			dup2(fd, lst->sfd);
		else
		{
			dup2(fd, 1);
			dup2(fd, 2);
		}
		close(fd);
	}
	else if (lst->read_meth == -2)
	{
		dup2(fd, 0);
		close(fd);
	}
	else if (lst->read_meth == -3)
		heredoc_broker(fds, lst);
}

int		redirect_to_fd(t_info *lst)
{
	int		fds;
	char	*itoa;

	if (lst->read_meth == -777)
		return (0);
	if (!lst->file)
	{
		if (lst->sfd && lst->dfd)
		{
			fds = dup2(lst->dfd, lst->sfd);
			if (fds == -1)
			{
				itoa = error_assembly(lst->dfd);
				ft_putendl_fd(itoa, 2);
				ft_strdel(&itoa);
				return (0);
			}
		}
		if (lst->read_meth == 5)
			close(lst->sfd);
	}
	return (1);
}

int		deathly_hallows(t_info *lst_demi, t_info **head)
{
	int		fd;
	t_info	*lst;

	lst = lst_demi;
	*head = lst_demi;
	while (lst)
	{
		if (!redirect_to_fd(lst_demi))
			return (0);
		lst = lst->next;
	}
	while (lst_demi)
	{
		if (lst_demi->file != NULL && ft_strcmp(lst_demi->file, "-1") != 0)
		{
			fd = open_file(lst_demi);
			redirect_to_file(lst_demi, fd);
		}
		lst_demi = lst_demi->next;
	}
	return (1);
}
