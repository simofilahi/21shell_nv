/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:01:22 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 21:12:59 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		retrieve_the_digit(char *name, int delimiter)
{
	if (delimiter == 0)
		return (ft_atoi(name));
	while (ft_isdigit(*name))
		name++;
	while (ft_istoken(*name))
		name++;
	return (ft_atoi(name));
}

int		count_arg(char **kratos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (kratos[i])
	{
		if (!ultimate_check(kratos[i]))
			count++;
		i++;
	}
	return (count + 1);
}

void	print_lstra(t_cmd *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			ft_putendl(lst->cmd[i]);
			i++;
		}
		if (lst->red != NULL)
		{
			while (lst->red)
			{
				if (lst->red->file)
					ft_putstr(lst->red->file);
				else
				{
					ft_putstr("NULL");
					ft_putchar('.');
				}
				ft_putnbr(lst->red->sfd);
				ft_putchar('.');
				ft_putnbr(lst->red->dfd);
				ft_putchar('.');
				ft_putnbr(lst->red->read_meth);
				lst->red = lst->red->next;
				ft_putchar('\n');
			}
		}
		lst = lst->next;
	}
}
