/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:55:56 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/07 10:28:20 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(char *path, t_env **head_ref)
{
	char	buff[1024];
	char	*cwd;
	DIR		*dir;
	char	*tmp;

	ft_bzero(buff, 1024);
	cwd = getcwd(buff, sizeof(buff));
	tmp = (ft_strcmp(path, "-") == 0) ? \
	get_var("OLDPWD=", head_ref) : ft_strdup(path);
	if (access(tmp, F_OK) == 0)
	{
		if (access(tmp, X_OK) == 0)
		{
			chdir(tmp);
			swap(head_ref, cwd);
			return ;
		}
		(!(dir = opendir(tmp))) ? chdir_gerror(tmp, 0) : chdir_gerror(tmp, 1);
		(dir) ? closedir(dir) : 0;
		return ;
	}
	chdir_gerror(tmp, 2);
	ft_strdel(&tmp);
}

void	echo_cmd(char *arg, char *narg, int flag)
{
	if (arg == NULL)
		ft_putchar_fd('\n', 1);
	else if (ft_strcmp(arg, "-n") == 0)
		return ;
	else if (arg && !narg && flag)
		ft_putstr_fd(arg, 1);
	else if (arg && !narg && !flag)
		ft_putendl_fd(arg, 1);
	else if (arg && narg)
	{
		ft_putstr_fd(arg, 1);
		ft_putchar_fd(' ', 1);
	}
}
