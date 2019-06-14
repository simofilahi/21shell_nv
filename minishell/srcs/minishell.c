/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:53:19 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:22:40 by mfilahi          ###   ########.fr       */
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

void	_minishell(char **command, t_env **head_ref)
{
	int		j;
	int		i;

	j = 0;
	if (command[j] == NULL)
		minishell(head_ref);
	if ((j = own_commands(command[0])))
	{
		(j == 3) ? setenv_cmd(command, head_ref) : 0;
	//	(j == 4) ? del_node(head_ref, argc) : 0;
		if (j == 3 || j == 4)
			return ;
		else if (command[1])
		{
			i = 0;
			while (command[++i])
				builtin_cmds(command[i], &j, head_ref);
		}
		else
			builtin_cmds(command[0], &j, head_ref);
	}
	else
		child_pid(command, head_ref);
	ft_free2d(command);
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
	write(fd, "\n", 1);
}

int 	metacharacters(char ch)
{
	if (ch == SQUOTE ||\
		ch == DQUOTE ||\
		ch == BACKSLACH ||\
		ch == PIPE)
		return (1);
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
				if (!ft_isspace(line[j++]) && !metacharacters(line[j++]))
					return (1);
		}
		return (0);
}

int		recall_readline(char *line, int *flag)
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
		if (metacharacters(line[index]) && (!a && !b))
		{
			if (line[index] == SQUOTE)
				a = 1;
			else if (line[index] == DQUOTE)
				b = 1;
			if (line[index] == BACKSLACH)
				c = 1;
			else if (line[index] == PIPE && beforepipe(line, index))
				d = 1;
			if (a || b || c || d)
				*flag = 1;
		}
		else if (metacharacters(line[index]) && (a || b))
		{
			if ((line[index] == SQUOTE && a) ||\
				 (line[index] == DQUOTE && line[index - 1] != BACKSLACH && b))
				*flag = 0;
		}
		else if (metacharacters(line[index]) && (c || d))
		{
			if ((c && line[index - 1] == BACKSLACH && line[index] == PIPE) ||\
				 (d && line[index - 1] == PIPE && line[index] == BACKSLACH))
				*flag = 0;
		}
		else if (!metacharacters(line[index]) && ft_isprint(line[index]))
		{
			if (c || d)
			 	*flag = 0;		 
		}
		index++;
	}
	return (1);
}

char **ft_parsing(char *path, int fd ,int index)
{
	char	*line;
	char	**tab;
	int 	flag;
	char	*tmp;
	char	*s;

	flag = 0;
	line = ft_readline(path, index - 1);
	while (recall_readline(line, &flag))
	{
		if (flag)
		{
			ft_putstr_fd("\033[1;34m...\033[0m", 1);
			tmp = ft_strdup(line);
			ft_strdel(&line);
			s = ft_readline(path, 0);
			line = ft_strjoin(tmp, s);
			ft_strdel(&tmp);
			ft_strdel(&s);
		}
		else
			break;
	}
	keephistory(line, fd, index);
	tab = ft_strsplit(line, ';');
	free(line);
	return (tab);
}


void	minishell(t_env **head_ref)
{
	char		**tab;
	char		**command;
	int			i;
	int 		fd;
	int			index;
	char		*homepath;
	char		*tmp;


	homepath = get_var("HOME=", head_ref);
	tmp = homepath;
	homepath = ft_strjoin(homepath, "/.21sh_history");
	ft_strdel(&tmp);
	fd = open(homepath, O_RDWR | O_TRUNC | O_CREAT | O_APPEND);
	index = 1;
	while ("21sh")
	{
		ft_putstr_fd("\033[1;34m$> \033[0m", 1);
		tab = ft_parsing(homepath, fd, index);
		i = 0;
		while (tab[i])
		{
			command = ft_strsplit(tab[i++], ' ');
			_minishell(command, head_ref);
		}
		ft_free2d(tab);
		index++;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*head_ref;

	(void)argc;
	(void)argv;
	g_signal_num = 0;
	signal(SIGINT, signal_handler);
	head_ref = copy_of_env(envp);
	minishell(&head_ref);
	free_list(&head_ref);
	return (0);
}