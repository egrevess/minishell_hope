/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:52:27 by viburton          #+#    #+#             */
/*   Updated: 2023/09/20 17:05:08 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	cnt_pipe_utils1(int *quotes, int *two)
{
	if (*quotes == 0)
	{
		*two = 1;
		*quotes = 1;
	}
	else if (*quotes == 1)
	{
		*two = 0;
		*quotes = 0;
	}
}

static void	cnt_pipe_utils2(int *quotes, int *two)
{
	if (*quotes == 0)
	{
		*two = 2;
		*quotes = 1;
	}
	else if (*quotes == 1)
	{
		*two = 0;
		*quotes = 0;
	}
}

static void	ft_cnt_pipe_utils(char **line, t_ij *t, int *nb, int *quotes)
{
	int	check;
	int	two;

	check = -2;
	two = 0;
	t->j = 0;
	while (line[t->i][t->j])
	{
		if (check != -2 && line[t->i][t->j - 1] == '|'
				&& line[t->i][t->j] != '|' && *quotes == 0)
			*nb += 1;
		else if (line[t->i][t->j] == '\'' && (two == 0 || two == 1))
			cnt_pipe_utils1(quotes, &two);
		else if (line[t->i][t->j] == '\"' && (two == 0 || two == 2))
			cnt_pipe_utils2(quotes, &two);
		else if (line[t->i][t->j] == '|'
				&& ft_strlen(line[t->i]) > 1 && *quotes == 0)
		{
			if (check != t->j - 1 && t->j != 0)
				*nb += 1;
			check = t->j;
		}
		t->j++;
	}
	t->i++;
}

int	ft_count_pipe(char **line, t_pipe *p)
{
	t_ij	t;
	int		nb;
	int		quotes;

	t.i = 0;
	nb = 0;
	quotes = 0;
	while (line[t.i])
		ft_cnt_pipe_utils(line, &t, &nb, &quotes);
	p->nb_pipe = nb;
	return (nb);
}
