/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:30:14 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/15 10:06:31 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_find_equa(char *par)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (par[i])
	{
		if (par[i] == '=')
			result++;
		i++;
	}
	return (result);
}

int	ft_check_export(char *par, t_struc *s)
{
	int	i;
	int	result;

	i = 0;
	s->checker_export = 0;
	while (par[i] && s->checker_export == 0)
	{
		if ((par[i] <= '9' && par[i] >= '0' && i !=0)
			|| (par[i] <= 'z' && par[i] >= 'a')
			|| (par[i] <= 'Z' && par[i] >= 'A')
			|| par[i] == '_')
			result = 0;
		else if (i != 0 && par[i] == '+' && par[i + 1] && par[i + 1] == '=')
			s->checker_export = 1;
		else if (par[i] == '=' && i != 0)
			break ;
		else
		{
			result = -1;
			break ;
		}
		i++;
	}
	return (result);
}

char	**ft_arrayjoin_env(t_struc *s, int index)
{
	char	**temp;
	int		i;

	s->lenght_env++;
	if (!s->pars[index] || !s->env)
		exit(EXIT_FAILURE);//pas sure que ce soit la bonne manière de protéger 
	temp = malloc(sizeof(*temp) * ((int) s->lenght_env + 1));
	if (!temp)
		exit(EXIT_FAILURE);
	i = 0;
	while (s->env[i])
	{
		temp[i] = ft_strdup(s->env[i]);
		i++;
	}
	ft_free_array(s->env, ft_len_tab(s->env) - 1);
	temp[i] = ft_strdup(s->pars[index]);
	temp[i + 1] = NULL;
	return (temp);
}

void	ft_export(t_struc *s)
{
	int	result;
	int	i;
	int	index;
	int	ok;

	index = 1;
	ok = 0;
	while (s->pars[index])
	{
		result = ft_check_export(s->pars[index], s);
		if (result == 0)
		{
			if (ft_find_equa(s->pars[index]) != 0)
			{
				if (ft_find_in_env_export(s, index) != -1)
					s->env = ft_arrayjoin_env(s, index);
			}
		}
		else if (result == -1 && ok == 0)
		{
			printf("minishell: export: `");//sortie d'erreur 
			i = 0;
			while (s->pars[index][i])
			{
				printf("%c", s->pars[index][i]);
				i++;
			}
			printf("': not a valid identifer\n");
			ok = 1;
		}
		index++;
	}
}
