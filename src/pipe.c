/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:33:09 by viburton          #+#    #+#             */
/*   Updated: 2023/09/21 18:35:52 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	pipes(t_struc *s, int num_commands)
{
	char	**commands;
	int		i;
	pid_t	wpid;
	int		status;

	i = 0;
	commands = malloc (sizeof (char *) * num_commands);
	if (!commands)
		exit(EXIT_FAILURE);
	pipe_util(s, commands, i, num_commands);
	wpid = wait(&status);
	while (wpid > 0)
		wpid = wait(&status);
	ft_free_array(commands, num_commands - 1);
	ft_free_array(s->pars, ft_len_tab(s->pars) - 1);
}
