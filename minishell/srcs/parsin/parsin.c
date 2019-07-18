/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:21 by aariss            #+#    #+#             */
/*   Updated: 2019/07/16 11:41:06 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*skip_quote(char *line)
{
	char	*str;
	int		keeper;
	int		i;
	int		k;

	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (0);
	i = -1;
	k = 0;
	while (line[++i])
	{
		(ft_isspace(line[i])) ? line[i] = -1 : 1;
		if (ft_isquote(line[i]))
		{
			keeper = line[i];
			if (line[i + 1])
				while (line[++i] != keeper)
				{
					if (line[i] == -7)
					{
						i = i + 2;
						str[k++] = keeper;
					}
					else
						str[k++] = line[i];
				}
		}
		else
			str[k++] = line[i];
	}
	while (k < (int)ft_strlen(line))
		str[k++] = '\0';
	return (str);
}

char	*skip_token(char *str, char *line, int *t)
{
	int	i;

	i = 0;
	while (ft_istoken(line[i]))
	{
		str = ft_joinchar(str, line[i]);
		i++;
	}
	if (ft_isdigit(line[i]))
	{
		while(ft_isdigit(line[i]))
		{
			str = ft_joinchar(str, line[i]);
			i++;
		}
	}
	else if (line[i] == '-')
	{
		str = ft_joinchar(str, line[i]);
		i++;
	}
	*t = i;
	return (str);
}

char	*skip_char(char *str, char *line, int *i, int definer, int quote)
{
	if (definer == 1)
	{
		(*i)++;
		if (line[*i] == 'n')
			str = ft_joinchar(str, '\n');
		else if (line[*i] == 't')
			str = ft_joinchar(str, '\t');
		else if (line[*i] == 'r')
			str = ft_joinchar(str, '\r');
		else if (line[*i] == 'v')
			str = ft_joinchar(str, '\v');
		else if (line[*i] == 'f')
			str = ft_joinchar(str, '\f');
		else if (line[*i] == quote)
		{
			str = ft_joinchar(str, -7);
			str = ft_joinchar(str, line[*i]);
			str = ft_joinchar(str, -7);
		}

		else
			str = ft_joinchar(str, line[*i]);
	}
	else if (definer == 0)
	{
		(*i)++;
		if (line[*i] == '"')
		{
			str = ft_joinchar(str, 39);
			str = ft_joinchar(str, line[*i]);
			str = ft_joinchar(str, 39);
		}
		else if (line[*i] == 39)
		{
			str = ft_joinchar(str, '"');
			str = ft_joinchar(str, line[*i]);
			str = ft_joinchar(str, '"');
		}
		else
			str = ft_joinchar(str, line[*i]);
	}
	return (str);
}

char	*tokens_master(char *str, char *line, int *i)
{
	int	t;
	int	v;

	t = 0;
	v = 0;
	str = ft_joinchar(str, -1);
	while (ft_isdigit(line[*i]))
	{
		str = ft_joinchar(str, line[*i]);
		(*i)++;
		t = 1;
	}
	if (line[*i] == '&')
	{
	//	if (t == 1) /* TOO EARLY TO DELETE */
	//		str = ft_joinchar(str, -1);
		if (line[(*i) + 1] != '<')
			str = ft_joinchar(str, line[*i]);
		(*i)++;
		if (line[*i] == '>')
		{
			str = ft_joinchar(str, line[*i]);
			(*i)++;
		}
		else
		{
			while (line[*i] == '<')
				(*i)++;
		}
		str = ft_joinchar(str, -1);
	}
	else if (line[*i] == '<')
	{
		str = ft_joinchar(str, line[*i]);
		(*i)++;
		if (line[*i] == '<')
		{
			str = ft_joinchar(str, line[*i]);
			(*i)++;
		}
		else if (line[*i] == '&' && t == 1)
		{
			str = ft_joinchar(str, line[*i]);
			(*i)++;
			if (ft_isdigit(line[*i]))
			{
				while (ft_isdigit(line[*i]))
				{
					str = ft_joinchar(str, line[*i]);
					(*i)++;
				}
			}
			else if (line[*i] == '-')
			{
				str = ft_joinchar(str, line[*i]);
				(*i)++;
			}
		}
		else if (line[*i] == '&' && t == 0)
		{
			str = ft_joinchar(str, line[*i]);
			(*i)++;
			if (line[*i] == '-')
			{
				str = ft_joinchar(str, line[*i]);
				(*i)++;
			}
		}
		str = ft_joinchar(str, -1);
	}
	else if (line[*i] == '>')
	{
		str = ft_joinchar(str, line[*i]);
		(*i)++;
		if (line[*i] == '>' || line[*i] == '&')
		{
			v = (line[*i] == '&') ? 1 : 0;
			str = ft_joinchar(str, line[*i]);
			(*i)++;
		}
		if (v == 1)
		{
			if (ft_isdigit(line[*i]))
			{
				while (ft_isdigit(line[*i]))
				{
					str = ft_joinchar(str, line[*i]);
					(*i)++;
				}
			}
			else if (line[*i] == '-')
			{
				str = ft_joinchar(str, line[*i]);
				(*i)++;
			}
		}
		str = ft_joinchar(str, -1);
	}
	return (str);
}

