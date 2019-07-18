#include "minishell.h"

char	*get_binary_path(char **cmd, t_env **head_ref)
{
	char 	**tab;
	char	*tmp;
	char	*s;
	int		i;


	i = 0;
	tab = get_path(head_ref);
	tmp = ft_strjoin("/", *cmd);
	s = NULL;
	while (tab[i])
	{	
		s = ft_strjoin(tab[i], tmp);
		if (access(s, F_OK) == 0)
		{
			ft_strdel(&(*cmd));
			ft_free2d(tab);
			return (s);
		}
		ft_strdel(&s);
		i++;
	}
	ft_free2d(tab);
	return (*cmd);
}

int		count_words(char **args, int index)
{
	t_defined *lst;
	int		   counter;
	int		   i;
	int		   j;

	lst = init_cases();
	counter = 0;
	i = 0;
	j= 0;
	while (args[i])
	{
		if (!is_one_of_them(args[i], lst))
			counter++;
		else 
		{
			if (index == j)
				return (counter);
			counter = 0;
			j++;
		}
		i++;
	}
	return (counter);
}

char	**get_arg(char **argv, char **token, int index)
{
	int	 len;
	int  i;
	int  j;
	int  f;
	t_defined *lst;
	char **arg;

	len = count_words(argv, index);
	lst = init_cases();
	if (!(arg = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	f = 0;
	while (argv[i])
	{
		if (!is_one_of_them(argv[i], lst))
		{	
			if (index == f)
			{
				arg[j] = ft_strdup(argv[i]);
				j++;
			}
		}
		else 
		{
			if (index == f)
            {
                *token = argv[i];
				return (arg);
            }
			f++;
		}
		i++;
	}
	return (arg);
}

void split_metachar(char *s, int *left, char **token, int *right)
{
	int i;
	int j;

	*left = ft_atoi(s);
	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	j = 0;
	while(ft_isalnum(s[j]))
		j++;
	*token = ft_strsub(s, i, j);
	*right = ft_atoi(s + j);
}

void	create_list2(t_childs **head_ref, t_childs **tail_ref, pid_t child, int index)
{
	t_childs *new_node;

	if (!(new_node = (t_childs *)malloc(sizeof(t_childs))))
		return ;
	new_node->child = child;
	new_node->index = index;
	new_node->next = NULL;
	if ((*head_ref) == NULL)
	{
		(*head_ref) = new_node;
		(*tail_ref) = new_node;
	}
	else
	{
		(*tail_ref)->next = new_node;
		(*tail_ref) = new_node;
	}
	
}

void	_child_pid(t_holder *h, int count)
{
	char	**env;
	char	**arg;
	char	**av1;
	t_childs *tail_ref;
	t_childs *head_ref;
//	int		left;
//	int 	right;
    char    *token;

	int	   fds[2];
	int	   status;
	pid_t  child;
//	pid_t  ch;
	int i;
	(void)status;
	(void)count;
    token = NULL;
	env = get_env(&h->head_ref);
	pipe(fds);
	tail_ref = NULL;
	head_ref = NULL;
	i = 0;
	while (i <= count)
	{
		printf("HELLO1\n");
		child = fork();
		create_list2(&head_ref, &tail_ref, child, i);
		printf("%d ==> head_ref->child => %d\n", i ,tail_ref->child);
		if (child == 0)
		{
			if (i == 0)
			{
				printf("HELLO2\n");
				arg = get_arg(h->lst->cmd, &token, i);
				arg[0]  = get_binary_path(&arg[0], &h->head_ref);	
				if (count != i)		
					dup2(fds[1], 1);
				close(0);
				execve(arg[0], arg, env);
				close(fds[1]);
			}
			else
			{
				printf("HELLO3\n");
				av1 = get_arg(h->lst->cmd, &token, i);
				av1[0] = get_binary_path(&av1[0], &h->head_ref);
				dup2(fds[0], 0);
				close(fds[1]);
				execve(av1[0], av1, env);
			}	
		}
		i++;
	}
	printf("HELLO4\n");
	printf("head_ref->child => %d\n", head_ref->child);
	printf("tail_ref->child => %d\n", tail_ref->child);
	waitpid(tail_ref->child, &status, 0);
	close(fds[1]);
	printf("\n");
	while (head_ref)
	{
	//	printf("HI\n");
		//printf("%d\n", head_ref->child);
		kill(head_ref->child, SIGKILL);
		head_ref = head_ref->next;
	}
}
