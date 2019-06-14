/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:03:31 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/04 18:25:25 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H
# include "libft.h"
# include "termcaps.h"
# include "keys.h"
# include "get_next_line.h"
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define BUFF_SIZE 100
# define BUFFER_SIZE 100000

// 

typedef struct		s_hlst
{
	char			*line;
	struct s_hlst	*next;
	struct s_hlst	*prev;
}					t_hlst;

typedef struct		s_package
{
	char			*line;
	char			buffer[BUFFER_SIZE];
	char			*holdcopy;
	int				index;
	int				posx;
	int				posy;
	int				init_y;
	int				last_y;
	int				init_row;
	int				len;
	char			*path;
	int				ll_index;
	struct termios	oldconf;
	struct winsize	w;
}					t_package;

/*
** Get history line
*/
int					gline(const int fd, char **line_target, int delimiter);
/*
** Manipulation of line :
** 						- insertion & deletion
*/
char				*insert_element(char *string, char ch, int key, int *llen);
void				delete_element(char *string, int key);
char				*delrange_of_elem(char *string, int startindex, int endindex);
char				*addrange_of_elem(char *s1, char *s2, int key);
/*
** Keys
*/
void				home_key();
void				end_key(t_package *p);
void				left_key(t_package *p);
void				right_key(t_package *p);
void				backspace_key(t_package *p);
void				ft_alt_downkey(t_package *p);
void				backwardkey(t_package *p);
void				forwardkey(t_package *p);
void				ft_alt_upkey(t_package *p);
void				ft_history_downkey(t_package *p);
void				ft_history_upkey(t_package *p);
void				ctrl_d();
void				left_key_with_history(int tmp, int x, int y, t_package *p);
/*
** copy/cut/paste
*/
void				copy_line_key(char **buffer_ref, char *line);
void				copy_before_cursor_key(char **buffer_ref, char *line, \
					int index);
void				copy_after_cursor_key(char **buffer_ref, char *line, \
					int index);
void				cut_line_key(char **buffer_ref, char **line);
void				cut_before_cursor_key(char **buffer_ref, char **line, \
					int index);
void				cut_after_cursor_key(char **buffer_ref, char **line, \
					int index);
void				paste_key(t_package *p);
void				paste_of_mouse(t_package *p);
/*
** termios and termcap config
*/
void				normal_mode(void);
struct termios		termios_config(void);
void				termcap_config(void);
int					my_putchar(int c);
/*
** cursor actions
*/
void				change_cursor_pos(int *posx, int *posy, int w_col, \
					int is_true);
void				move_cursor(int ch);
void				clear_screen(void);
int					get_pos(int *y, int *x);
int					get_index(int randomindex, int tmpy, int tmpx);
int					increment_row_1(t_package *p);
int					increment_row(t_package *p, int flag);
/*
** print to stdout
*/
void				print_line(char *line, int index);
int					print(t_package*p, int index, int col);
void				print_readablechar();
/*
** read from stdin
*/
void				read_line();
char				*ft_readline(char *path, int ll_index);
/*
** others :
**			- initialization memeber of structure
**			- func cloud to store @ of structure
**			- count lines if newline is found
*/
void				init_structure_members(char *path, int ll_index);
t_package			*cloud(t_package *p);
int					get_n_line(int fd, char **line, int n);
int					new_line_is_found(char *line);
int					checking(char *line, int index, int key);
int					count_lines(char *line, int w_col);
#endif
