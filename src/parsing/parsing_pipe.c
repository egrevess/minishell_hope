/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:52:24 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/19 11:49:59 by emmagrevess      ###   ########.fr       */
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
	while(s->pars[i])
	{
		if (s->pars[i][0] == '|' && ((int) ft_strlen(s->pars[i]) > 1 
			|| (!s->pars[i + 1] || check_only_quotes(s->pars, i + 1) == 0)
			|| ((s->pars[i + 1] && s->pars[i + 1][0] == '|'))))
			return(1);
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

char	**ft_pipe(t_struc *s, t_pipe *p)
{
	int		i;
	int		j;
	int		until;
	int		start;
	int 	nb_pipe;
	char	**temp;
	int		index;

	j = 0;
	i = 0;
	index = 0;
	s->size_pars = len_pars(s->pars);
	nb_pipe = ft_count_pipe(s->pars, p);
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
					while(s->pars[i][j])
					{
						if (s->pars[i][j] == '|')
							break;
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
					while(s->pars[i][j] == '|')
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
		/*
		while (temp[index])
		{
			printf("temp = %s\n", temp[index]);
			index++;
		}
		*/
		//free(s->pars);
		return (temp);
	}	
	else 
		return (s->pars);
}
