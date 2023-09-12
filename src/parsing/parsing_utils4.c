/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:15:45 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 11:50:41 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*ft_del_quotes_utils(char *s, char c, char *temp, int *i)
{
	*i += 1;
	while (s[*i] != c)
	{
		if (temp == NULL)
			temp = ft_substr(s, *i, 1);
		else
			temp = ft_strjoin(temp, ft_substr(s, *i, 1));
		*i += 1;
	}
	*i += 1;
	return (temp);
}

static char	*ft_del_quotes_utils2(char *s, char d, char *temp, int *i)
{
	*i += 1;
	while (s[*i] != d)
	{
		if (temp == NULL)
			temp = ft_substr(s, *i, *i);
		else
			temp = ft_strjoin(temp, ft_substr(s, *i, 1));
		*i += 1;
	}
	*i += 1;
	return (temp);
}

static char	*ft_del_quotes_utils3(char *s, char *temp, int *i)
{
	if (temp == NULL)
		temp = ft_substr(s, *i, 1);
	else
		temp = ft_strjoin(temp, ft_substr(s, *i, 1));
	*i += 1;
	return (temp);
}

char	*ft_del_quotes(char	*s, char c, char d)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == c)
			temp = ft_del_quotes_utils(s, c, temp, &i);
		else if (s[i] == d)
			temp = ft_del_quotes_utils2(s, d, temp, &i);
		else
			temp = ft_del_quotes_utils3(s, temp, &i);
	}
	return (temp);
}
