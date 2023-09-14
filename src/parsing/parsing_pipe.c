/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:52:24 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/14 16:44:04 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	check_only_quotes(char **pars, int i)
{
	int	j;

	while (pars[i])
	{
		j = 0;
		while (pars[i][j])
		{
			if (pars[i][j] != '\'' || pars[i][j] != '\"')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_pipe(t_struc *s, t_pipe *p)
{
	int	i;

	i = 0;
	p->nb_pipe = 0;
	while (s->pars[i])
	{
		if (s->pars[i][0] == '|' && (int) ft_strlen(s->pars[i]) == 1)
			p->nb_pipe++;
		i++;
	}
	i = 0;
	while (s->pars[i])
	{
		if (s->pars[i][0] == '|' && ((int) ft_strlen(s->pars[i]) > 1
			|| (!s->pars[i + 1] || check_only_quotes(s->pars, i + 1) == 0)
			|| ((s->pars[i + 1] && s->pars[i + 1][0] == '|'))))
			return (1);
		i++;
	}
	return (0);
}

int	len_pars(char **pars)
{
	int	i;

	i = 0;
	while (pars[i])
	{
		i++;
	}
	return (i);
}

char	**ft_pipe(t_struc *s, t_pipe *p)
{
	int	nb_pipe;

	s->size_pars = len_pars(s->pars);
	nb_pipe = ft_count_pipe(s->pars, p, 0, 0);
	if (nb_pipe > 0)
	{
		return (split_pipe_commands(s->pars, p, 0, 0));
	}
	else
		return (s->pars);
}
