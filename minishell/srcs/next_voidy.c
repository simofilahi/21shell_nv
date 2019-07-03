/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_voidy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 09:47:33 by aariss            #+#    #+#             */
/*   Updated: 2019/07/03 14:44:38 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipecount(char **argv, int delim)
{
	int			i;
	int			len;
	int			counter;

	i = 0;
	counter = 0;
	len = 0;
	while (argv[i])
	{
		if (delim == 1)
		{
			if (ft_strcmp(argv[i], "|") != 0)
				counter++;
		}
		else if (delim == 0)
		{
			if (ft_strcmp(argv[i], "|") == 0)
				len = 0;
			else if (++len == 1)
				counter++;
		}
		i++;
	}
	if (counter)
		return (counter);
	return (0);
}

char	**get_piped(char **argv, int index)
{
	int	 len;
	int  i;
	int  j;
	int  f;
	char **arg;

	len = count_words(argv, index);
	if (!(arg = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	f = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "|") != 0)
		{	
			if (index == f)
			{
				arg[j] = ft_strdup(argv[i]);
				j++;
			}
		}
		else 
		{
			if (index == f)
			{
				return (arg);
			}
			f++;
		}
		i++;
	}
	return (arg);
}

int		retrieve_the_digit(char *name, int	delimiter)
{
	if (delimiter == 0)
		return (ft_atoi(name));
	return (ft_atoi(name + ft_strlen(name) - 1));
}

int		count_arg(char **kratos, t_defined *lst)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (kratos[i])
	{
		if (!is_one_of_them(kratos[i], lst))
			count++;
		i++;
	}
	return (count + 1);
}
