/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:49:41 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/04 13:36:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_dollar(t_struc *s)
{
	(void) s;
	printf("minishell: %d: command not found\n", g_output);
	g_output = 127;
}
