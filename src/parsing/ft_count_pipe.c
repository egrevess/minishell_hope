/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:52:27 by viburton          #+#    #+#             */
/*   Updated: 2023/09/20 12:17:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
/*
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
*/

int	ft_count_pipe(char **line, t_pipe *p)
{
	int	i;
	int	j;
	int	nb;
	int check;
	int	len;
	int quotes;
	int two;
	
	i = 0;
	nb = 0;
	quotes = 0;
	while (line[i])
	{
		check = -2;
		j = 0;
		len = ft_strlen(line[i]);
		two = 0;
		while (line[i][j])
		{
			if (check != -2 && line[i][j - 1] == '|' && line[i][j] != '|' && quotes == 0)
				nb++;
			else if (line[i][j] == '\'' && (two == 0 || two == 1))
			{
				if (quotes == 0)
				{
					two = 1;
					quotes = 1;
				}
				else if (quotes == 1)
				{
					two = 0;
					quotes = 0;
				}
			}
			else if (line[i][j] == '\"' && (two == 0 || two == 2))
			{
				if (quotes == 0)
				{
					two = 2;
					quotes = 1;
				}
				else if (quotes == 1)
				{
					two = 0;
					quotes = 0;
				}
			}
			else if (line[i][j] == '|' && len > 1 && quotes == 0)
			{
				if (check != j - 1 && j != 0 )
					nb++;
				check = j;
			}
			j++;
		}
		i++;
	}
	//printf("%d\n", nb);
	p->nb_pipe = nb;
	return (nb);
}
