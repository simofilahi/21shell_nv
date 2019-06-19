/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:07:07 by aariss            #+#    #+#             */
/*   Updated: 2019/06/19 08:49:01 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSIN_H
# define PARSIN_H
# define B_S 1

# include "libft.h"
# include "minishell.h"

/*
 ******** Data Structures ********
 */


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
int     ft_count_till(char *s, int c);

/*
 ******** Others ********
 */
char	*ft_joinchar(char *s, char c);
char	*skip_quote(char *line);
char	*get_my_line(int fd);
char    *ft_strfchr(char *s, int c);
char    *ft_strfchr_alpha(char *s);

#endif
