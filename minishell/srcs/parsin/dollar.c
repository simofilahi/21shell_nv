/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:42:23 by aariss            #+#    #+#             */
/*   Updated: 2019/06/19 14:43:08 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char    *dollar_get_simple(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strfchr(env->var, '=');
		if (ft_strncmp(name, env->var, (ft_strlen(env->var) - 1)) == 0)
		{
			*ptr = str;
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char    *dollar_get_quoted(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strfchr(env->var, '=');
		if (ft_strncmp(name, str, ft_strlen(str)) == 0)
		{
			*ptr = str;
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*dollar_handle_simple(char *toto, char *line, int *i, t_env *env)
{
	char	*str;
	char	*ptr;

	ptr = NULL;
	str = dollar_get_simple(line + *i + 1, env, &ptr);
	if (str)
	{
		toto = ft_strjoin(toto, str);
		(*i) = (*i) + ft_strlen(ptr);
	}
	else
	{
		(*i)++;
		while (ft_isalpha(line[*i]))
			(*i)++;
	}
	return (toto);
}

char	*dollar_handle_quoted(char *toto, char *line, int *i, int quote, t_env *env)
{
	char	*str;
	char	*ptr;
	char	*kali;

	if (quote == 39)
		toto = ft_joinchar(toto, '$');
	else if (quote == '"')
	{ 
		/*  MAY BE MORE USEFULL TO CALL THE FUNCTION dollar_handle_simple HERE INSTEAD...JUST A THOUGHT  */
		ptr = NULL;
		kali = ft_strfchr_alpha(line + *i + 1);
		str = dollar_get_quoted(kali, env, &ptr);
		if (str)
		{
			toto = ft_strjoin(toto, str);
			(*i) = (*i) + ft_strlen(ptr);
		}
		else
		{
			(*i)++;
			while (ft_isalpha(line[*i]))
				(*i)++;
			(*i)--;
		}
	}
	return (toto);
}
