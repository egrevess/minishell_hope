/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:52:24 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/12 12:05:35 by viburton         ###   ########.fr       */
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
	int		i;
	int		j;
	int		until;
	int		start;
	int		nb_pipe;
	char	**temp;
	int		index;

	j = 0;
	i = 0;
	index = 0;
	s->size_pars = len_pars(s->pars);
	nb_pipe = ft_count_pipe(s->pars, p, 0, 0);
	if (nb_pipe > 0)
	{
		printf("size pars = %d\n", s->size_pars);
		printf("nb_pipe = %d\n", nb_pipe);
		printf("size malloc %d\n", s->size_pars + nb_pipe + 1);
		temp = malloc(sizeof(*temp) * (s->size_pars + nb_pipe + 1));
		if (!temp)
			exit(EXIT_FAILURE);
		while (s->pars[i])
		{
			j = 0;
			while (j <= ((int) ft_strlen(s->pars[i]) - 1))
			{
				nb_pipe = 0;
				if (s->pars[i][j] != '|')
				{
					until = 0;
					start = j;
					while (s->pars[i][j])
					{
						if (s->pars[i][j] == '|')
							break ;
						j++;
					}
					printf("inde = %d\n", index);
					temp[index] = malloc(sizeof(char *) * (j - start + 1));
					while (j > start)
					{
						temp[index][until] = s->pars[i][start];
						until++;
						start++;
					}
					temp[index][until] = '\0';
					index++;
				}
				else if (s->pars[i][j] == '|')
				{
					until = 0;
					while (s->pars[i][j] == '|')
					{
						nb_pipe++;
						j++;
					}
					printf("inde = %d\n", index);
					temp[index] = malloc(sizeof(*temp[index]) * (nb_pipe + 1));
					while (nb_pipe > 0)
					{
						temp[index][until] = '|';
						nb_pipe--;
						until++;
					}
					temp[index][until] = '\0';
					index++;
				}
			}
			i++;
		}
		temp[index] = NULL;
		index = 0;
		return (temp);
	}
	else
		return (s->pars);
}
