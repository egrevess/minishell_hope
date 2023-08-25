/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorburton <victorburton@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:05:38 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/08/25 16:28:28 by victorburto      ###   ########.fr       */
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
