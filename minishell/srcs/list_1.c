/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:31:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:10:21 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		len_of_list(t_env **head_ref)
{
	t_env	*current;
	int		counter;

	current = *head_ref;
	counter = 0;
	while (current)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}

void	print_env(t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
		if (current->var)
			ft_putstr_fd(current->var, 1);
		if (current->value)
			ft_putstr_fd(current->value, 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}

char	*get_var(char *deli, t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp(deli, current->var) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

void	swap(t_env **head_ref, char *path)
{
	t_env	*current;
	char	*pwdvar;

	if (!(get_var("OLDPWD=", head_ref)))
			return ;
	else if (!(pwdvar = get_var("PWD=", head_ref)))
			return ;
	current = *head_ref;
	while (current)
	{
		if (ft_strncmp("OLDPWD=", current->var, 7) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(pwdvar);
			ft_strdel(&pwdvar);
		}
		if (ft_strncmp("PWD=", current->var, 4) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(path);
		}
		current = current->next;
	}
}

t_env	*copy_of_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (env[++i])
		createlist(&head, &tail, env[i]);
	return (head);
}
