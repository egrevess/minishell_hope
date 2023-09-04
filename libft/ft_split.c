/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:49:20 by viburton          #+#    #+#             */
/*   Updated: 2023/09/04 13:32:15 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_split(char const *s, char c)
{
	char	**spl;
	size_t	size;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	size = check_str(s, c);
	spl = (char **)malloc(sizeof(spl) * (size + 1));
	if (!spl)
		return (NULL);
	spl = ft_create_str(spl, s, c, i);
	return (spl);
}
