/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:12:51 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 15:04:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*extract_command(char *input, int start, int end)
{
	int		len;
	char	*command; 
	int		i;

	len = end - start;
	command = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!command)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		command[i] = input[start + i];
		i++;
	}
	command[len] = '\0';
	return (command);
}

static char	**allocate_commands(int size)
{
	char	**commands;

	commands = malloc(sizeof(char *) * (size + 1));
	if (!commands)
		exit(EXIT_FAILURE);
	return (commands);
}

static int split_pipe_command_utils(char **pars, char **temp, int i)
{
	int count;
	int	k;
	int start;
	int	index;
	int	j;

	index = 0;
	count = 0;
	k = 0;
	while (pars[i])
	{
		j = 0;
		while (pars[i][j])
		{
			if (pars[i][j] != '|')
			{
				start = j;
				while (pars[i][j] && pars[i][j] != '|')
					j++;
				temp[index] = extract_command(pars[i], start, j);
				index++;
			}
			else if (pars[i][j] == '|')
			{
				while (pars[i][j] == '|')
				{
					count++;
					j++;
				}
				temp[index] = malloc(sizeof(char) * (count + 1));
				while (k < count)
				{
					temp[index][k] = '|';
					k++;
				}
				temp[index][count] = '\0';
				index++;
			}
		}
		i++;
	}
	return (index);
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