char	*parsin(char *line, t_env *env, t_defined *lst)
{
	int			i;
	int			keeper;
	int			t;
	char		*str;

	(void)lst;
	i = 0;
	t = 0;
	str = ft_strdup("");
	/* FIX TILDE HERE */
	if (line)
	{
		while (i < (int)ft_strlen(line))
		{
			if (line[i] == 92)
				str = skip_char(str, line, &i, 0, 0);
			else if (ft_isquote(line[i]))
			{
				keeper = line[i];
				str = ft_joinchar(str, line[i]);
				i++;
				while (line[i] != keeper)
				{
					if (line[i] == 92)
						str = skip_char(str,line, &i, 1, keeper);
					else if (line[i] == '$' && ft_strlen(line + i + 1) > 2)
						str = dollar_handle_quoted(str, line, &i, keeper, env);
					else
						str = ft_joinchar(str, line[i]);
					i++;
				}
				str = ft_joinchar(str, line[i]);
			}
			else if ((ft_isdigit(line[i]) && got_token_after_digit(line + i)) || ft_istoken(line[i]))
			{
				str = tokens_master(str ,line, &i);
				while (ft_istoken(line[i]))
					i++;
				i--;
			}
			else if (line[i]  == ';')
				str = ft_joinchar(str, -3);
			else if (line[i] == '|')
				str = ft_joinchar(str, -4);
			else if (line[i] == '$' && ft_strlen(line + i + 1) > 1)
				str = dollar_handle_simple(str, line, &i, env);
			else if (line[i] == '~')/* AND REMOVE THIS */
				str = ft_strjoin(str, get_var("HOME=", &env));
			else
				str = ft_joinchar(str, line[i]);
			i++;
		}
		return (skip_quote(str));
	}
	return (NULL);
}

t__mc	*mc_lst(char **mc)
{
	t__mc	*lst;
	t__mc	*head;
	int		i;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	i = 0;
	while (i < count_tab(mc))
	{
		lst->cmd = ft_strsplit(mc[i], -4);
		i++;
		if (i == 1)
			head = lst;
		if (i < count_tab(mc))
		{
			if (!(lst->next = (t__mc*)malloc(sizeof(t__mc))))
				return (NULL);
			lst = lst->next;
		}
	}
	lst->next = NULL;
	return (head);
}

t_info	*add_demi(char *kratos, char *file ,int *t, int def, int file_identifier)
{
	t_info *one;
	int		f;

	if (!(one = (t_info*)malloc(sizeof(t_info))))
		return (0);
	f = ft_strlen(kratos) - 1;
	if (def == 1)
	{
		if (file_identifier == 1)
		{
			if (file)
				one->file = ft_strdup(file);
			else
				one->file = ft_strdup("PARSIN_ERROR");
		}
		else
			one->file = ft_strdup("no_file");
		one->sfd = (ft_isdigit(kratos[0])) ? retrieve_the_digit(kratos, 0) : 0;
		one->dfd = (ft_isdigit(kratos[f])) ? retrieve_the_digit(kratos, 1) : 0;
		if (alright_token(kratos) != 1 && ft_strchr(kratos, '&'))
			one->read_meth = 0;
		else if (alright_token(kratos) == 1 && ft_strchr(kratos, '<')
				&& !ft_strchr(kratos, '-'))
			one->read_meth = -2;
		else if (alright_token(kratos) == 2 && ft_strchr(kratos, '<')
				&& (!ft_strchr(kratos, '&') || !ft_strchr(kratos, '-')))
			one->read_meth = -3;
		else if (alright_token(kratos) == 1 && ft_strchr(kratos, '>')
				&& !ft_strchr(kratos, '-'))
			one->read_meth = 1;
		else if (alright_token(kratos) == 2 && ft_strchr(kratos, '>')
				&& (!ft_strchr(kratos, '&') || !ft_strchr(kratos, '-')))
			one->read_meth = 2;
		else
			one->read_meth = 0;
	}
	else if (def == 0)
	{
		one->file = ft_strdup("-1");
		one->sfd = -1;
		one->dfd = -1;
		one->read_meth = -1;
	}
	one->next = NULL;
	(*t)++;
	return (one);
}

void	add_casual(t_god **lst, t_info **head ,char **kratos, int *i, int *v)
{
	if (*v == 0)
	{
		(*lst)->demi_god = add_demi(kratos[*i], NULL,&(*v), 1, 0);
		*head = (*lst)->demi_god;
	}
	else
	{
		(*lst)->demi_god->next = add_demi(kratos[*i], NULL,&(*v), 1, 0);
		(*lst)->demi_god = (*lst)->demi_god->next;
	}
}

