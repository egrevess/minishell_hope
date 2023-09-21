/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:29:18 by viburton          #+#    #+#             */
/*   Updated: 2023/09/21 18:22:11 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef struct s_data
{
	int	end;
	int	start;
	int	quotes;
	int	two;
}	t_data;

static char	**ft_free(char **spl, size_t i)
{
	while (i > 0)
	{
		free(spl[i]);
		i--;
	}
	free(spl[0]);
	free(spl);
	return (NULL);
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

void	ft_create_str_1(t_data *d, char const *s)
{
	d->quotes = 0;
	d->two = 0;
	if (s[d->start + d->end] == '\'')
	{
		d->end++;
		d->two = 1;
		while (s[d->start + d->end] && s[d->start + d->end] != '\'')
			d->end++;
		d->quotes = d->end;
	}
	else if (s[d->start + d->end] == '\"' && d->two != 1)
	{
		d->end++;
		d->two = 2;
		while (s[d->start + d->end] && s[d->start + d->end] != '\"')
			d->end++;
		d->quotes = d->end;
	}
	d->end++;
}

char	**ft_create_str(char **spl, char const *s, char c, int i)
{
	t_data	d;

	d.start = 0;
	while (s[d.start])
	{
		d.end = 0;
		while (s[d.start + d.end] && s[d.start + d.end] != c)
			ft_create_str_1(&d, s);
		if (d.end > 0)
		{
			spl[i] = ft_strndup(s + d.start, d.end);
			if (!spl[i])
				return (ft_free(spl, i));
			i++;
			if (d.end == d.quotes + 1 || d.quotes == -1)
				d.end--;
			d.start = d.start + d.end;
		}
		if (s[d.start])
			d.start++;
	}
	spl[i] = NULL;
	return (spl);
}
