/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:27:06 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/10 14:29:31 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env **head_ref)
{
	t_env	*current;

	current = *head_ref;
	while ((*head_ref)->next)
	{
		current = *head_ref;
		*head_ref = (*head_ref)->next;
		free(current->var);
		free(current);
	}
	free((*head_ref)->var);
	free((*head_ref));
}

void	_env_gerror()
{
	ft_putstr_fd("setenv: ", 2);
	ft_putendl_fd("\033[0;31mToo many arguments.\033[0m", 2);
}

void	_chdir_gerror(char *path, int flag)
{
	if (path == NULL)
		return;
	if (flag == 0)
		ft_putstr_fd ("cd: \033[0;31mnot a directory: \033[0m", 2);
	else if (flag == 1)
		ft_putstr_fd("cd: \033[0;31mpermission denied: \033[0m", 2);
	else if (flag == 2)
		ft_putstr_fd("cd: \033[0;31mno such file or directory: \033[0m", 2);
	ft_putstr_fd("\033[0;31m",2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putchar_fd('\n', 2);
}
