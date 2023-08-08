/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:50:50 by viburton          #+#    #+#             */
/*   Updated: 2022/10/05 15:50:53 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dsize;
	size_t	i;

	dsize = 0;
	i = 0;
	if (!dst && !dstsize)
		return (0);
	while (dst[dsize] && dsize < dstsize)
		dsize++;
	while (src[i] && dsize + i + 1 < dstsize)
	{
		dst[dsize + i] = src[i];
		i++;
	}
	if (dsize != dstsize)
		dst[dsize + i] = '\0';
	return ((size_t)ft_strlen(src) + dsize);
}
