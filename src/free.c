/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:05:38 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/03/14 13:29:03 by emmagrevess      ###   ########.fr       */
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