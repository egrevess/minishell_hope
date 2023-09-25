/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:49:41 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/25 13:15:58 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_dollar(t_struc *s)
{
	if (s->sizefirst_pars > 2)
	{
		printf("minishell: %d%s: command not found\n", g_output,
			ft_substr(s->pars[0], 2, s->sizefirst_pars));
	}
	else
		printf("minishell: %d: command not found\n", g_output);
	g_output = 127;
}
