/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 22:14:58 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 21:07:07 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		got_no_token(char *kratos)
{
	int	i;

	i = 0;
	while (kratos[i])
	{
		if (ft_istoken(kratos[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_iswhite(char c)
{
	if (c == ' ' || c == '\t'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r')
		return (1);
	return (0);
}

int		aggreg_check(char *kratos, int *i, int def)
{
	if (def == 0)
	{
		*i = *i + 2;
		if (ft_isdigit(kratos[*i]))
		{
			while (ft_isdigit(kratos[*i]))
				(*i)++;
			if (ft_isalpha(kratos[*i]))
				return (1);
			else
				return (2);
		}
		else if (kratos[*i] == '-')
			return (2);
		return (1);
	}
	else if (def == 1)
	{
		*i = *i + 2;
		if (ft_isdigit(kratos[*i]))
			return (2);
	}
	return (0);
}

int		digit_token_check(char *kratos, int *i, int def)
{
	if (def)
	{
		while (ft_isdigit(kratos[*i]))
			(*i)++;
		if (kratos[*i] == '&' && kratos[(*i) + 1] == '>')
			return (1);
		else if (kratos[*i] == '>' && kratos[(*i) + 1] == '&')
			return (aggreg_check(kratos, &(*i), 0));
		else if (kratos[*i] == '<' && kratos[(*i) + 1] == '&')
			return (aggreg_check(kratos, &(*i), 1));
		else if (kratos[*i] == '>' || kratos[*i] == '<')
			return (1);
	}
	return (0);
}

int		ultimate_check(char *kratos)
{
	int	i;

	i = 0;
	if (ft_strcmp(kratos, ">") == 0
			|| ft_strcmp(kratos, "<") == 0
			|| ft_strcmp(kratos, ">>") == 0
			|| ft_strcmp(kratos, "<<") == 0
			|| ft_strcmp(kratos, "&>") == 0)
		return (1);
	else if (ft_isdigit(kratos[i]) && got_token_after_digit(kratos + i))
		return (digit_token_check(kratos, &i, 1));
	else if (kratos[i] == '<' && kratos[i + 1] == '&')
	{
		i = i + 2;
		if (ft_isdigit(kratos[i]))
			return (1);
	}
	else if (kratos[i] == '>' && kratos[i + 1] == '&')
		return (1);
	return (0);
}
