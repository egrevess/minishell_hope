/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:45:54 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 15:48:09 by viburton         ###   ########.fr       */
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

static void	split_pipe_command_utils2(char **temp, int k, int *index, int count)
{
	temp[*index] = malloc(sizeof(char) * (count + 1));
	while (k < count)
	{
		temp[*index][k] = '|';
		k++;
	}
	temp[*index][count] = '\0';
	*index += 1;
}

static void	split_pipe_command_utils3(char c, int *index, int *j, char **temp)
{
	int	count;

	count = 0;
	while (c == '|')
	{
		count++;
		*j += 1;
	}
	split_pipe_command_utils2(temp, 0, index, count);
}

int	split_pipe_command_utils(char **pars, char **temp, int i)
{
	int	start;
	int	index;
	int	j;

	index = 0;
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
				split_pipe_command_utils3(pars[i][j], &index, &j, 0);
		}
		i++;
	}
	return (index);
}
