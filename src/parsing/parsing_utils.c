/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:47:53 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/21 13:09:09 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_find_in_env(t_struc *s, int i)
{
	char	*temp;
	int		index;
	int		len;
	int		x;

	len = (int) ft_strlen(s->env[i]);
	index = (int)(ft_strrchr((const char *) s->env[i], '=') - s->env[i]) + 1;
	temp = malloc(sizeof(*temp) * (len - index + 1));
	if (!temp)
		exit(EXIT_FAILURE);
	x = 0;
	while (s->env[i][index + x])
	{
		temp[x] = s->env[i][index + x];
		x++;
	}
	temp[x] = '\0';
	return (temp);
}

int	ft_find_in_env_dollar(t_struc *s, int index)
{
	int		i;
	char	*par;
	int		check;

	check = -1;
	s->size_second_pars = (int) ft_strlen(s->pars[index]);
	par = malloc(sizeof(*par) * (s->size_second_pars));
	if (!par)
		exit (EXIT_FAILURE);
	par = ft_memcpy(par, &s->pars[index][1], (size_t)(s->size_second_pars - 1));
	i = 0;
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], par, (size_t)(s->size_second_pars - 1)) == 0
			&& (s->size_second_pars - 1) ==
			(int)(ft_strrchr((const char*) s->env[i], '=') - s->env[i]))
		{
			check = i;
			break ;
		}
		i++;
	}
	free (par);
	return (check);
}

static void	check_dbqu_utils(t_struc *s, int index, int i, char ***par)
{
	int		reps;
	int		check;

	check = 0;
	reps = 0;
	(void)	par;
	while (s->pars[index][i] == '\"' )
	{
		reps++;
		i++;
	}
	if (s->pars[index][i] != '$')
		return ;
	i++;
	while (s->pars[index][i] && s->pars[index][i] != '\"')
		i++;
	while (s->pars[index][i] && s->pars[index][i] == '\"')
	{
		check++;
		i++;
	}
	if (check == reps && i == (int)ft_strlen(s->pars[index]))
		par = ft_split(s->pars[index], '\"');
	else if (check != reps)
		printf("Error: syntax error near unexpected token\n");
}

void	check_double_quotes(t_struc *s, int index)
{
	int		i;
	char	**par;

	i = 0;
	par = NULL;
	check_dbqu_utils(s, index, i, par);
	if (!par)
		return ;
	if (ft_len_tab(par) == 1)
	{
		free(s->pars[index]);
		s->pars[index] = ft_strdup(par[0]);
		ft_free_array(par, ft_len_tab(par) - 1);
	}
}

void	ft_sub_dollar(t_struc *s)
{
	int	index;
	int	pass;

	index = 0;
	pass = -1;
	while (s->pars[index])
	{
		check_double_quotes(s, index);
		if (s->pars[index][0] == '$')
		{
			pass = ft_find_in_env_dollar(s, index);
			if (pass != -1)
			{
				free(s->pars[index]);
				s->pars[index] = ft_find_in_env(s, pass);
			}
		}
		index++;
	}
}