void	add_file(t_god **lst, t_info **head ,char **kratos, int *i, int *v)
{
	int	keeper;
	int	keeper_plus;

	keeper = *i;
	keeper_plus = *i + 1;
	if (kratos[keeper_plus])
	{
		(*i)++;
		if (*v == 0)
		{
			(*lst)->demi_god = add_demi(kratos[keeper], kratos[*i], &(*v), 1, 1);
			*head = (*lst)->demi_god;
		}
		else
		{
			(*lst)->demi_god->next = add_demi(kratos[keeper], kratos[*i], &(*v), 1, 1);
			(*lst)->demi_god = (*lst)->demi_god->next;
		}
	}
	else
	{
		ft_putendl_fd("21sh: parse error near `\\n'", 1);
	}
	/* TO BREAK THIS FROM THE LOOP DOWN BELLOW TURN THE FUNCTION INTO INT --> USEFUL TRICK */
}

int		got_first_digit(char *kratos)
{
	int	i;

	if (ft_isdigit(kratos[0]))
	{
		i = 0;
		while (ft_isdigit(kratos[i]))
			i++;
		if (kratos[i] == '&' && kratos[i + 1] == '>')
			i++;
		while (kratos[i] == '<' || kratos[i] == '>')
			i++;
		if (kratos[i] == '&' || ft_isdigit(kratos[i]) || kratos[i] == '-')
			return (0);
		return (1);
	}
	return (0);
}

int		ultimate_check(char *kratos)
{
	int	i;

	i = 0;
	if (ft_strcmp(kratos, ">") == 0
			|| ft_strcmp(kratos, "<") == 0
			|| ft_strcmp(kratos, ">>") == 0
			|| ft_strcmp(kratos, "<<") == 0
			|| ft_strcmp(kratos, "&>") == 0)
		return (1);
	else if (ft_isdigit(kratos[i]))
	{
		while(ft_isdigit(kratos[i]))
			i++;
		if (kratos[i] == '&' && kratos[i + 1] == '>')
			return (1);
		else if (kratos[i] == '>' && kratos[i + 1] == '&')
		{
			i = i + 2;
			if (ft_isdigit(kratos[i]))
			{
				while (ft_isdigit(kratos[i]))
					i++;
				if (ft_isalpha(kratos[i]))
					return (1);
				else
					return (2);
			}
			return (1);
		}
		else if (kratos[i] == '<' && kratos[i + 1] == '&')
		{
			 i = i + 2;
			 if (ft_isdigit(kratos[i]))
				 return (1);
		}
		else if (kratos[i] == '>' || kratos[i] == '<')
			return (1);
	}
	else if (kratos[i] == '<' && kratos[i + 1] == '&')
	{
		i = i + 2;
		if (ft_isdigit(kratos[i]))
		    return (1);
	}
	return (0);
}

void	not_known_as_if(char **kratos, t_god **lst, int *t)
{
	int		i;
	int		v;
	int		j;
	t_info	*head;

	i = 0;
	j = 0;
	v = 0;
	if (!((*lst)->cmd = (char **)malloc(sizeof(char *) *  count_arg(kratos))))
		return ;
	while (kratos[i])
	{
		if (ultimate_check(kratos[i]) == 1)
			add_file(&(*lst), &head, kratos, &i, &v);
		else if (ultimate_check(kratos[i]) == 2)
			add_casual(&(*lst), &head, kratos, &i, &v);
		else
		{
			(*lst)->cmd[j] = ft_strdup(kratos[i]);
			j++;
		}
		i++;
	}
	if (v == 0)
	{
		(*lst)->demi_god = add_demi(kratos[i], NULL,&v, 0, 0);
		head = (*lst)->demi_god;
	}
	(*lst)->cmd[j] = NULL;
	(*lst)->demi_god = head;
	(*t)++;
}

t_god	*well_you_know(char **cmd, t_god **lst, int *t)
{
	t_god	*head;
	t_god	*predictor;
	char	**kratos;
	int		i;

	i = 0;
	while (cmd[i])
	{
		kratos = ft_strsplit(cmd[i], -1);
		if (*t == 0)
			head = *lst;
		not_known_as_if(kratos, &(*lst), &(*t));
		if (!((*lst)->next = (t_god*)malloc(sizeof(t_god))))
			return (0);
		predictor = (*lst);
		(*lst) = (*lst)->next;
		ft_free2d(kratos);
		i++;
	}
	predictor->next = NULL;
	return (head);
}

t_god	*last_splice(t__mc **old_lst)
{
	t_god	*lst;
	t_god	*head;
	int		t;

	if (!(lst = (t_god*)malloc(sizeof(t_god))))
		return (0);
	t = 0;
	head = well_you_know((*old_lst)->cmd, &lst, &t);
	(*old_lst) = (*old_lst)->next;
	return (head);
}

t__mc	*mc_maker(char *line, t_env *env)
{
	char		**slice;
	char		*parsed;
	t_defined	*tokens;
	t__mc		*lst;

	tokens = init_cases();
	parsed = parsin(line, env, tokens);
	if (parsed[ft_strlen(parsed)] == '\n')
		parsed[ft_strlen(parsed)] = '\0';
	slice = ft_strsplit(parsed, -3);
	lst = mc_lst(slice);
	return (lst);
}
