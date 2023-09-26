/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:23:54 by viburton          #+#    #+#             */
/*   Updated: 2023/09/26 17:33:39 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_expr(t_struc *s)
{
	if (ft_len_tab(s->pars) == 4
		&& ft_strncmp(s->pars[1], "$?", 2) == 0 && ft_strlen(s->pars[1]) == 2
		&& ft_strncmp(s->pars[3], "$?", 2) == 0 && ft_strlen(s->pars[3]) == 2
		&& ft_strncmp(s->pars[2], "+", 1) == 0 && ft_strlen(s->pars[2]) == 1)
	{
		printf("%i\n", g_output * 2);
		return (0);
	}
	else
	{
		g_output = ft_execve(s, 0, 0, NULL);
		free_path(s);
		return (g_output);
	}
}

void	free_path(t_struc *s)
{
	if (s->path)
		ft_free_array(s->path, ft_len_tab(s->path) - 1);
}

void	handle_pwd(t_struc *s)
{
	if (s->pwd)
	{
		g_output = 0;
		printf("%s\n", s->pwd);
	}
	else
		g_output = 1;
}
