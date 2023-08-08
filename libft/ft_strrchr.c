/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:52:20 by viburton          #+#    #+#             */
/*   Updated: 2023/02/16 14:07:03 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	position;

	i = 0;
	position = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			position = i;
		i++;
	}
	if (position > 0 || (unsigned char)s[0] == (unsigned char)c)
		return ((char *)&s[position]);
	if (s[i] == 0 && c == 0)
		return ((char *)&s[i]);
	return (NULL);
}
