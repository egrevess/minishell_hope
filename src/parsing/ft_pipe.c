/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:12:51 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 15:46:51 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	**allocate_commands(int size)
{
	char	**commands;

	commands = malloc(sizeof(char *) * (size + 1));
	if (!commands)
		exit(EXIT_FAILURE);
	return (commands);
}

static char	**split_pipe_commands(char **pars, t_pipe *p)
{
	int		index;
	int		nb_pipe;
	int		size;
	char	**temp;

	nb_pipe = ft_count_pipe(pars, p, 0, 0);
	size = len_pars(pars) + nb_pipe + 1;
	temp = allocate_commands(size);
	index = split_pipe_command_utils(pars, temp, 0);
	temp[index] = NULL;
	return (temp);
}

char	**ft_pipe(t_struc *s, t_pipe *p)
{
	int	nb_pipe;

	nb_pipe = ft_count_pipe(s->pars, p, 0, 0);
	s->size_pars = len_pars(s->pars);
	if (nb_pipe > 0)
	{
		return (split_pipe_commands(s->pars, p));
	}
	else
		return (s->pars);
}
