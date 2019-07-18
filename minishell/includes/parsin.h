/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:07:07 by aariss            #+#    #+#             */
/*   Updated: 2019/07/08 15:54:44 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSIN_H
# define PARSIN_H
# define B_S 1

# include "libft.h"
# include "minishell.h"

/*
 ******** Check Functions ********
 */

int		ft_istoken(int c);
int		ft_isquote(int c);
int		got_token_after_digit(char *line);
int		alright_token(char *name);

/*
 ******** Count Functions ********
 */
int		count_tab(char **tab);
int     ft_count_till(char *s, int c);
int		ft_count_falpha(char *s);

/*
 ******** Others ********
 */
char	*ft_joinchar(char *s, char c);
char	*skip_quote(char *line);
char	*get_my_line(int fd);
char    *ft_strfchr(char *s, int c);
char    *ft_strfchr_alpha(char *s);

#endif
