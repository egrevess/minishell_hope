/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:45:54 by viburton          #+#    #+#             */
/*   Updated: 2023/09/18 11:16:44 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*extract_command(char *input, int start, int end)
{
	int		len;
	char	*command;
	int		i;

	len = end - start;
	i = 0;
	command = malloc(sizeof(char) * (len + 1));
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

	commands = (char **)malloc(sizeof(char *) * (size + 1));
	if (!commands)
		exit(EXIT_FAILURE);
	return (commands);
}

static void	extract_pipe_symbols(char **pars, char **temp, int *index, t_ij *t)
{
	int	count;
	int	k;

	k = 0;
	count = 0;
	while (pars[t->i][t->j] == '|')
	{
		count++;
		t->j += 1;
	}
	temp[*index] = (char *)malloc(sizeof(char) * (count + 1));
	if (!temp[*index])
		exit(EXIT_FAILURE);
	while (k < count)
	{
		temp[*index][k] = '|';
		k++;
	}
	temp[*index][count] = '\0';
	(*index)++;
}

static void	extract_npipe_cmnd(char **pars, char **temp, int *index, int i)
{
	int		start;
	t_ij	t;

	t.j = 0;
	start = t.j;
	while (pars[i][t.j])
	{
		if (pars[i][t.j] != '|')
		{
			while (pars[i][t.j] && pars[i][t.j] != '|')
				t.j += 1;
			temp[*index] = extract_command(pars[i], start, t.j);
			(*index)++;
		}
		else if (pars[i][t.j] == '|')
		{
			t.i = i;
			extract_pipe_symbols(pars, temp, index, &t);
		}
	}
}

char	**split_pipe_commands(char **pars, t_pipe *p, int i, int j)
{
	int		index;
	int		nb_pipe;
	int		size;
	char	**temp;

	index = 0;
	nb_pipe = ft_count_pipe(pars, p, 0, 0);
	size = len_pars(pars) + nb_pipe + 1;
	temp = allocate_commands(size);
	while (pars[i])
	{
		j = 0;
		extract_npipe_cmnd(pars, temp, &index, i);
		i++;
	}
	temp[index] = NULL;
	return (temp);
}
