/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voidy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuser <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:22:39 by macuser           #+#    #+#             */
/*   Updated: 2019/07/03 15:17:05 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_info	*add_one(char *kratos, int *t)
{
	t_info *one;
	int		f;

	if (!(one = (t_info*)malloc(sizeof(t_info))))
		return (0);
	f = ft_strlen(kratos) - 1;
	one->file = ft_strdup("NADAA");
	one->sfd = (ft_isdigit(kratos[0])) ? retrieve_the_digit(kratos, 0) : 0;
	one->dfd = (ft_isdigit(kratos[f])) ? retrieve_the_digit(kratos, 1) : 0;
	one->read_meth = 0;
	one->next = NULL;
	(*t)++;
	return (one);
}

t_god	*godly_void(char **kratos, t_defined *tokens)
{
	t_god		*new;
	t_info		*head_demi;
	int			i;
	int			j;
	int			t;

	if (!(new = (t_god*)malloc(sizeof(t_god))))
		return (0);
	if (!(new->cmd = (char**)malloc(sizeof(char*) * (pipecount(kratos, 1) + 1))))
		return (0);
	i = 0;
	j = 0;
	t = 0;
	while (kratos[i])
	{
		if (!is_one_of_them(kratos[i], tokens))
		{
			new->cmd[j] = ft_strdup(kratos[i]);
			j++;
		}
		else
		{
			if (t != 0)
			{
				new->demi_god->next = add_one(kratos[i], &t);
				new->demi_god = new->demi_god->next;
			}
			else
			{
				new->demi_god = add_one(kratos[i], &t);
				head_demi = new->demi_god;
			}
		}
		i++;
	}
	new->cmd[j] = NULL;
	new->next = NULL;
	new->demi_god = head_demi;
	return (new);
}

void	print_lstra(t_god *lst)
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
		if (lst->demi_god != NULL)
		{
			ft_putstr(lst->demi_god->file);
			ft_putchar('.');
			ft_putnbr(lst->demi_god->sfd);
			ft_putchar('.');
			ft_putnbr(lst->demi_god->dfd);
			ft_putchar('.');
			ft_putnbr(lst->demi_god->read_meth);
		}
		ft_putchar('\n');
		lst = lst->next;
	}
}

void	voidy(char **cmd)
{
	int			i;
	int			count;
	char		**kratos;
	t_defined	*tokens;
	t_god		*lst;
	t_god		*head;

	i = 0;
	count = pipecount(cmd, 0);
//	ft_putnbr(count);
	tokens = init_cases();
	while (i < count)
	{
		ft_putendl("toto");
		kratos = get_piped(cmd, i);
		ft_putendl("tutu");
		if (lst->next == NULL)
		{
			lst->next = godly_void(kratos, tokens);
			lst = lst->next;
		}
		else
		{
			lst = godly_void(kratos, tokens);
			head = lst;
		}
		i++;
	}
	print_lstra(head);
}
