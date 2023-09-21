/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:52:24 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/20 17:05:58 by viburton         ###   ########.fr       */
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

void	pipe_utils2(t_struc *s, t_ij *t, char **temp)
{
	t->until = 0;
	t->start = t->j;
	while (s->pars[t->i][t->j] && s->pars[t->i][t->j] != '|')
		t->j++;
	temp[t->index] = malloc(sizeof(char *) * (t->j - t->start + 1));
	while (t->j > t->start)
	{
		temp[t->index][t->until] = s->pars[t->i][t->start];
		t->until++;
		t->start++;
	}
	temp[t->index][t->until] = '\0';
	t->index++;
}

void	pipe_utils(t_struc *s, t_ij *t, char **temp)
{
	int	nb_pipe;

	nb_pipe = 0;
	if (s->pars[t->i][t->j] != '|')
		pipe_utils2(s, t, temp);
	else if (s->pars[t->i][t->j] == '|')
	{
		t->until = 0;
		while (s->pars[t->i][t->j] == '|')
		{
			nb_pipe++;
			t->j++;
		}
		temp[t->index] = malloc(sizeof(*temp[t->index]) * (nb_pipe + 1));
		while (nb_pipe > 0)
		{
			temp[t->index][t->until] = '|';
			nb_pipe--;
			t->until++;
		}
		temp[t->index][t->until] = '\0';
		t->index++;
	}
}

char	**ft_pipe(t_struc *s, t_pipe *p)
{
	t_ij	t;
	int		nb_pipe;
	char	**temp;

	t.j = 0;
	t.i = 0;
	t.index = 0;
	s->size_pars = ft_len_tab(s->pars);
	nb_pipe = ft_count_pipe(s->pars, p);
	if (nb_pipe <= 0)
		return (s->pars);
	temp = malloc(sizeof(*temp) * (s->size_pars + nb_pipe + 1));
	if (!temp)
		exit(EXIT_FAILURE);
	while (s->pars[t.i])
	{
		t.j = 0;
		while (t.j <= ((int) ft_strlen(s->pars[t.i]) - 1))
			pipe_utils(s, &t, temp);
		t.i++;
	}
	temp[t.index] = NULL;
	return (temp);
}
