/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:29:54 by viburton          #+#    #+#             */
/*   Updated: 2023/10/09 17:41:18 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_parse(char *str, t_struc *s, t_pipe *p)
{
	int		i;
	char	*delimiter;

	i = 0;
	delimiter = NULL;
	s->heredoc_content = "\0";
	while (str[i] && str[i] != '\"' && str[i] != '\'')
	{
		if (str[i] == '<')
			return (heredocs(i, delimiter, str, s));
		else if (str[i] == '>')
			return (redirection(i, str, s));
		i++;
	}
	s->pars = ft_split(str, ' ');
	s->pars = ft_pipe(s, p);
	return (0);
}

static char	**ft_array_del(char **s, int find)
{
	char	**temp;
	int		i;
	int		index;
	int		size;

	size = ft_len_tab(s) - 1;
	temp = malloc(sizeof(*temp) * (size + 1));
	if (!temp)
		exit (EXIT_FAILURE);
	i = 0;
	index = 0;
	while (s[i])
	{
		if (i != find)
		{
			temp[index] = ft_strdup(s[i]);
			index++;
		}
		i++;
	}
	temp[index] = NULL;
	index = 0;
	ft_free_array(s, ft_len_tab(s) - 1);
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

static int	ft_check_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_parse_quotes(t_struc *s)
{
	int	i;

	i = 0;
	s->echo_quotes = 0;
	while (s->pars[i])
	{
		if ((s->pars[i][0] == '\'' || s->pars[i][0] == '\"')
				&& check_only_quo(s->pars[i], s->pars[i][0], -1, 0) == 0)
		{
			if (!s->pars[i + 1])
				s->echo_quotes = 1;
			s->pars = ft_array_del(s->pars, i);
			i--;
		}
		else if (ft_check_other(s->pars[i], '\'') == 1)
		{
			ft_free_array(s->pars, ft_len_tab(s->pars) - 1);
			printf("Error: syntax error near unexpected token\n");
			return (NULL);
		}
		else if (ft_check_quotes(s->pars[i]) == 1)
			s->pars[i] = ft_del_quotes(s->pars[i], '\'', '\"');
		i++;
	}
	return (s->pars);
}
