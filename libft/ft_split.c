/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:49:20 by viburton          #+#    #+#             */
/*   Updated: 2023/05/16 12:01:00 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	check_str(char const *s, char c)
{
	size_t	i;
	size_t	n;
	int		quotes;
	int 	two;

	i = 1;
	n = 0;
	quotes = 0;
	two = 0; 
	if (!(s[0]))
		return (0);
	if (s[0] != c )
		n++;
	while (s[i])
	{
		if (s[0] == '\'' && i == 1)
		{
			two = 1;
			quotes = 1;
		}
		else if (s[0] == '\"' && i == 1)
		{
			two = 2;
			quotes = 1;
		}
		//printf ("quotes = %d\n", quotes);
		//printf ("two = %d\n", two);
		//printf("s[i] = %c\n ", s[i]);
		if (s[i] != c && s[i - 1] == c
				&& quotes == 0 && two == 0)
		{
			n++;
			//printf("s[i] = %c\n ", s[i]);
		}
		if (s[i] == '\'' && (two == 0 || two == 1))
		{
			if (quotes == 0)
			{
				quotes = 1;
				two = 1;
			}
			else if (quotes == 1)
			{
				quotes = 0;
				two = 0;
			}
		}
		else if (s[i] == '\"' && (two == 0 || two == 2))
		{
			if (quotes == 0)
			{
				quotes = 1;
				two = 2;
			}
			else if (quotes == 1)
			{
				quotes = 0;
				two = 0;
			}
		}
		i++;
	}
	//printf("%zu\n", n);
	return (n);
}

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

static char	**ft_create_str(char **spl, char const *s, char c, int i)
{
	size_t	start;
	size_t	end;
	int		quotes;
	int		two;

	start = 0;
	while (s[start])
	{
		end = 0;
		while (s[start + end] && s[start + end] != c)
		{
			quotes = 0;
			two = 0;
			if (s[start + end] == '\'')
			{
				end++;
				two = 1;
				while (s[start + end] && s[start + end] != '\'')
					end++;
				quotes = end;
			}
			else if(s[start + end] == '\"' && two != 1)
			{
				end++;
				two = 2;
				while (s[start + end] && s[start + end] != '\"')
					end++;
				quotes = end;
			}
			end++;
		}
		if (end > 0)
		{
			spl[i] = ft_strndup(s + start, end);
			if (!spl[i])
			{
				ft_free(spl, i);
				return (NULL);
			}
			i++;
			if ((int) end == quotes + 1 || quotes == -1)
				end--;
			start = start + end;
		}
		if (s[start])
			start++;
	}
	spl[i] = NULL;
	return (spl);
}

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
