/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:53:19 by mfilahi           #+#    #+#             */
/*   Updated: 2019/06/19 09:37:18 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sys_cmd(char **command, char *path_found, t_env **head_ref)
{
	int		i;
	char	*temp;
	char	**tab;
	char	*tmp;

	if (ft_strncmp(command[0], "./", 2) != 0)
	{
		temp = ft_strjoin("/", command[0]);
		tab = get_path(head_ref);
		i = 0;
		while (tab[i])
		{
			tmp = ft_strdup(temp);
			command[0] = ft_strjoin(tab[i], tmp);
			free(tmp);
			if (access(command[0], F_OK) == 0)
				break ;
			free(command[0]);
			free(tab[i]);
			i++;
		}
		free(temp);
	}
	execute(command, path_found, head_ref);
}

void	child_pid(char **command, t_env **head_ref)
{
	pid_t	child_pid;
	char	*path_found;

	child_pid = fork();
	if (child_pid == 0)
	{
		path_found = ft_strdup(command[0]);
		if (command[0][0] == '/')
			execute(command, path_found, head_ref);
		else
			sys_cmd(command, path_found, head_ref);
		free(path_found);
		exit(0);
	}
	else
	{
		g_signal_num = 1;
		wait(NULL);
	}
	g_signal_num = 0;
}

void	_minishell(char **arg, char *homepath, t_env **head_ref)
{
	int		j;

	j = 0;
	if ((j = own_commands(arg[0])))
		builtin_cmds(arg, head_ref, homepath, j);
	else
		child_pid(arg, head_ref);
	ft_free2d(arg);
}

void	keephistory(char *line, int fd, int index)
{
	char	*ret;
	char	*historyline;
	char	*tmp;

	ret = ft_itoa(index);
	tmp = ft_strjoin(ret, ":");
	historyline = ft_strjoin(tmp, line);
	write(fd, historyline, ft_strlen(historyline));
}

int 	_metacharacters(char ch, int flag)
{
	if (flag)
	{
		if (ch == SQUOTE ||\
			ch == DQUOTE)
			return (1);
	}
	else
	{
		if (ch == BACKSLACH ||\
			ch == PIPE)
			return (1);
	}
	return (0);
}

int		beforepipe(char *line, int index)
{
		int j;

		if (index == 0)
			return (0);
		else
		{
			j = 0;
			while (j < index)
				if (!ft_isspace(line[j++]))
					return (1);
		}
		return (0);
}

/*
** recall readline in cases where qoutes or backslach or pipe found;
*/

int		qoutes_handler(char *line, int *flag)
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		index;

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	index = 0;
	while (line[index])
	{
		if (_metacharacters(line[index], 1) && (!a && !b))
		{
			if (line[index] == SQUOTE && ((!_metacharacters(line[index - 1], 0)) || d))
				a = 1;
			else if (line[index] == DQUOTE && ((!_metacharacters(line[index - 1], 0)) || d))
				b = 1;
			if (a || b)
				*flag = 1;
		}
		else if (_metacharacters(line[index], 0) && (!c && !d) && (!a && !b))
		{
			if (line[index] == BACKSLACH && !_metacharacters(line[index + 1], 1))
				c = 1;
			else if (line[index] == PIPE && beforepipe(line, index))
				d = 1;
			if (c || d)
				*flag = 1;
		}
		else if (_metacharacters(line[index], 1) && (a || b))
		{
			if ((line[index] == SQUOTE && a) ||\
				 (line[index] == DQUOTE && line[index - 1] != BACKSLACH && b))
			{
				a = 0;
				b = 0;
				*flag = 0;
			}
		}
		else if (_metacharacters(line[index], 0) && (c || d))
		{
			if ((c && line[index - 1] == BACKSLACH && line[index] == PIPE) ||\
				 (d && line[index - 1] == PIPE && line[index] == BACKSLACH))
				*flag = 0;
		}
		else if (!_metacharacters(line[index], 0) && ft_isprint(line[index]))
		{
			if ((c && (!a && !b)) || (d && (!a && !b)))
			 	*flag = 0;
		}
		index++;
	}
	return (1);
}

char	*recall_readline(char *line, char *homepath)
{
	int 	flag;
	char	*tmp;
	char	*s;
	int 	ctrl_d;

	flag = 0;
	while (qoutes_handler(line, &flag))
	{
		if (flag)
		{
			ft_putstr_fd("\033[1;32m...\033[0m", 1);
			tmp = ft_strdup(line);
			ft_strdel(&line);
			if (!(s = ft_readline(homepath, 0, &ctrl_d)))
			{
				ft_putchar_fd('\n', 1);
				return (NULL);
			}
			ft_putchar_fd('\n', 1);
			line = ft_strjoin(tmp, s);
			ft_strdel(&tmp);
			ft_strdel(&s);
		}
		else
			break;
	}
	return (line);
}

char	*call_readline(t_env **head_ref, char *homepath, int fd, int index)
{
		int			ctrl_d;
		char		*line;

		line = ft_readline(homepath, index, &ctrl_d);
		ft_putchar_fd('\n', 1);
		if (!line)
			return (NULL);
		else if (line[0] == '\n')
			minishell(head_ref, homepath, fd, index);
		else if (!(line = recall_readline(line, homepath)))
			minishell(head_ref, homepath, fd, index);
		return (line);
}

void	minishell(t_env **head_ref, char *homepath, int fd, int index)
{
	t__mc		*lst;
	char		*line;

	while ("21sh")
	{
		ft_putstr_fd("\033[1;34m$> \033[0m", 1);
		if (!(line = call_readline(head_ref, homepath, fd, index - 1)))
				break;
		keephistory(line, fd, index);
		lst = mc_maker(line, *head_ref);
		while (lst)
		{
			_minishell(lst->cmd, homepath, head_ref);
			lst = lst->next;
		}
		index++;
	}
}

int		create_hfile(t_env **head_ref, char **homepath)
{
	int			fd;
	char		*tmp;

	*homepath = get_var("HOME=", head_ref);
	tmp = *homepath;
	*homepath = ft_strjoin(*(homepath), "/.21sh_history");
	ft_strdel(&tmp);
	if ((fd = open(*homepath, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777)) < 0)
		return (0);
	return (fd);
}

int		main(int ac, char **av, char **envp)
{
	t_env	*head_ref;
	int		fd;
	char	*homepath;

	(void)ac;
	(void)av;
	homepath = NULL;
	g_signal_num = 0;
	signal(SIGINT, signal_handler);
	head_ref = copy_of_env(envp);
	fd = create_hfile(&head_ref, &homepath);
	minishell(&head_ref, homepath, fd, 1);
	ft_strdel(&homepath);
	free_list(&head_ref);
	ft_putendl_fd("\033[01;33mBye!\033[0m", 2);
	return (0);
}
