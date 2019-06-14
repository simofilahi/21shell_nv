/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:51:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:12:58 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "line_edition.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
//
# include <stdio.h>

/*
** metacharacters
*/
#define BACKSLACH '\\'
#define SQUOTE '\''
#define DQUOTE '"'
#define HASH '#'
#define PIPE '|'

int				g_signal_num;

typedef struct	s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;


void			minishell(t_env **head_ref);
void			child_pid(char **command, t_env **head_ref);
void			sys_cmd(char **command, char *path_found, t_env **head_ref);
void			execute(char **command, char *path_found, t_env **head_ref);
char			**get_env(t_env **head_ref);
int				len_of_list(t_env **head_ref);
void			builtin_cmds(char *ptrcmd, int *j, t_env **head_ref);
void			which_cmd(char **command, t_env **head_ref);
int				cmd_is_found(char **tab, char **ptrcmd, char *temp);
void			_env_gerror();
int				own_commands(char *ptab);
t_env			*del_node(t_env **head_ref, char *str);
void			add_node(t_env **head_ref, char *s1, char *s2, int flag);
void			echo_cmd(char *cmd, int flag);
void			ft_chdir(char *path, t_env **head_ref);
void			_chdir_gerror(char *path, int flag);
void			swap(t_env **head_ref, char *path);
char			*get_var(char *deli, t_env **head_ref);
void			ft_handle(char *line);
void			print_env(t_env **head_ref);
t_env			*copy_of_env(char **tab);
void			createlist(t_env **head_ref, t_env **tail, char *var);
char			**get_path(t_env **head_ref);
int				find_path(char *penv);
void			signal_handler(int sign);
void			free_list(t_env **head_ref);
char			*ft_readline(char *path, int ll_index);
void			setenv_cmd(char **ptrcmd, t_env **head_ref);

#endif
