/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:47:53 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/26 15:06:19 by viburton         ###   ########.fr       */
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

static void	check_dbqu_utils(t_struc *s, int index, int i, char ***par)
{
	int		reps;
	int		check;

	check = 0;
	reps = 0;
	(void) par;
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
		*par = ft_split(s->pars[index], '\"');
}

void	check_double_quotes(t_struc *s, int index)
{
	int		i;
	char	**par;

	i = 0;
	par = NULL;
	check_dbqu_utils(s, index, i, &par);
	if (!par)
		return ;
	if (ft_len_tab(par) == 1)
	{
		free(s->pars[index]);
		s->pars[index] = ft_strdup(par[0]);
		ft_free_array(par, ft_len_tab(par) - 1);
	}
}

static int	check_quotes(char *par, int *pass)
{
	int	i;

	i = 1;
	if (par[0] != '$')
		return (-1);
	while (par[i] && par[i] != '\'' && par[i] != '\"')
		i++;
	if (i >= 1)
	{
		*pass = i;
	}
	return (*pass);
}

void	ft_sub_dollar(t_struc *s)
{
	int		index;
	int		pass;
	char	*temp;

	index = 0;
	pass = -1;
	while (s->pars[index])
	{
		check_double_quotes(s, index);
		temp = ft_strdup(s->pars[index]);
		if (s->pars[index][0] == '$' && (int) ft_strlen(s->pars[index]) > 1 &&
			ft_strncmp(s->pars[index], "$?", 2) != 0)
		{
			pass = ft_find_in_env_dollar(s, index);
			free(s->pars[index]);
			if (pass != -1)
				s->pars[index] = ft_find_in_env(s, pass);
			else if (check_quotes(temp, &pass) != -1)
				s->pars[index] = ft_substr(temp, pass, (int) ft_strlen(temp));
			else
				s->pars[index] = NULL;
		}
		index++;
		free (temp);
	}
}
