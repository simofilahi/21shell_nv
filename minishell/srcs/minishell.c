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
//


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
		g_signal_num = 0;
		wait(NULL);
	}
	g_signal_num = 1;
}

int		specialtoken(char **argv)
{
	t_defined	 *lst;
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

void	_minishell(t_holder *h)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	if (!(count = specialtoken(h->lst->cmd)) &&\
		 (j = own_commands(h->lst->cmd[0])))
		builtin_cmds(h, j);
	else
	{
		//if (count)
		//	_child_pid(h, count);
		//else
			child_pid(h->lst->cmd, &h->head_ref);
	}
}

void	keephistory(t_holder *h, char *line, int fd, int *index)
{
	char		*ret;
	char		*historyline;
	char		*tmp;
	static char *lline;

	if (*index == 1)
		lline = ft_strdup(line);
	else
	{
		if (ft_strcmp(line, lline) == 0)
		{
			(*index)--;
			return ;
		}
		free(lline);
		lline = ft_strdup(line);
	}
	h->ptr = lline;
	ret = ft_itoa(*index);
	tmp = ft_strjoin(ret, ":");
	historyline = ft_strjoin(tmp, line);
	write(fd, historyline, ft_strlen(historyline));
	ft_strdel(&ret);
	ft_strdel(&tmp);
}


int just_spaces(char *line)
{
	while(*line)
	{
		if (ft_isspace(*line))
			line++;
		else
			return (0);
	}
	return (1);
}

/*
** - get line from readline func;
*/

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
		else if (line[0] == '\n' || just_spaces(line))
		{
			  ft_strdel(&line);
			  return (NULL);
		}
		return (recall_readline(h, line, h->homepath));
}

void	minishell(t_holder *h, int fd, int index)
{
	char		*line;
	int			flag;
	t__mc		*curr;

	flag = 0;
	while ("21sh")
	{
		while (!(line = call_readline(h, index - 1, &flag)) && !flag)
				;
		if (!flag)
		{
			if (line[0] == PIPE)
			{
				ft_putstr_fd("21sh: parse error near ", 2);
				ft_putchar_fd(line[0], 2);
				ft_putchar_fd('\n', 2);
			}
			else
			{
				keephistory(h, line, fd, &index);
				h->lst = mc_maker(line, h->head_ref);
				ft_strdel(&line);
				curr = h->lst;
				while (h->lst)
				{
					_minishell(h);
					h->lst = h->lst->next;
				}
				_free_list(curr);
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
		

//	fd2 = fopen("/dev/ttys001", "a+");
	g_signal_num = 1;
	signal(SIGINT, signal_handler);
	h = ft_memalloc(sizeof(t_holder));
	h->head_ref = copy_of_env(envp);
	if (!(fd = create_hfile(h)))
	{
		ft_putendl_fd("Failed To Create History File \n", 2);
		return (0);
	}
	minishell(h, fd, 1);
	free_structure(h);
	return (0);
}