/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:07:07 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 16:42:33 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSIN_H
# define PARSIN_H
# define B_S 1

# include "libft.h"
# include "shell.h"

int		ft_istoken(int c);
int		ft_isquote(int c);
int		got_token_after_digit(char *line);
int		alright_token(char *name);
int		count_tab(char **tab);
int		ft_count_till(char *s, int c);
int		ft_count_falpha(char *s);
char	*ft_joinchar(char *s, char c);
char	*skip_quote(char *line);
char	*get_my_line(int fd);
char	*ft_strfchr(char *s, int c);
char	*ft_strfchr_alpha(char *s);

#endif
