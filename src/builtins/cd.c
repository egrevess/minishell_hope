/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:56:20 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/21 18:12:41 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	send_path(char *path, t_struc *s)
{
	char	*temp;

	if (s->pwd)
		free(s->pwd);
	temp = ft_find_pdw(s);
	if (path[0] == '~')
		path = getenv("HOME");
	if (path != NULL && temp != NULL)
	{
		if (chdir(path) == 0)
		{
			change_value_env(s, temp);
			g_output = 0;
		}
		else
		{
			printf("minishell: cd: %s: No such file or directory\n", s->pars[1]);
			g_output = 1;
		}
	}
	else
		exit(EXIT_FAILURE);
}

char	**ft_arrayjoin_oldpwd(t_struc *s, char *oldpwd)
{
	char	**temp;
	int		i;

	s->lenght_env++;
	if (!oldpwd || !s->env)
		exit (EXIT_FAILURE);
	temp = malloc(sizeof(*temp) * ((int) s->lenght_env + 1));
	if (!temp)
		exit (EXIT_FAILURE);
	i = 0;
	while (s->env[i])
	{
		temp[i] = ft_strdup(s->env[i]);
		i++;
	}
	temp[i] = ft_strdup(oldpwd);
	temp[i + 1] = NULL;
	ft_free_array(s->env, ft_len_tab(s->env) - 1);
	return (temp);
}

void	change_value_env(t_struc *s, char *temp)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], "PWD", (size_t) 3) == 0)
		{
			free(s->env[i]);
			s->env[i] = ft_strjoin("PWD=", ft_find_pdw(s));
		}
		else if (ft_strncmp(s->env[i], "OLDPWD", (size_t) 6) == 0)
		{
			free(s->env[i]);
			s->env[i] = ft_strjoin("OLDPWD=", temp);
			check = 1;
		}
		i++;
	}
	if (check == 0)
		s->env = ft_arrayjoin_oldpwd(s, ft_strjoin("OLDPWD=", temp));
	free (temp);
}

void	ft_cd(t_struc *s)
{
	int	i;

	i = -1;
	if (s->size_pars == 1)
	{
		i = ft_in_env(s, "HOME");
		if (i != -1)
			send_path(ft_find_in_env(s, i), s);
	}
	else if (s->size_pars == 2)
		send_path(s->pars[1], s);
}
