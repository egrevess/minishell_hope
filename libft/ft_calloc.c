/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:34:36 by viburton          #+#    #+#             */
/*   Updated: 2022/10/05 16:35:33 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	i;

	result = (void *)malloc(sizeof(void) * size * count);
	if (!result)
		return (NULL);
	if (size == 0)
		size = 1;
	i = count * size;
	if (i / size != count)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
