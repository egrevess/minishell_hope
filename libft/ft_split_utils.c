/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:44:29 by viburton          #+#    #+#             */
/*   Updated: 2023/09/04 12:08:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	check_str_utils1(char const *s, size_t i, int *two, int *quotes)
{
	if (s[0] == '\'' && i == 1)
	{
		*two = 1;
		*quotes = 1;
	}
	else if (s[0] == '\"' && i == 1)
	{
		*two = 2;
		*quotes = 1;
	}
}

static void	check_str_utils2b(char const *s, size_t i, int *two, int *quotes)
{
	if (s[i] == '\"')
	{
		if (*two == 0 || *two == 2)
		{
			if (*quotes == 0)
			{
				*quotes = 1;
				*two = 2;
			}
			else if (*quotes == 1)
			{
				*quotes = 0;
				*two = 0;
			}
		}
	}
}

static void	check_str_utils2(char const *s, size_t i, int *two, int *quotes)
{
	if (s[i] == '\'')
	{
		if (*two == 0 || *two == 1)
		{
			if (*quotes == 0)
			{
				*quotes = 1;
				*two = 1;
			}
			else if (*quotes == 1)
			{
				*quotes = 0;
				*two = 0;
			}
		}
	}
	check_str_utils2b(s, i, two, quotes);
}

size_t	check_str(char const *s, char c)
{
	size_t	i;
	size_t	n;
	int		quotes;
	int		two;

	i = 1;
	n = 0;
	quotes = 0;
	two = 0; 
	if (!(s[0]))
		return (0);
	if (s[0] != c)
		n++;
	while (s[i])
	{
		check_str_utils1(s, i, &two, &quotes);
		if (s[i] != c && s[i - 1] == c && quotes == 0 && two == 0)
			n++;
		check_str_utils2(s, i, &two, &quotes);
		i++;
	}
	return (n);
}
