/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:18:23 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 09:18:44 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*error_assembly(int fd)
{
	char	*itoa;
	char	*tmp;

	itoa = ft_itoa(fd);
	tmp = itoa;
	itoa = ft_strjoin("21sh: ", itoa);
	ft_strdel(&tmp);
	tmp = itoa;
	itoa = ft_strjoin(itoa, ": bad file descriptor");
	ft_strdel(&tmp);
	return (itoa);
}
