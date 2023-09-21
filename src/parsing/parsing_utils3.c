/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:05:34 by viburton          #+#    #+#             */
/*   Updated: 2023/09/21 11:01:36 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_check_other_utils2(char c_s, char d, int *two, int *quotes)
{
	if (c_s == d && (*two == 2 || *two == 0))
	{
		if (*quotes == 0)
		{
			*two = 2;
			*quotes = 1;
		}
		else if (*quotes == 1)
		{
			*two = 0;
			*quotes = 0;
		}
	}
}

static void	ft_check_other_utils(char c_s, char c, int *two, int *quotes)
{
	if (c_s == c && (*two == 1 || *two == 0))
	{
		if (*quotes == 0)
		{
			*two = 1;
			*quotes = 1;
		}
		else if (*quotes == 1)
		{
			*two = 0;
			*quotes = 0;
		}
	}
	ft_check_other_utils2(c_s, '\"', two, quotes);
}

int	ft_check_other(const char *s, char c)
{
	int	i;
	int	quotes;
	int	two;

	i = 0;
	two = 0;
	quotes = 0;
	while (s[i])
	{
		ft_check_other_utils(s[i], c, &two, &quotes);
		i++;
	}
	if (two != 0)
		return (1);
	else
		return (0);
}
