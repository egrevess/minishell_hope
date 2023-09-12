/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort_par.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:45:47 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/05 15:09:05 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_copy_env(t_struc	*s)
{
	int	i;

	i = 0;
	s->copy_env = malloc (sizeof(*s->copy_env) * (s->lenght_env + 1));
	if (!s->copy_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (s->env[i])
	{
		s->copy_env[i] = ft_strdup(s->env[i]);
		i++;
	}
	s->copy_env[i] = NULL;
}

void	ft_swap(int n, int a, t_struc *s)
{
	char	*temp;

	temp = s->copy_env[n];
	s->copy_env[n] = s->copy_env[a];
	s->copy_env[a] = temp;
}

int	ft_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static void	sortenv_utils(t_struc *s, int i, int j)
{
	while (s->copy_env[i])
	{
		j = 0;
		printf("declare -x ");
		while (s->copy_env[i][j] != '=')
		{
			printf("%c", s->copy_env[i][j]);
			j++;
		}
		printf("=\"");
		j++;
		while (s->copy_env[i][j])
		{
			printf("%c", s->copy_env[i][j]);
			j++;
		}
		printf("\"\n");
		i++;
	}
	g_output = 0;
	ft_free_array(s->copy_env, i - 1);
}

void	ft_sort_env(t_struc *s)
{
	int		i;
	int		j;

	j = 0;
	ft_copy_env(s);
	if (!s->copy_env)
	{
		g_output = 1;
		exit(EXIT_FAILURE);
	}
	while (j < s->lenght_env - 1)
	{
		i = j + 1;
		while (i < s->lenght_env)
		{
			if (ft_compare(s->copy_env[j], s->copy_env[i]) > 0)
			{
				ft_swap(j, i, s);
			}
			i++;
		}
		j++;
	}
	sortenv_utils(s, 0, 0);
}
