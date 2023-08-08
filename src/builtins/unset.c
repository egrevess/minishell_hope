/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:18:14 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/15 10:06:36 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	**ft_array_delete(t_struc *s, int find)
{
	char	**temp;
	int		i;
	int		index;

	s->lenght_env--;
	temp = malloc(sizeof(*temp) * ((int) s->lenght_env + 1));
	if (!temp)
		exit (EXIT_FAILURE);
	i = 0;
	index = 0;
	while (s->env[i])
	{
		if (i != find)
		{
			temp[index] = ft_strdup(s->env[i]);
			index++;
		}
		i++;
	}
	temp[index] = NULL;
	ft_free_array(s->env, ft_len_tab(s->env) - 1);
	return (temp);
}

int	ft_find_in_env_unset(t_struc *s, int index)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = (int) ft_strlen(s->pars[index]);
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], s->pars[index], (size_t) size) == 0
			&& (size == ((int) (ft_strrchr((const char*) s->env[i], '=') - s->env[i]))))
		{
			j = -1;
			break ;
		}
		i++;
	}
	if (j == -1)
		s->env = ft_array_delete(s, i);
	return (j);
}

int	ft_check_unset(char *par)
{
	int	i;
	int	result;

	i = 0;
	while (par[i])
	{
		if ((par[i] <= '9' && par[i] >= '0')
			|| (par[i] <= 'z' && par[i] >= 'a')
			|| (par[i] <= 'Z' && par[i] >= 'A')
			|| par[i] == '_')
			result = 0;
		else
		{
			result = -1;
			break ;
		}
		i++;
	}
	return (result);
}

int	ft_unset(t_struc *s)
{
	int	index;
	int	result;
	int	ok;

	index = 1;
	ok = 0;
	while (s->pars[index])
	{
		result = ft_check_unset(s->pars[index]);
		if (result == 0)
			ft_find_in_env_unset(s, index);
		else if (result == -1 && ok == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", s->pars[index]);
			ok = 1;
		}
		index++;
	}
	return (ok);
}
