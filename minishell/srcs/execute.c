/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:56:52 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:23:12 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **command, char *path_found, t_env **head_ref)
{
	char	*msgerror;
	char	**env;

	env = get_env(head_ref);
	if (execve(command[0], command, env) == -1)
	{
		if (access(command[0], F_OK) == -1)
		{
			msgerror = ft_strjoin("command not found: ", path_found);
			ft_putendl_fd(msgerror, 2);
		}
		if (access(command[0], F_OK) == 0 && access(command[0], X_OK) != 0)
		{
			msgerror = ft_strjoin("permission denied: ", path_found);
			ft_putendl_fd(msgerror, 2);
		}
		free(msgerror);
	}
	ft_free2d(env);
}


char	**get_path(t_env **head_ref)
{
	t_env	*current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp(current->var, "PATH=") == 0)
			break ;
		current = current->next;
	}
	return (ft_strsplit(current->value, ':'));
}

void	signal_handler(int sign)
{
	ft_putchar('\n');
	if (sign == SIGINT && g_signal_num > 0)
	{
		ft_putstr_fd("\033[1;34m$> \033[0m", 1);
		g_signal_num = 2;
	}
}