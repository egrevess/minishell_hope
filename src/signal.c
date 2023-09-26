/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:44:22 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/26 12:00:41 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	execut(int sig)
{
	(void) sig;
	g_output = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	execut1(int sig)
{
	(void) sig;
	printf("\n");
}

void	execut2(int sig)
{
	(void) sig;
	printf("Quit: 3\n");
}
