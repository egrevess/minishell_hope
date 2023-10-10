/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:15 by viburton          #+#    #+#             */
/*   Updated: 2023/10/10 11:22:03 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	print_er(void)
{
	printf("minishell: error near unexpected token \'newline\'\n");
	return (4);
}

static int	check_after(char *s, int i)
{
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	redir_in(char *filename, char *str, t_struc *s)
{
	free(filename);
	(void) str;
	(void) s;
	printf("\n");
	return (4);
}

int	heredocs(int i, char *delimiter, char *str, t_struc *s)
{
	if (str[i + 1] == '<' && str[i + 2])
	{
		if (check_after(str, i + 2) == 1)
			return (print_er());
		if (str[i + 2] == ' ')
			delimiter = ft_substr(str, i + 3, ft_strlen(str));
		else
			delimiter = ft_substr(str, i + 2, ft_strlen(str));
	}
	else
	{
		if (check_after(str, i + 1) == 1)
			return (print_er());
		if (str[i + 1] == ' ')
			redir_in(ft_substr(str, i + 2, ft_strlen(str)), str, s);
		else
			redir_in(ft_substr(str, i + 1, ft_strlen(str)), str, s);
		return (4);
	}
	if (delimiter)
	{
		s->pars = ft_split(str, ' ');
		heredoc_handle(s, delimiter);
	}
	return (4);
}
