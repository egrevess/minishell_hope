/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:12:05 by viburton          #+#    #+#             */
/*   Updated: 2023/10/09 15:55:29 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	**ft_array_del(t_struc *s)
{
	char	**temp;
	int		i;
	int		index;

	temp = malloc(sizeof(*temp) * ((int) ft_len_tab(s->pars) - 1));
	if (!temp)
		exit (EXIT_FAILURE);
	i = 0;
	index = 0;
	while (s->pars[i + 2])
	{
		if (s->pars[i][0] == '<' && s->pars[i][1] == '<')
			i = i + 2;
		temp[index] = ft_strdup(s->pars[i]);
		index++;
		i++;
	}
	temp[index] = NULL;
	ft_free_array(s->pars, ft_len_tab(s->pars) - 1);
	return (temp);
}

static char	*ft_strjoin_her(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

static void	execute_with_heredoc(t_struc *s, char *delimiter)
{
	int		i;
	char	*tmp2;

	tmp2 = readline("> ");
	(void) i;
	while (ft_strncmp(delimiter, tmp2, ft_strlen(delimiter)) != 0)
	{
			s->heredoc_content = ft_strjoin_her(s->heredoc_content, tmp2);
			s->heredoc_content = ft_strjoin_her(s->heredoc_content, "\n");
			free(tmp2);
			tmp2 = readline("> ");
	}
	s->pars = ft_array_del(s);
	ft_execve(s, 0, 0, NULL);
	if (s->path)
		ft_free_array(s->path, ft_len_tab(s->path) - 1);
	free(tmp2);
 	if (s->heredoc_content != NULL)
 		free(s->heredoc_content);
	ft_free_array(s->pars, ft_len_tab(s->pars) - 1);
	if (delimiter)
		free(delimiter);
}

void	heredoc_handle(t_struc *s, char *delimiter)
{
	char	**tmp;
	int		i = 0;

	tmp = ft_split(delimiter, ' ');
	i = 0;
	s->heredoc_content = NULL;
	free(delimiter);
	delimiter = ft_strdup(tmp[0]);
	/*
	while (tmp[i])
	{
		if (i == 0)
			delimiter = tmp[0];
		else
		{
			if (i == 1)
				s->heredoc_content = tmp[i];
			else
			{
				s->heredoc_content = ft_strjoin_her(s->heredoc_content, " ");
				s->heredoc_content = ft_strjoin_her(s->heredoc_content, tmp[i]);
			}
		}
		i++;
	}*/
	execute_with_heredoc(s, delimiter);
	if (tmp != NULL)
		ft_free_array(tmp, ft_len_tab(tmp) - 1);
}
