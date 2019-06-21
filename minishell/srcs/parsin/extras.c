/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:14:25 by aariss            #+#    #+#             */
/*   Updated: 2019/06/19 15:10:11 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

void	print_lst(t__mc	*lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (i < count_tab(lst->cmd))
		{
			printf("%s", lst->cmd[i]);
			i++;
		}
		lst = lst->next;
	}
}

char    *ft_strfchr_alpha(char *s)
{
	char        *str;
	size_t      i;

	if (!(str = (char*)malloc(sizeof(char) * (ft_count_falpha(s) + 1))))
		return (0);
	i = 0;
	while (s[i] && ft_isalpha(s[i]))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char    *ft_strfchr(char *s, int c)
{
	char        *str;
	size_t      i;
	int         len;

	len = ft_count_till(s, c);
	if (!(str = (char*)malloc(sizeof(char) * (ft_count_till(s, c) + 1))))
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_joinchar(char *s, char c)
{
	char	*str;
	int		s_size;
	int		i;

	s_size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_size + 2))))
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

t_defined	*fill_lst(char **tab)
{
	int	i;
	t_defined *head;
	t_defined *lst;

	if (!(lst = (t_defined*)malloc(sizeof(t_defined))))
		return (0);
	i = 0;
	while (i < count_tab(tab))
	{
		lst->data = ft_strdup(tab[i]);
		i++;
		if (i == 1)
			head = lst;
		if (i < count_tab(tab))
		{
			if (!(lst->next = (t_defined*)malloc(sizeof(t_defined))))
				return (0);
			lst = lst->next;
		}
	}
	lst->next = NULL;
	return (head);
}

t_defined	*init_cases(void)
{
	char **defined;

	if (!(defined = (char**)malloc(sizeof(char*) * 19)))
		return (0);
	defined[0] = ft_strdup(">");
	defined[1] = ft_strdup("<");
	defined[2] = ft_strdup("1>");
	defined[3] = ft_strdup("2>");
	defined[4] = ft_strdup("1<");
	defined[5] = ft_strdup("2<");
	defined[6] = ft_strdup("1>>");
	defined[7] = ft_strdup("2>>");
	defined[8] = ft_strdup("&>");
	defined[9] = ft_strdup(">&");
	defined[10] = ft_strdup("&>>");
	defined[11] = ft_strdup("1<&");
	defined[12] = ft_strdup("2<&");
	defined[13] = ft_strdup("1<&2");
	defined[14] = ft_strdup("2<&1");
	defined[15] = ft_strdup("1>&2");
	defined[16] = ft_strdup("2>&1");
	defined[17] = ft_strdup("|");
	defined[18] = NULL;
	return (fill_lst(defined));
}
