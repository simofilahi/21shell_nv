/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:53:19 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/03 14:33:54 by aariss           ###   ########.fr       */
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

char	*get_binary_path(char **cmd, t_env **head_ref)
{
	char 	**tab;
	char	*tmp;
	int		i;


	i = 0;
	tab = get_path(head_ref);
	tmp = ft_strjoin("/", *cmd);
	while (tab[i])
	{	
		*cmd = ft_strjoin(tab[i], tmp);
		if (access(*cmd, F_OK) == 0)
			break ;
		free(tab[i]);
		i++;
	}
	return (*cmd);
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

int		specialtoken(char **argv)
{
	t_defined *lst;
	int			 i;
	int			counter;

	lst = init_cases();
	i = 0;
	counter = 0;
	while (argv[i])
	{
		if (is_one_of_them(argv[i], lst))
			counter++;
		i++;
	}
	if (counter)
		return (counter);
	return (0);
}

int		count_words(char **args, int index)
{
	t_defined *lst;
	int		   counter;
	int		   i;
	int		   j;

	lst = init_cases();
	counter = 0;
	i = 0;
	j= 0;
	while (args[i])
	{
		if (!is_one_of_them(args[i], lst))
			counter++;
		else 
		{
			if (index == j)
				return (counter);
			counter = 0;
			j++;
		}
		i++;
	}
	return (counter);
}

char	**get_arg(char **argv, int index, char **which_token)
{
	int	 len;
	int  i;
	int  j;
	int  f;
	t_defined *lst;
	char **arg;

	len = count_words(argv, index);
	lst = init_cases();
	if (!(arg = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	f = 0;
	while (argv[i])
	{
		if (!is_one_of_them(argv[i], lst))
		{	
			if (index == f)
			{
				arg[j] = ft_strdup(argv[i]);
				j++;
			}
		}
		else 
		{
			*which_token = ft_strdup(argv[i]);
			if (index == f)
			{
				arg[len + 1] = NULL;
				return (arg);
			}
			f++;
		}
		i++;
	}
	arg[j] = NULL;
	return (arg);
}

void	_minishell(t_holder *h)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	if ((count = specialtoken(h->lst->cmd)))
		voidy(h->lst->cmd);
	else
	{
		if ((j = own_commands(h->lst->cmd[0])))
			builtin_cmds(h, j);
		else
			child_pid(h->lst->cmd, &h->head_ref);
	}
	ft_free2d(h->lst->cmd);
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

void	_qoutes_handler(t_var *v, char *line, int *flag)
{
	if (_metacharacters(line[v->index], 1) && (v->a || v->b))
	{
		if ((line[v->index] == SQUOTE && v->a) ||\
				(line[v->index] == DQUOTE && line[v->index - 1] != BACKSLACH && v->b))
		{
			v->a = 0;
			v->b = 0;
			*flag = 0;
		}
	}
	else if (_metacharacters(line[v->index], 0) && (v->c || v->d))
	{
		if ((v->c && line[v->index - 1] == BACKSLACH && line[v->index] == PIPE) ||\
				(v->d && line[v->index - 1] == PIPE && line[v->index] == BACKSLACH))
			*flag = 0;
	}
	else if (!_metacharacters(line[v->index], 0) && ft_isprint(line[v->index]))
	{
		if ((v->c && (!v->a && !v->b)) || (v->d && (!v->a && !v->b)))
			*flag = 0;
	}
}

int		qoutes_handler(char *line, int *flag)
{
	t_var *v;

	v = ft_memalloc(sizeof(t_var));
	while (line[v->index])
	{
		if (_metacharacters(line[v->index], 1) && (!v->a && !v->b))
		{
			if (line[v->index] == SQUOTE && ((!_metacharacters(line[v->index - 1], 0)) || v->d))
				v->a = 1;
			else if (line[v->index] == DQUOTE && ((!_metacharacters(line[v->index - 1], 0)) || v->d))
				v->b = 1;
			if (v->a || v->b)
				*flag = 1;
		}
		else if (_metacharacters(line[v->index], 0) && (!v->c && !v->d) && (!v->a && !v->b))
		{
			if (line[v->index] == BACKSLACH && !_metacharacters(line[v->index + 1], 1))
				v->c = 1;
			else if (line[v->index] == PIPE && beforepipe(line, v->index))
				v->d = 1;
			if (v->c || v->d)
				*flag = 1;
		}
		else
			_qoutes_handler(v, line, flag);
		v->index++;
	}
	free(v);
	return (1);
}

char	*recall_readline(char *line, char *homepath)
{
	int 	flag;
	char	*tmp;
	char	*s;

	flag = 0;
	while (qoutes_handler(line, &flag))
	{
		if (flag)
		{
			tmp = ft_strdup(line);
			if (!(s = ft_readline("...", homepath, -2)))
			{
				ft_putchar_fd('\n', 1);
				return (line);
			}
			ft_strdel(&line);
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

char	*call_readline(t_holder *h, int index, int *flag)
{
	char		*line;

	line = ft_readline("$> ",h->homepath, index);
	ft_putchar_fd('\n', 1);
	*flag = 0;
	if (!line)
	{
		*flag = 1;
		return (NULL);
	}
	else if (line[0] == '\n')
		return (NULL);
	return (recall_readline(line, h->homepath));
}

void	minishell(t_holder *h, int fd, int index)
{
	char		*line;
	int			flag;

	flag = 0;
	while ("21sh")
	{
		while (!(line = call_readline(h, index - 1, &flag)) && !flag)
			;
		if (!flag)
		{
			keephistory(line, fd, index);
			h->lst = mc_maker(line, h->head_ref);
			ft_strdel(&line);
			while (h->lst)
			{
				_minishell(h);
				h->lst = h->lst->next;
			}
		}
		else
			break ;
		index++;
	}
}

int		create_hfile(t_holder *h)
{
	char	*tmp;
	int		fd;

	h->homepath = get_var("HOME=", &h->head_ref);
	tmp = h->homepath;
	h->homepath = ft_strjoin(h->homepath, "/.21sh_history");
	ft_strdel(&tmp);
	if ((fd = open(h->homepath, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777)) < 0)
		return (0);
	return (fd);
}

int		main(int ac, char **av, char **envp)
{
	t_holder *h;
	int		fd;

	(void)ac;
	(void)av;
	h = ft_memalloc(sizeof(t_holder));
	g_signal_num = 0;
	signal(SIGINT, signal_handler);
	h->head_ref = copy_of_env(envp);
	if (!(fd = create_hfile(h)))
	{
		ft_putendl_fd("Failed To Create History File \n", 2);
		return (0);
	}
	minishell(h, fd, 1);
	ft_strdel(&h->homepath);
	free_list(&h->head_ref);
	//free_list2(h->lst);
	free(h);
	ft_putendl_fd("\033[01;33mBye!\033[0m", 2);
	return (0);
}
