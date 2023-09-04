/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:56:52 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/04 15:46:24 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_echo_option(char **par)
{
	int	check_nl;
	int	i;

	check_nl = 0;
	i = 1;
	while (par[i])
	{
		if (ft_strncmp(par[i], "-n", (size_t) 2) == 0
			&& (int) ft_strlen(par[i]) == 2)
			check_nl++;
		else
			break ;
		i++;
	}
	return (check_nl);
}

static void	ft_echo_utils(t_struc *s, int *i, int *index, int *check_nl)
{
	if (ft_strncmp(s->pars[*i], "-n", (size_t)2) == 0 && *i == 1)
	{
		*check_nl = ft_echo_option(s->pars);
		while (*check_nl > *index)
		{
			*index += 1;
			*i += 1;
		}
	}
}

void	ft_echo(t_struc *s)
{
	int	i;
	int	index;
	int	check_nl;

	i = 1;
	check_nl = 0;
	index = 0;
	while (s->pars[i])
	{
		ft_echo_utils(s, &i, &index, &check_nl);
		if (s->pars[i][0] == '$' && ft_find_in_env_dollar(s, index) == -1)
			printf("");
		if (ft_strncmp(s->pars[i], "$?", (size_t)2) == 0
			&& (int)ft_strlen(s->pars[i]) == 2)
			printf("%d", g_output);
		else if (s->pars[i])
			printf("%s", s->pars[i]);
		if (s->pars[i + 1] || s->echo_quotes == 1)
			printf(" ");
		i++;
	}
	if (check_nl == 0)
		printf("\n");
}
