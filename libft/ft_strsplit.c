/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:53:56 by mfilahi           #+#    #+#             */
/*   Updated: 2019/05/14 17:23:39 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_words_count(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int		ft_word_len(char *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		break ;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**argv;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	len = ft_words_count((char *)s, c);
	if (!(argv = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (*s && len-- > 0)
	{
		while (*s && *s == c)
			s++;
		argv[i] = ft_strnew((size_t)ft_word_len((char *)s, c));
		j = 0;
		while (*s && *s != c)
			argv[i][j++] = *s++;
		argv[i][j] = '\0';
		i++;
	}
	argv[i] = 0;
	return (argv);
}
