/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:34:44 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/04 14:52:37 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
	return (1);
}

int	ft_execve(t_struc *s)
{
	pid_t	pid;
	int		res;

	pid = fork ();
	if (ft_in_env(s, "PATH") != -1)
		s->path = ft_split(ft_find_in_env(s, ft_in_env(s, "PATH")), ':');
	if (pid == 0)
	{
		if (!s->path)
			return (printf("minishell: %s: command not found\n", s->pars[0]), 1);
		res = execute_command(s->path, s->pars, s->env);
		return (res);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	return (0);
}
