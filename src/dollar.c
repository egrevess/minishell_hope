/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:49:41 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/03/16 16:35:12 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_dollar(t_struc *s)
{
	(void) s;
	//manque une protection
	printf("minishell: %d: command not found\n", g_output);
	g_output = 127;
}
