/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:42 by viburton          #+#    #+#             */
/*   Updated: 2022/10/05 15:47:46 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!(dst) && !(src))
		return (NULL);
	i = 0;
	if ((unsigned char *)dst < (const unsigned char *)src)
	{
		while (len--)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
		while (len--)
			((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
	return (dst);
}
