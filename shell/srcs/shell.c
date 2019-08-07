/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:38:37 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/07 19:25:41 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	keephistory(t_his **his_tail, char *hline)
{
	int			len;
	static char	*lline;

	len = ft_strlen(hline);
	hline[len - 1] = '\0';
	if (!(*his_tail))
		lline = ft_strdup(hline);
	else
	{
		if (ft_strcmp(hline, lline) == 0)
			return ;
		free(lline);
		lline = ft_strdup(hline);
	}
	keephistorylst(his_tail, hline);
	ft_strdel(&hline);
}

/*
** - get line from readline func;
*/

char	*call_readline(t_holder *h, int *flag)
{
	if (g_signal_num == 3)
		g_signal_num = 1;
	else
	{
		h->line = ft_readline("$> ", h->his_tail, 0);
		ft_putchar_fd('\n', 1);
	}
	*flag = 0;
	if (!h->line)
	{
		*flag = 1;
		return (NULL);
	}
	else if (h->line[0] == '\n' || just_spaces(h->line))
		return (NULL);
	return (recall_readline(h));
}

void	shell_1(t_holder *h, int i, int count)
{
	t_cmd	*valhala;
	t__mc	*curr;

	keephistory(&h->his_tail, ft_strdup(h->line));
	h->mclst = mc_maker(h->line, h->head_ref);
	ft_strdel(&h->line);
	h->line = ft_strnew(1);
	curr = h->mclst;
	count = count_mclst(curr);
	i = 0;
	while (i < count)
	{
		valhala = last_splice(&curr, h->head_ref);
		h->lst = valhala;
	//	print_lstra(valhala);
		if (valhala->cmd[0])
			darlin_g(h);
		free_main_lst(valhala);
		i++;
	}
	free_list_mc(curr);
}

void	shell(t_holder *h)
{
	int			flag;

	flag = 0;
	while ("21sh")
	{
		while (((!(call_readline(h, &flag)) && !flag)) || (g_signal_num == 3))
			;
		if (!flag)
		{
			if (h->line[0] == PIPE)
			{
				ft_putstr_fd("21sh: parse error near ", 2);
				ft_putchar_fd(h->line[0], 2);
				ft_putchar_fd('\n', 2);
				ft_strdel(&h->line);
				h->line = ft_strnew(1);
			}
			else
				shell_1(h, 0, 0);
		}
		else
			break ;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_holder *h;

	(void)ac;
	(void)av;
	fd2 = fopen("/dev/ttys002", "a+");
	g_signal_num = 1;
	signal(SIGINT, signal_handler);
	h = ft_memalloc(sizeof(t_holder));
	h->head_ref = copy_of_env(envp);
	shell(h);
	free_structure(h);
	return (0);
}
