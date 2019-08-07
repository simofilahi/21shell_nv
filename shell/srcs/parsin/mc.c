/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:43:29 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 20:56:53 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t__mc	*mc_lst(char **mc)
{
	t__mc	*lst;
	t__mc	*head;
	t__mc	*predator;
	int		i;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	i = 0;
	while (i < count_tab(mc))
	{
		lst->cmd = ft_strsplit(mc[i], -4);
		i++;
		if (i == 1)
			head = lst;
		if (!(lst->next = (t__mc*)malloc(sizeof(t__mc))))
			return (NULL);
		predator = lst;
		lst = lst->next;
	}
	predator->next = NULL;
	return (head);
}

t__mc	*mc_maker(char *line, t_env *env)
{
	char		**slice;
	char		*parsed;
	t__mc		*lst;

	parsed = parsin(line, env);
	slice = ft_strsplit(parsed, -3);
	ft_strdel(&parsed);
	lst = mc_lst(slice);
	ft_free2d(slice);
	return (lst);
}
