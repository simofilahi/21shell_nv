/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:59:55 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/07 10:19:44 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		len_of_var(char *s)
{
	int	index;

	index = 1;
	while (*s && *s++ != '=')
		index++;
	return (index);
}

/*
** Create linked list to store environment;
*/

void	createlist(t_env **head, t_env **tail, char *s)
{
	t_env	*new_node;
	int		index;

	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	index = len_of_var(s);
	new_node->var = ft_strsub(s, 0, index);
	new_node->value = ft_strdup(s + index);
	new_node->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = new_node;
		(*tail) = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		(*tail) = (*tail)->next;
	}
}

/*
** - get path values from environment;
** - split and store each path in case into tab;
*/

char	**get_env(t_env **head_ref)
{
	t_env	*current;
	char	**tab;
	int		i;

	current = *head_ref;
	if (!(tab = (char **)malloc(sizeof(char *) * (len_of_list(head_ref) + 1))))
		return (NULL);
	i = 0;
	while (current)
	{
		tab[i] = ft_strjoin(current->var, current->value);
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

/*
** del variable from environment;
*/

void	del_node(char *s, t_env **head_ref)
{
	t_env	*current;
	t_env	*prev;
	char	*str;

	current = *head_ref;
	prev = current;
	str = (s[ft_strlen(s) - 1] != '=') ? \
		ft_strjoin(s, "=") : ft_strdup(s);
	while (current &&
			(ft_strcmp(str, current->var) != 0))
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	if (current == *head_ref)
		*head_ref = (*head_ref)->next;
	ft_strdel(&current->var);
	if (current->value)
		ft_strdel(&current->value);
	free(current);
	ft_strdel(&str);
}

/*
** add variable into environment;
*/

void	add_node(t_env **head_ref, char *s, int flag)
{
	t_env	*new_node;
	t_env	*current;
	int		len;

	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	if (!flag)
	{
		new_node->var = ft_strdup(s);
		new_node->value = NULL;
	}
	else
	{
		len = len_of_var(s);
		new_node->var = ft_strsub(s, 0, len);
		new_node->value = ft_strdup(s + len);
	}
	new_node->next = NULL;
	current = *head_ref;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
