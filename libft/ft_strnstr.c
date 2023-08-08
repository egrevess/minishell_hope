/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:52:05 by viburton          #+#    #+#             */
/*   Updated: 2022/10/05 15:52:07 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;

	if (!haystack && !len)
		return (0);
	if (*needle == '\0')
		return ((char *)haystack);
	size = ft_strlen(needle);
	while (*haystack != '\0' && len >= size)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, size) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
