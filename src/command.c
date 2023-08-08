/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:34:44 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/03/20 16:31:02 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_execve(t_struc *s)
{
	pid_t	pid;
	int		i;
	
	i = 0;
	pid = fork ();
	if (ft_in_env(s,"PATH") != -1) 
		s->path = ft_split(ft_find_in_env(s, ft_in_env(s,"PATH")), ':');
	if (pid == 0) //processus enfant 
	{
		if (!s->path)
		{
			printf("minishell: %s: command not found\n",s->pars[0]);
			return (1);
		}
		while (s->path[i])
		{
			if (access(ft_strjoin(ft_strjoin(s->path[i],"/"), s->pars[0]), X_OK) == 0)
				return (execve(ft_strjoin(ft_strjoin(s->path[i],"/"),s->pars[0]), s->pars, s->env));
			else if (access(s->pars[0], X_OK) == 0)
				return (execve(s->pars[0], s->pars, s->env));
			i++;
		}
			printf("minishell: %s: command not found\n",s->pars[0]);
			return (1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	return (0);
}