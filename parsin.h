/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:07:07 by aariss            #+#    #+#             */
/*   Updated: 2019/06/14 15:55:21 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSIN_H
# define PARSIN_H
# define B_S 1

#include "libft.h"

/*
 ******** Data Structures ********
 */

typedef struct	s__mc t__mc;

struct	s__mc
{
	char			**cmd;
	struct s__mc	*next;
};

/*
 ******** Check Functions ********
 */

int		ft_istoken(int c);
int		ft_isquote(int c);
int		ft_ischarspecial(int c);

/*
 ******** Count Functions ********
 */
int		count_tab(char **tab);

/*
 ******** Others ********
 */
char	*ft_joinchar(char *s, char c);
char	*parsin(char *line);
char	*skip_quote(char *line);
char	*get_my_line(int fd);
t__mc	*mc_maker(char *line);

#endif
