/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:52:27 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 12:08:53 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	is_pipe(char c, char prev, int in_quotes)
{
	if (c == '|' && prev != '|' && !in_quotes)
		return (1);
	return (0);
}

static int	is_quote(char c, int *in_quotes)
{
	if (c == '\'' && (*in_quotes == 0 || *in_quotes == 1))
	{
		*in_quotes = 1;
		return (1);
	}
	else if (c == '\"' && (*in_quotes == 0 || *in_quotes == 2))
	{
		*in_quotes = 2;
		return (1);
	}
	return (0);
}

int	ft_count_pipe(char **line, t_pipe *p, int j, int i)
{
	int		nb;
	int		in_quotes;
	char	prev;

	nb = 0;
	in_quotes = 0;
	while (line[i])
	{
		j = 0;
		prev = 0;
		while (line[i][j])
		{
			if (is_pipe(line[i][j], prev, in_quotes))
				nb++;
			else if (is_quote(line[i][j], &in_quotes))
				;
			prev = line[i][j];
			j++;
		}
		i++;
	}
	p->nb_pipe = nb;
	return (nb);
}
