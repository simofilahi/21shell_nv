/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 19:42:28 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/20 19:14:41 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_nbr(int n)
{
	int	len;

	len = (n > 0) ? 0 : 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*s;
	int		sign;
	int		len;

	sign = 0;
	len = ft_count_nbr(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (!(s = ft_strnew(len)))
		return (NULL);
	s[len] = '\0';
	while (len--)
	{
		s[len] = (n % 10) + 48;
		n /= 10;
	}
	if (sign)
		s[0] = '-';
	return (s);
}
