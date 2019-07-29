/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:56:32 by mfilahi           #+#    #+#             */
/*   Updated: 2018/10/21 12:28:51 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	int		j;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	while (s[len - 1] && ft_isspace(s[len - 1]))
		len--;
	if (!(str = ft_strnew(len - i)))
		return (NULL);
	j = 0;
	while (s[i] && i < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
