/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:29:18 by viburton          #+#    #+#             */
/*   Updated: 2023/09/04 13:32:50 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_free(char **spl, size_t i)
{
	while (i > 0)
	{
		free(spl[i]);
		i--;
	}
	free(spl[0]);
	free(spl);
}

static char	*ft_strndup(char const *str, size_t size)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(sizeof(*dest) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	crt_strtls(const char *s, size_t *startend, int *quotes, int *two)
{
	if (s[startend[0] + startend[1]] == '\'')
	{
		startend[1] += 1;
		*two = 1;
		while (s[startend[0] + startend[1]]
			&& s[startend[0] + startend[1]] != '\'')
			startend[1] += 1;
		*quotes = startend[1];
	}
	else if (s[startend[0] + startend[1]] == '\"' && *two != 1)
	{
		startend[1] += 1;
		*two = 2;
		while (s[startend[0] + startend[1]]
			&& s[startend[0] + startend[1]] != '\"')
			startend[1] += 1;
		*quotes = startend[1];
	}
	startend[1] += 1;
}

static int	crate_strtls2(char **spl, size_t *startend, int *quotes, int *i)
{
	if (!spl[*i])
	{
		ft_free(spl, *i);
		return (0);
	}
	*i += 1;
	if ((int)startend[1] == *quotes + 1 || *quotes == -1)
		startend[1] -= 1;
	startend[0] = startend[0] + startend[1];
	return (1);
}

char	**ft_create_str(char **spl, const char *s, char c, int i)
{
	size_t		startend[2];
	int			quotes;
	int			two;

	startend[0] = 0;
	while (s[startend[0]])
	{
		startend[1] = 0;
		quotes = 0;
		two = 0;
		while (s[startend[0] + startend[1]]
			&& s[startend[0] + startend[1]] != c)
			crt_strtls(s, startend, &quotes, &two);
		if (startend[1] > 0)
		{
			spl[i] = ft_strndup(s + startend[0], startend[1]);
			if (!crate_strtls2(spl, startend, &quotes, &i))
				return (NULL);
		}
		if (s[startend[0]])
			startend[0]++;
	}
	spl[i] = NULL;
	return (spl);
}
