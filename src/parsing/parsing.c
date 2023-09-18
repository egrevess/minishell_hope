/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:29:54 by viburton          #+#    #+#             */
/*   Updated: 2023/09/18 11:25:44 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	**ft_parse(char *str, t_struc *s)
{
	int		i;
	char	*delimiter;

	i = 0;
	delimiter = NULL;
	s->heredoc_content = "\0";
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[i + 2] == ' ')
				delimiter = ft_substr(str, i + 3, ft_strlen(str));
			else
				delimiter = ft_substr(str, i + 2, ft_strlen(str));
			break ;
		}
		i++;
	}
	if (delimiter)
	{
		s->pars = ft_split(str, ' ');
	}
	return (ft_split(str, ' '));
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
			&& check_only_quo(s->pars[i], s->pars[i][0], 0, 0) == 0)
		{
			if (!s->pars[i + 1])
				s->echo_quotes = 1;
			s->pars = ft_array_del(s->pars, i);
			i--;
		}
		else if (ft_check_other(s->pars[i], '\'') == 1)
		{
			printf("Error: syntax error near unexpected token\n");
			return (NULL);
		}
		else if (ft_check_quotes(s->pars[i]) == 1)
			s->pars[i] = ft_del_quotes(s->pars[i], '\'', '\"');
		i++;
	}
	return (s->pars);
}
