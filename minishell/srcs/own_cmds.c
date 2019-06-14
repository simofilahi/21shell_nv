/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:55:56 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:41:18 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_chdir(char *path, t_env **head_ref)
{
	char	buff[1024];
	char	*cwd;
	DIR		*dir;

	ft_bzero(buff, 1024);
	cwd =  getcwd(buff, sizeof(buff));
	if (access(path, F_OK) == 0)
	{
		(!(dir = (opendir(path)))) ? _chdir_gerror(path, 0) : closedir(dir);
		if (!dir)
			return ;
		if (access(path, X_OK) == 0)
		{
			chdir(path);
			swap(head_ref, cwd);
			return ;
		}
		_chdir_gerror(path, 1);
	}
	_chdir_gerror(path, 2);
}

void	echo_cmd(char *cmd, int flag)
{
	if (cmd == NULL)
		ft_putchar_fd('\n', 1);
	else if (cmd && flag)
		ft_putendl_fd(cmd, 1);
	else
		ft_putstr_fd(cmd, 1);
}
