/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:37:04 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/07 17:37:06 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void	child_pid(char **command, t_cmd *lst, t_env **head_ref, pid_t *get)
{
	pid_t		child_pid;
	char		*path_found;

	(void)lst;
	child_pid = fork();
	*get = child_pid;
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
}

void	keephistorylst(t_his **his_tail, char *hline)
{
	t_his		*newnode;

	if (!(newnode = (t_his *)malloc(sizeof(t_his))))
		return ;
	newnode->hline = ft_strdup(hline);
	newnode->next = NULL;
	if (!(*his_tail))
	{
		(*his_tail) = newnode;
		(*his_tail)->prev = NULL;
	}
	else
	{
		newnode->prev = (*his_tail);
		(*his_tail)->next = newnode;
		(*his_tail) = newnode;
	}
}

int		just_spaces(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
			return (0);
	}
	return (1);
}
