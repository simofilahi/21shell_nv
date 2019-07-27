/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:53:19 by mfilahi           #+#    #+#             */
/*   Updated: 2019/07/22 15:56:20 by mfilahi          ###   ########.fr       */
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

void	child_pid(char **command, t_god *lst, t_env **head_ref, int cast)
{
	pid_t	child_pid;
	char	*path_found;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (cast)
			if (!deathly_hallows(lst->demi_god))
				exit (0);
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
		if (lst->next == NULL)
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

void	keephistory(t_holder *h, int fd, int *index)
{
	char		*ret;
	char		*historyline;
	char		*tmp;
	static char *lline;

	if (*index == 1)
		lline = ft_strdup(h->line);
	else
	{
		if (ft_strcmp(h->line, lline) == 0)
		{
			(*index)--;
			return ;
		}
		free(lline);
		lline = ft_strdup(h->line);
	}
	h->ptr = lline;
	ret = ft_itoa(*index);
	tmp = ft_strjoin(ret, ":");
	historyline = ft_strjoin(tmp, h->line);
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
	if (g_signal_num == 3)
		g_signal_num = 1;
	else
	{
		h->line = ft_readline("$> ",h->homepath, index);
		ft_putchar_fd('\n', 1);
	}
	*flag = 0;
	if (!h->line)
	{
		*flag = 1;
		return (NULL);
	}
	else if (h->line[0] == '\n' || just_spaces(h->line))
		return (NULL);
	return (recall_readline(h, h->homepath));
}

void	minishell(t_holder *h, int fd, int index)
{
	int			flag;
	int			count;
	t__mc		*curr;
	t_god		*valhala;
	int			i;

	flag = 0;
	while ("21sh")
	{
		while (((!(call_readline(h, index, &flag)) && !flag)) || (g_signal_num == 3))
			;
		if (!flag)
		{
				if (h->line[0] == PIPE)
				{
					ft_putstr_fd("21sh: parse error near ", 2);
					ft_putchar_fd(h->line[0], 2);
					ft_putchar_fd('\n', 2);
				}
				else
				{
					keephistory(h, fd, &index);
					h->mclst = mc_maker(h->line, h->head_ref);
					ft_strdel(&h->line);
					h->line = ft_strnew(1);
					curr = h->mclst;
					count = count_mclst(curr);
					i = 0;
					while (i < count)
					{
						valhala = last_splice(&curr);
						h->lst = valhala;
					//	print_lstra(valhala);
						darlin_g(h);
					//		_minishell(valhala);
						i++;
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
   if (!h->homepath)
	{
		h->homepath = ft_strdup(".21sh_history");
		if ((fd = open(h->homepath, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777)) < 0)
			return (0);
		return (fd);
	}
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

	fd2 = open("/dev/ttys002", O_WRONLY);
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
