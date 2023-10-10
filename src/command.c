/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:34:44 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/10/10 11:18:13 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	ft_print_er(t_struc *s)
{
	printf("minishell: %s: No such file or directory\n", s->pars[0]);
	s->path = NULL;
}

static int	execute_command(char **path, char **pars, char **env)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(ft_strjoin(ft_strjoin(path[i], "/"),
					pars[0]), X_OK) == 0)
			return (execve(ft_strjoin(ft_strjoin(path[i], "/"),
						pars[0]), pars, env));
		else if (access(pars[0], X_OK) == 0)
			return (execve(pars[0], pars, env));
		i++ ;
	}
	printf("minishell: %s: command not found\n", pars[0]);
	exit(127);
	return (1);
}

int	ft_execve(t_struc *s, int res, int status, char *str)
{
	pid_t	pid;

	if (ft_in_env(s, "PATH") != -1)
	{
		str = ft_find_in_env(s, ft_in_env(s, "PATH"));
		s->path = ft_split(str, ':');
		free(str);
	}
	else
	{
		ft_print_er(s);
		return (1);
	}
	pid = fork ();
	if (pid == 0)
	{
		res = execute_command(s->path, s->pars, s->env);
		exit(res);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	wait(&status);
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	return (res);
}
