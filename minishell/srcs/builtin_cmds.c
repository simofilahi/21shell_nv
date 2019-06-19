/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:50:38 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:30:26 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** search through PATH values for binary if exist or not;
*/

char	*binary_path(char **tab, char *arg)
{
	int		i;
	char	*tmp;
	char	*s;

	i = 0;
	tmp = ft_strjoin("/", arg);
	while (tab[i])
	{
		s = ft_strjoin(tab[i], tmp);
		if (access(s, F_OK) == 0)
		{
			ft_strdel(&tmp);
			return (s);
		}
		ft_strdel(&s);
		i++;
	}
	ft_strdel(&tmp);
	return (NULL);
}

/*
** search for binary path;
*/

void	which_cmd(char *arg, t_env **head_ref)
{
	char	**tab;
	char	*ret;

	tab = get_path(head_ref);
	if ((ret = binary_path(tab, arg)))
		ft_putendl_fd(ret, 1);
	else
	{
		ret = ft_strjoin(arg, " not found");
		ft_putendl_fd(ret, 2);
	}
	ft_strdel(&ret);
	ft_free2d(tab);
}


int specialchar(char *s)
{
	while (*s)
		if (!ft_isalpha(*s++))
			return (1);
	return (0);
}

/*
** set new variables to environment;
*/

int  setenv_cmd(char *arg, char *sarg, t_env **head_ref, int flag)
{
	char *tmp;
	char *s;

	tmp = NULL;
	if (specialchar(arg))
	{
		ft_putendl_fd("setenv: Variable name must contain alphanumeric characters.", 2);
		return (0);
	}
	else
	{
		s = ft_strjoin(arg, "=");
		del_node(s, head_ref);
		tmp = s;
	}
	if (flag)
	{
		s = ft_strjoin(tmp, sarg);
		add_node(head_ref, s, flag);
	}
	else
		add_node(head_ref, s, flag);
	if (tmp != NULL)
		ft_strdel(&tmp);
	return (1);
}

void builtin_cmds(char **arg, t_env **head_ref, char *homepath, int j)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (j == 5)
		print_env(head_ref);
	else if (j == 7)
	{
		ft_strdel(&homepath);
		free_list(head_ref);
		ft_putendl_fd("\033[01;33mBye!\033[0m", 2);
		exit(0);
	}
	while (arg[i])
	{
		if ((j == 2 && i == 2) || (j == 3 && i == 3))
			return ;
		else if (j == 1)
		{
			if (ft_strcmp(arg[1], "-n") == 0 && i == 1)
				flag = 1;
			else
			echo_cmd(arg[i], arg[i + 1], flag);
		}
		else if (j == 2)
			ft_chdir(arg[i], head_ref);
		else if (j == 3)
		{
			if (arg[i + 1])
				flag = 1;
			else
				flag = 0;
			if (!setenv_cmd(arg[i], arg[i + 1], head_ref, flag) || flag)
				return ;
		}
		else if (j == 4)
			del_node(arg[i], head_ref);
		else if (j == 6)
			which_cmd(arg[i], head_ref);
		i++;
	}
}

int		own_commands(char *cmd)
{
	char	*command[9];
	int		i;

	command[1] = "echo";
	command[2] = "cd";
	command[3] = "setenv";
	command[4] = "unsetenv";
	command[5] = "env";
	command[6] = "which";
	command[7] = "exit";
	command[8] = NULL;
	i = 1;
	while (command[i])
	{
		if ((ft_strcmp(cmd, command[i]) == 0))
			return (i);
		i++;
	}
	return (0);
}
