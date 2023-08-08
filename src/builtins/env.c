/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:33:19 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/15 10:06:20 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_printf_env(t_struc *s)
{
	int	i;

	i = 0;
	if (!s->env)
	{
		g_output = 1;
		return ;
	}
	while (s->env[i])
	{
		printf("%s\n", s->env[i]);
		i++;
	}
	g_output = 0;
}

int	ft_init_env(t_struc *s, char **env)
{
	int i;

	i = 0;
	s->env = malloc (sizeof(*s->env) * (240));
	if (!s->env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		s->env[i] = ft_strdup(env[i]);
		i++;
	}
	s->env[i] = NULL;
	s->lenght_env = i;
	return (1);
}

int	ft_in_env(t_struc *s, char *var)
{
	int	i;
	int check;
	int size;

	i = 0;
	check = -1;
	size = (int) ft_strlen(var);
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], var , (size_t) (size - 1)) == 0
			&& (size) == (int) (ft_strrchr((const char*) s->env[i], '=') - s->env[i]))
		{
			check = i;
			break;
		}
		i++;
	}
	return (check);
}
