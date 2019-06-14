/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 22:45:01 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/18 23:30:26 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int j;

	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[j])
	{
		i = 0;
		while (big[j + i] == little[i])
		{
			if (!little[i + 1])
				return ((char *)big + j);
			i++;
		}
		j++;
	}
	return (0);
}
