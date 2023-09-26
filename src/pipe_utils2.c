/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:56:16 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/25 15:21:15 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*ft_strjoin_pipe(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free ((char *) s1);
	return (str);
}

int	ft_pipes(t_struc *s, t_pipe *p)
{
	if (check_pipe(s, p) == 1)
	{
		printf("Error: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

t_list	*init_list(t_struc *s, t_list *c, int i)
{
	char	*command;

	command = NULL;
	while (s->pars[i])
	{
		if (s->pars[i][0] != '|')
		{
			if (command == NULL)
				command = ft_strjoin(s->pars[i], " ");
			else
			{
				command = ft_strjoin_pipe(command, s->pars[i]);
				command = ft_strjoin_pipe(command, " ");
			}
		}
		else
		{
			ft_lstadd_back(&c, ft_lstnew(command));
			command = NULL;
		}
		i++;
	}
	ft_lstadd_back(&c, ft_lstnew(command));
	ft_lstadd_back(&c, ft_lstnew(NULL));
	return (c);
}

int	ft_execve_pipe(t_struc *s, char **command)
{
	int		i;

	i = 0;
	if (ft_in_env(s, "PATH") != -1)
		s->path = ft_split(ft_find_in_env(s, ft_in_env(s, "PATH")), ':');
	if (!s->path)
	{
		printf("minishell: %s: command not found\n", command[0]);
		exit(EXIT_FAILURE);
	}
	while (s->path[i])
	{
		if (access(ft_strjoin(ft_strjoin(s->path[i], "/"),
					command[0]), X_OK) == 0)
			return (execve(ft_strjoin(ft_strjoin(s->path[i], "/"),
						command[0]), command, s->env));
		else if (access(command[0], X_OK) == 0)
			return (execve(command[0], command, s->env));
		i++;
	}
	printf("minishell: %s: command not found\n", command[0]);
	return (1);
}

int	ft_count_pipe1(t_struc *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s->pars[i])
	{
		if (s->pars[i][0] == '|' && (int) ft_strlen(s->pars[i]) == 1)
			j++;
		i++;
	}
	s->nb_pipe = j;
	return (j);
}
