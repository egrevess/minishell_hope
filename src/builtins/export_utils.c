/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:31:33 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/15 10:06:27 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_change_pars_export(t_struc *s, int index)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s->pars[index])));
	if (!str)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (s->pars[index][j])
	{
		if (s->pars[index][j] != '+')
		{
			str[i] = s->pars[index][j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	free(s->pars[index]);
	return (str);
}

char	*ft_copy_pars_after_equal(t_struc *s, int index)
{
	char	*str;
	int		i;
	int		j;
	int		size;
	int		check;

	size = 0;
	check = 0;
	i = 0;
	j = 0;
	while (s->pars[index][j])
	{
		if (s->pars[index][j] == '=')
			check = 1;
		else if (check == 1)
			size++;
		j++;
	}
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (!str)
		exit(EXIT_FAILURE);
	while (s->pars[index][j - size + i])
	{
		str[i] = s->pars[index][j - size + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_find_in_env_export(t_struc *s, int index)
{
	int		i;
	int		j;
	int		size;
	char	*temp_pars;
	char	*temp_env;

	i = 0;
	j = 0;
	if (s->checker_export == 1)
	{
		s->pars[index] = ft_change_pars_export(s, index);
		temp_pars = ft_copy_pars_after_equal(s,index);
	}
	size = ft_strrchr((const char*) s->pars[index], '=') - s->pars[index];
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], s->pars[index] , (size_t) size) == 0)
		{
			j = -1;
			break;
		}
		i++;
	}
	if (j == -1)
	{
		size = (int) ft_strlen(s->env[i]);
		temp_env = ft_strdup(s->env[i]);
		free(s->env[i]);
		if (s->checker_export != 1)
			s->env[i] = ft_strdup(s->pars[index]);
		else 
		{
			s->env[i] = ft_strjoin(temp_env, temp_pars);
			free(temp_env);
			free(temp_pars);
		}
	}
	return (j);
}