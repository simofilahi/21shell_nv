/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_capios_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:32:12 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/17 16:39:43 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

/*
** - store static structure;
*/

t_package		*cloud(t_package *p)
{
	static t_package	*tmp;

	if (p == NULL)
		return (tmp);
	else
		tmp = p;
	return (tmp);
}

/*
** - use in termcap;
*/

int				my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

/*
** - set old configuration termios;
*/

void			normal_mode(void)
{
	t_package	*p;

	p = cloud(NULL);
	tcsetattr(0, TCSANOW, &p->oldconf);
}

/*
** - set new configuration termios by enbling non-canonical;
*/

struct termios	termios_config(void)
{
	struct termios	newconf;
	struct termios	oldconf;

	if (tcgetattr(0, &oldconf) < 0)
		ft_putendl_fd("error can't get the current configuration", \
				2);
	if (tcgetattr(0, &newconf) < 0)
		ft_putendl_fd("error can't get the current configuration", \
				2);
	newconf.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &newconf) < 0)
		ft_putendl_fd("error can't apply the configuration", 2);
	return (oldconf);
}

/*
** - store internally capabilities of termcap;
*/

int				termcap_config(void)
{
	char	*termtype;
	int		success;
	char	buf2[30];
	char	*ap;

	ap = buf2;
	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		ft_putstr_fd("variable TERM not found", 2);
		return (0);
	}
	success = tgetent(ap, termtype);
	if (success == -1 || success == 0)
	{
		ft_putstr_fd("set a valid TERM value", 2);
		return (0);
	}
	return (1);
}
