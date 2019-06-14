/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:14:25 by aariss            #+#    #+#             */
/*   Updated: 2019/06/14 16:02:52 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

int		count_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_isquote(int c)
{
		if (c == 39 || c == '"')
			return (1);
		return (0);
}

int		ft_istoken(int c)
{
	if (c == '|' || c == '>' || c == '<'
			|| c == '&' || c == '1' || c == '2')
		return (1);
	return (0);
}

char	*ft_joinchar(char *s, char c)
{
	char	*str;
	int		s_size;
	int		i;

	s_size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_size + 2))))
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
