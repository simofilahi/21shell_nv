/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:59:55 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:30:10 by mfilahi          ###   ########.fr       */
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

t_env	*del_node(t_env **head_ref, char *str)
{
	t_env	*current;
	t_env	*prev;
	char	*s;

	current = *head_ref;
	prev = current;
	if (!str)
		return (NULL);
	s = (str[ft_strlen(str) - 1] != '=') ? \
		ft_strjoin(str, "=") : ft_strdup(str);
	while (current &&
			(ft_strncmp(s, current->var, ft_strlen(s)) != 0))
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return (NULL);
	prev->next = current->next;
	if (current == *head_ref)
		*head_ref = (*head_ref)->next;
	free(current->var);
	free(current);
	free(s);
	return (*head_ref);
}

char	*equal_actions(t_env **head_ref, char *s1, char *s2, int flag)
{
	char *s;

	if (s1 && !s2 && flag)
	{
		del_node(head_ref, s1);
		return (ft_strjoin(s1, "="));
	}
	if (s1 && s2 && flag)
		del_node(head_ref, s2);
	if (s1 && s2 && !flag)
	{
		ft_putendl_fd("here", 1);
		del_node(head_ref, s1);
		s = ft_strjoin(s1, "=");
		free(s1);
		s1 = ft_strjoin(s, s2);
		free(s);
	}
	return (ft_strdup(s1));
}

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
	free(s);
}