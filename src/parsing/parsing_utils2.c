/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:19:02 by viburton          #+#    #+#             */
/*   Updated: 2023/09/21 11:04:58 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	check_only_quo_utils(char c)
{
	char	d;

	if (c == '\'')
		d = '\"';
	else
		d = '\'';
	return (d);
}

static int	check_only_quo_utils2(char c, char d, int *one)
{
	if (c == d)
	{
		if (*one == 0 || (*one % 2 == 0 && *one != 1))
			*one = 0;
		else
			return (1);
	}
	return (0);
}

int	check_only_quo(char *str, char c, int i, int one)
{
	char	d;
	int		two;

	two = 0;
	d = check_only_quo_utils(c);
	if (((int) ft_strlen(str)) == 1) // rajouter le if
		return (1);
	while (str[++i]) // changer le i
	{
		if (str[i] != c && str[i] != d)
			return (1);
		if (str[i] == c)
		{
			if (two == 0 || (two % 2 == 0 && two > 1))
				two = 0;
			else
				return (1);
			one++;
		}
		if (str[i] == d && check_only_quo_utils2(str[i], d, &one) == 1)
			return (1);
		else
			two++;
	}
	return (0);
}
