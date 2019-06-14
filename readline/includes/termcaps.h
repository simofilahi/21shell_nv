/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:19:22 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 18:19:29 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# define CM_POS tgetstr("cm", NULL)
# define CL_SCREEN tgetstr("cd", NULL)
# define SC tgetstr("sc", NULL)
# define RC tgetstr("rc", NULL)
# define MCUOL tgetstr("up", NULL)
# define MCDOL tgetstr("do", NULL)
# define SVC tgetstr("vi", NULL)
# define EVC tgetstr("ve", NULL)

#endif
