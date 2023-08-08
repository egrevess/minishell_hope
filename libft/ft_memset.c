/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:29:57 by viburton          #+#    #+#             */
/*   Updated: 2022/10/05 15:30:09 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)b;
	while (i < len)
	{
		*(char *)s1 = (unsigned char)c;
		s1++;
		i++;
	}
	return (b);
}
