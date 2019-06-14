/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:53:56 by aariss            #+#    #+#             */
/*   Updated: 2019/06/14 15:40:29 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*get_my_line(int fd)
{
	char	buffer[B_S + 1];
	char	*ptr;
	int		ret;
	char	*tmp;

	ptr = ft_strdup("");
	while ((ret = read(fd, buffer, B_S)))
	{
		buffer[ret] = '\0';
		if (ft_strchr(buffer, '\n'))
			break ;
		tmp = ptr;
		ptr = ft_strjoin(ptr, buffer);
		ft_strdel(&tmp);
	}
	return (ptr);
}
