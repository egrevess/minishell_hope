/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:00:01 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/05/15 10:06:23 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

int	ft_atoi_em(const char *str, int *check)
{
	long int	i;
	long		nb;
	long int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1 * neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = str[i] + (nb * 10) - 48;
		i++;
	}
	if (str[i] || i == 0)
		(*check) = 1;
	return (nb * neg);
}

void	ft_exit_par(t_struc *s)
{
	int	check;
	int	exit_value;

	check = 0;
	ft_atoi_em(s->pars[1], &check);
	if (s->size_pars > 2 && check == 0)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_output = 1;
		return ;
	}
	else if (s->size_pars >= 2)
	{
		exit_value = ft_atoi_em(s->pars[1], &check);
		if (check == 1)
		{
			printf("exit\nminishell: exit: ");
			printf("%s: numeric argument required\n", s->pars[1]);
			g_output = 255;
			exit (255);
		}
		else if(check == 0)
		{
			g_output = exit_value;
			printf("exit\n");
			if (exit_value >= 255)
				exit(exit_value - ((exit_value % 256) * 256));
			else if (exit_value <= 255)
				exit (exit_value + ((exit_value % 256) * 256));
		}
	}
	exit(EXIT_SUCCESS);
}