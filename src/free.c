/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:05:38 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/19 16:35:54 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_free_array(char **tab, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
void	ft_free(t_struc *s, t_pipe *p)
{
	int	i;

	(void) p;
	i = 0;
	
	if (s->str)
		free(s->str);
	if (s->pars)
	{
		while (s->pars[i])
		{
			free(s->pars[i]);
			i++;
		}
		free (s->pars);
	}
	if (s->pwd)
		free (s->pwd);
}
