/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:11:50 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 10:17:32 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_main_lst(t_cmd *lst)
{
	t_cmd	*tmp;
	t_info	*tmp_demi;

	while (lst)
	{
		ft_free2d(lst->cmd);
		while (lst->red)
		{
			tmp_demi = lst->red;
			lst->red = lst->red->next;
			if (tmp_demi->file)
				ft_strdel(&tmp_demi->file);
			free(tmp_demi);
		}
		free(lst->red);
		lst->red = NULL;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	free(lst);
	lst = NULL;
}
