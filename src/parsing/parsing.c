/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:29:54 by viburton          #+#    #+#             */
/*   Updated: 2023/06/22 16:25:08 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

#include <stdio.h>		// A retirer !!!

char    **ft_parse(char *str)
{
	char **line;
	int i =0;
		
	line = ft_split(str, ' ');
	while (line[i])
	{
		printf("%s\n", line[i]);
		i++;
	}
	return (ft_split(str, ' '));
}

static char	**ft_array_del(char **s, int find)
{
	char	**temp;
	int		i;
	int		index;
	int		size;

	size = ft_len_tab(s) - 1;
	//printf("size = %d\n", size);
	temp = malloc(sizeof(*temp) * (size + 1));
	if (!temp)
		exit (EXIT_FAILURE);
	i = 0;
	index = 0;
	while (s[i])
	{
		if (i != find)
		{
			temp[index] = ft_strdup(s[i]);
			index++;
		}
		i++;
	}
	temp[index] = NULL;
	index = 0;
	ft_free_array(s, ft_len_tab(s) - 1);
	return (temp);
}

static int	check_only_quo(char *str, char c)
{
	int		i;	
	char	d;
	int		two;
	int		one;
	
	i = 0;
	two = 0;
	one = 0;
	if (c == '\'')
		d = '\"';
	else
		d = '\'';
	while (str[i])
	{
		if (str[i] != c && str[i] != d)
			return (1);
		if (str[i] == c)
		{
			if (two == 0 || (two % 2 == 0 && two > 1))
				two = 0;
			else 
				return (1);
			one++;
		}
		else if (str[i] == d)
		{
			if (one == 0 || (one % 2 == 0 && one != 1))
				one = 0;
			else 
				return (1);
			two++;
		}
		i++;
	}
	return (0);
}

static	int	ft_check_other(const char *s, char c, char d)
{
	int	i;
	int	quotes;
	int	two;

	i = 0;
	two = 0;
	quotes = 0;
	while (s[i])
	{
		if (s[i] == c && (two == 1 || two == 0))
		{
			if (quotes == 0)
			{
				two = 1;
				quotes = 1;
			}
			else if (quotes == 1)
			{
				two = 0;
				quotes = 0;
			}
		}
		else if (s[i] == d && (two == 2 || two == 0))
		{
			if (quotes == 0)
			{
				two = 2;
				quotes = 1;
			}
			else if (quotes == 1)
			{
				two = 0;
				quotes = 0;
			}
		}
		i++;
	}
	if (two != 0)
		return (1);
	else 
		return (0);
}

static int	ft_check_quotes(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static char *ft_del_quotes(char	*s, char c, char d)
{
	int	i;
	char *temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			//printf("%c\n", s[i]);
			while (s[i] != c)
			{
				//printf("c = %c\n", s[i]);
				if (temp == NULL)
				{
					//printf("before temp i = %d\n", i);
					temp = ft_substr(s , i, 1);
					//printf("after null %s\n", temp);
					//printf("after temp i = %d\n", i);
				}
				else
				{
					//printf("before temp i = %d\n", i);
					//printf("before temp %s\n", temp);
					temp = ft_strjoin(temp, ft_substr(s , i, 1));
					//printf("after temp %s\n", temp);
					//printf("after temp i = %d\n", i);
				}
				i++;
			}
			i++;

		}
		else if (s[i] == d)
		{
			i++;
			while (s[i] != d)
			{
				if (temp == NULL)
					temp = ft_substr(s , i, i);
				else 
					temp = ft_strjoin(temp, ft_substr(s , i, 1));
				i++;
			}
			i++;
		}
		else
		{
			if (temp == NULL)
				temp = ft_substr(s , i, 1);
			else 
				temp = ft_strjoin(temp, ft_substr(s , i, 1));
			i++;
		}
		//printf("%s\n", temp);
	}
	return (temp);
}
	
char	**ft_parse_quotes(t_struc *s)
{
	int	i;

	i = 0;
	s->echo_quotes = 0;
	//printf("-----------\n");
	while (s->pars[i])
	{
		//printf("s->pars[i]%s\n",s->pars[i]);
		if ((s->pars[i][0] == '\'' || s->pars[i][0] == '\"') && check_only_quo(s->pars[i], s->pars[i][0]) == 0)
		{
			//printf("s->pars[i]%s\n",s->pars[i]);
			if (!s->pars[i + 1])
				s->echo_quotes = 1;
			s->pars = ft_array_del(s->pars, i);
			i--;
		}
		else if (ft_check_other(s->pars[i], '\'', '\"') == 1)
		{
			printf("Error: syntax error near unexpected token\n");
			return (NULL);
		}
		else if (ft_check_quotes(s->pars[i]) == 1)
			s->pars[i] = ft_del_quotes(s->pars[i] , '\'', '\"');
		//printf("%s\n",s->pars[i]);
		i++;
	}
	return (s->pars);
}