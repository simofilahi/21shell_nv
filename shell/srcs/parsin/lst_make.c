/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:39:26 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 19:19:12 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sure_darlin(char **kratos, t_cmd **lst, t_info **head, t_index *l)
{
	t_index	def;

	if (l->v == 0)
	{
		def.i = 0;
		def.j = 0;
		(*lst)->red = create_info(kratos[l->i], NULL, &(*l), def);
		*head = (*lst)->red;
	}
	if (l->v == 777)
	{
		def.i = 777;
		def.j = 0;
		(*lst)->red = create_info(kratos[l->i], NULL, &(*l), def);
		*head = (*lst)->red;
	}
}

void	not_known_as_if(char **kratos, t_cmd **lst, int *t)
{
	t_index	l;
	t_info	*head;

	l.i = 0;
	l.j = 0;
	l.v = 0;
	if (!((*lst)->cmd = (char **)malloc(sizeof(char *) * count_arg(kratos))))
		return ;
	while (kratos[l.i])
	{
		if (ultimate_check(kratos[l.i]) == 1)
			add_file(&(*lst), &head, kratos, &l);
		else if (ultimate_check(kratos[l.i]) == 2)
			add_casual(&(*lst), &head, kratos, &l);
		else if (got_no_token(kratos[l.i]))
			(*lst)->cmd[l.j++] = ft_strdup(kratos[l.i]);
		l.i++;
	}
	sure_darlin(kratos, &(*lst), &head, &l);
	(*lst)->cmd[l.j] = NULL;
	(*lst)->red = head;
	(*t)++;
}

void	tilde_fix(char **cmd, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '~' && cmd[i][1] != '~')
		{
			tmp = cmd[i];
			cmd[i] = ft_strjoin(get_var("HOME=", &env), cmd[i] + 1);
			ft_strdel(&tmp);
		}
		i++;
	}
}

t_cmd	*well_you_know(char **cmd, t_cmd **lst, int *t, t_env *env)
{
	t_cmd	*head;
	t_cmd	*predictor;
	char	**kratos;
	int		i;

	i = 0;
	while (cmd[i])
	{
		kratos = ft_strsplit(cmd[i], -1);
		tilde_fix(kratos, env);
		if (*t == 0)
			head = *lst;
		not_known_as_if(kratos, &(*lst), &(*t));
		if (!((*lst)->next = (t_cmd*)malloc(sizeof(t_cmd))))
			return (0);
		predictor = (*lst);
		(*lst) = (*lst)->next;
		ft_free2d(kratos);
		i++;
	}
	predictor->next = NULL;
	free(*lst);
	return (head);
}

t_cmd	*last_splice(t__mc **old_lst, t_env *env)
{
	t_cmd	*lst;
	t_cmd	*head;
	int		t;

	if (!(lst = (t_cmd*)malloc(sizeof(t_cmd))))
		return (0);
	t = 0;
	head = well_you_know((*old_lst)->cmd, &lst, &t, env);
	(*old_lst) = (*old_lst)->next;
	return (head);
}
