/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:51:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/18 21:15:38 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "line_edition.h"
# include "parsin.h"
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

/*
 **********	DATA STRUCTURES ********
 */
int				g_signal_num;

typedef struct	s_env t_env;
struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
};

typedef struct	s__mc t__mc;

struct		s__mc
{
	char			**cmd;
	struct s__mc	*next;
};

typedef	struct	s_defined t_defined;

struct		s_defined
{
	char				*data;
	struct s_defined	*next;
};


typedef	struct	s_var t_var;

struct		s_var
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		index;
};

typedef	struct	s_info t_info;

struct		s_info
{
	char			*file;
	int				sfd;
	int				dfd;
	int				read_meth;
	struct s_info	*next;
};

typedef	struct	s_god t_god;

struct		s_god
{
	char			**cmd;
	struct s_info	*demi_god;
	struct s_god	*next;
};

typedef	struct	s_holder t_holder;

struct		s_holder
{
	t_env	*head_ref;
	t__mc	*mclst;
	t_god	*lst;
	char	*line;
	char	*homepath;
	char	*heredoc;
	char	*ptr;
};

typedef	struct	s_childs t_childs;

struct		s_childs
{
	pid_t child;
	int	  index;
	struct	s_childs *next;
};

/*
 **********	BUILDING Functions ********
 */

char	**get_piped(char **argv, int index);
int		pipecount(char **argv, int delim);
void	voidy(char **cmd);
int		retrieve_the_digit(char *name, int	delimiter);
int		count_arg(char **cmd);
int		count_mclst(t__mc *lst);
t_god	*last_splice(t__mc **old_lst);
void	print_lstra(t_god *lst);
int		count_lstgod(t_god *lst);
void	darlin_g(t_holder *h);
int		ultimate_check(char *kratos);
int		deathly_hallows(t_info *lst);

/*
 **********	$ Functions ********
 */
char    *dollar_get_simple(char *name, t_env *env, char **ptr);
char    *dollar_get_quoted(char *name, t_env *env, char **ptr);
char	*dollar_handle_simple(char *toto, char *line, int *i, t_env *env);
char	*dollar_handle_quoted(char *toto, char *line, int *i, int quote, t_env *env);
void	_free_list(t__mc	*lst);
/*
 **********	Others ********
 */
int			count_words(char **args, int index);
char		**get_arg(char **argv, int index, char **which_token);
int			specialtoken(char **argv);
void		khilo(t_god *lst, t_env *env);
t_god		*god_like(char **cmd);
void		minishell(t_holder *h, int fd, int index);
void		_child_pid(t_holder *h, int count);
t__mc		*mc_maker(char *line, t_env *env);
char		*parsin(char *line, t_env *env, t_defined *tokens);
t_defined	*init_cases(void);
int			is_one_of_them(char *name, t_defined *lst);
void		child_pid(char **command, t_god *lst, t_env **head_ref, int game_changer);
void		sys_cmd(char **command, char *path_found, t_env **head_ref);
void		execute(char **command, char *path_found, t_env **head_ref);
char		**get_env(t_env **head_ref);
int			len_of_list(t_env **head_ref);
void		builtin_cmds(t_holder *h, int j);
void		which_cmd(char *arg, t_env **head_ref);
int			cmd_is_found(char **tab, char **ptrcmd, char *temp);
void		_env_gerror(void);
int			own_commands(char *ptab);
void		del_node(char *s, t_env **head_ref);
void		add_node(t_env **head_ref, char *s1, int flag);
void		echo_cmd(char *arg, char *narg, int flag);
void		ft_chdir(char *path, t_env **head_ref);
void		_chdir_gerror(char *path, int flag);
void		swap(t_env **head_ref, char *path);
char		*get_var(char *deli, t_env **head_ref);
void		ft_handle(char *line);
void		print_env(t_env **head_ref);
t_env		*copy_of_env(char **tab);
void		createlist(t_env **head_ref, t_env **tail, char *var);
char		**get_path(t_env **head_ref);
int			find_path(char *penv);
void		signal_handler(int sign);
void		free_list(t_env **head_ref);
char		*ft_readline(char prompt[3], char *path, int ll_index);
int			setenv_cmd(char *arg, char *sarg, t_env **head_ref, int flag);
char		*recall_readline(t_holder *h, char *homepath);
void		free_structure(t_holder *h);

#endif
