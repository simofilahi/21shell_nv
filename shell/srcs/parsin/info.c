/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 09:49:04 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 16:25:22 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	read_define(char *kratos, t_info **one)
{
	char	*toto;

	if (ft_strchr(kratos, '<')
			&& !ft_strchr(kratos, '-') && (!ft_strchr(kratos, '&')))
		(*one)->read_meth = -2;
	else if (ft_strchr(kratos, '>')
			&& !ft_strchr(kratos, '-') && (!ft_strchr(kratos, '&')))
		(*one)->read_meth = 1;
	else if ((toto = ft_strchr(kratos, '<')) && ft_strchr(toto, '&'))
		(*one)->read_meth = -4;
	else if ((toto = ft_strchr(kratos, '>')) && ft_strchr(toto, '&')
			&& !ft_strchr(toto, '-'))
		(*one)->read_meth = 3;
	else if ((toto = ft_strchr(kratos, '&')) && ft_strchr(toto, '>'))
		(*one)->read_meth = 4;
	else if ((toto = ft_strchr(kratos, '>'))
			&& (toto = ft_strchr(toto, '&')) && ft_strchr(toto, '-'))
		(*one)->read_meth = 5;
}

void	no_redirection(int def, t_info **one)
{
	if (def == 0)
	{
		(*one)->file = ft_strdup("-1");
		(*one)->sfd = -1;
		(*one)->dfd = -1;
		(*one)->read_meth = -1;
	}
	else if (def == 777)
	{
		(*one)->file = ft_strdup("-1");
		(*one)->sfd = -1;
		(*one)->dfd = -1;
		(*one)->read_meth = -777;
	}
}

void	read_methods(char *kratos, t_info **one)
{
	if (alright_token(kratos) != 1 && ft_strchr(kratos, '&'))
		(*one)->read_meth = 0;
	else if (alright_token(kratos) == 1)
		read_define(kratos, &(*one));
	else if (alright_token(kratos) == 2 && ft_strchr(kratos, '<')
			&& (!ft_strchr(kratos, '&') || !ft_strchr(kratos, '-')))
		(*one)->read_meth = -3;
	else if (alright_token(kratos) == 2 && ft_strchr(kratos, '>')
			&& (!ft_strchr(kratos, '&') || !ft_strchr(kratos, '-')))
		(*one)->read_meth = 2;
	else
		(*one)->read_meth = 0;
}

t_info	*create_info(char *kratos, char *file, t_index *l, t_index def)
{
	t_info	*one;
	int		f;

	if (!(one = (t_info*)malloc(sizeof(t_info))))
		return (0);
	one->file = NULL;
	f = ft_strlen(kratos) - 1;
	if (def.i == 1)
	{
		if (def.j == 1)
			if (file)
				one->file = ft_strdup(file);
		one->sfd = (ft_isdigit(kratos[0])) ? retrieve_the_digit(kratos, 0) : 0;
		one->dfd = (ft_isdigit(kratos[f])) ? retrieve_the_digit(kratos, 1) : 0;
		read_methods(kratos, &one);
	}
	else if (def.i == 0 || def.i == 777)
		no_redirection(def.i, &one);
	one->next = NULL;
	l->v++;
	return (one);
}
