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

int		cmd_is_found(char **tab, char **ptrcmd, char *temp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		(*ptrcmd) = ft_strdup(temp);
		tmp = (*ptrcmd);
		(*ptrcmd) = ft_strjoin(tab[i], (*ptrcmd));
		free(tmp);
		if (access((*ptrcmd), F_OK) == 0)
		{
			free((*ptrcmd));
			return (1);
		}
		free((*ptrcmd));
		i++;
	}
	return (0);
}

void	which_cmd(char **command, t_env **head_ref)
{
	char	*temp;
	char	*cmd;
	char	**tab;
	char		*ptr;
	int		j;

	tab = get_path(head_ref);
	j = 1;
	while (command[j])
	{
		cmd = ft_strdup(command[j]);
		ptr = cmd;
		cmd = ft_strjoin(cmd, " not found");
		free(ptr);
		temp = ft_strjoin("/", command[j]);
		if (cmd_is_found(tab, &command[j], temp))
		{
			free(cmd);
			free(temp);
			ft_putendl_fd(command[j], 1);
		}
		else
		{
			free(temp);
			ft_putendl_fd(cmd, 2);
			free(cmd);
		}
		free(temp);
		free(cmd);
		j++;
	}
	j = -1;
	while (tab[++j])
		free(tab[j]);
	free(tab);
}

int specialchar(char *s)
{
	while (*s)
		if (!ft_isalpha(*s++))
			return (1);
	return (0);
}

int  setenv_cmd(char *arg, char *sarg, t_env **head_ref, int flag)
{
	char *tmp;
	char *s;

	/*if (ptrcmd[1] == NULL)
		print_env(head_ref);
	else if (ptrcmd[1][0] == '=')
	{
		tmp = ft_strjoin(ptrcmd[1], " not found");
		ft_putendl_fd(tmp, 2);
		free(tmp);
	}
	else if (ptrcmd[2] == NULL)
	{
		tmp = ft_trim(ptrcmd[1], '=');
		if (ptrcmd[1][(ft_strlen(ptrcmd[1]) - 1)] != '=')
			add_node(head_ref, ptrcmd[1], tmp, 1);
		if (tmp)
			free(tmp);
		return ;
	}
	else if (ptrcmd[3] == NULL && \
			ptrcmd[2][(ft_strlen(ptrcmd[2]) - 1)] != '=')
			add_node(head_ref, ptrcmd[1] ,ptrcmd[2], 0);
	else
		_env_gerror();*/
	tmp = NULL;
	if (specialchar(arg))
	{
		ft_putendl_fd("setenv: Variable name must contain alphanumeric characters.", 2);
		return (0);
	}
	else
	{
		s = ft_strjoin(arg, "=");
		del_node(head_ref, s);
		tmp = s;
	}
	if (flag)
	{
		s = ft_strjoin(tmp, sarg);
		add_node(head_ref, s, flag);
	}
	else
		add_node(head_ref, s, flag);
	if (tmp)
		ft_strdel(&tmp);
	return (1);
}

/*void	builtin_cmds(char *argc, int *j,t_env **head_ref)
{
	int i;

	i = 0;
	if (*j == 1)
		echo_cmd(argc, 0);
	else if (*j == 2)
		ft_chdir(argc, head_ref);
	else if(*j == 4)
		del_node(head_ref, argc);
	else if(*j == 5)
		print_env(head_ref);
	else if(*j == 6) 
		which_cmd(argc, head_ref);
	else if (*j == 7)
	{
		free_list(head_ref);
		exit(0);
	}
}*/

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
