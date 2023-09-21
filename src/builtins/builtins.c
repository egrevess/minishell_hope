/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:47 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/09/21 18:16:59 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_find_pdw(t_struc *s)
{
	s->pwd = malloc(sizeof(*s->pwd) * 1024);
	if (!s->pwd)
		exit(EXIT_FAILURE);
	getcwd(s->pwd, 1024);
	return (s->pwd);
}

static void	handle_single_builtin(t_struc *s)
{
	s->sizefirst_pars = (int)ft_strlen(s->pars[0]);
	if (ft_strncmp(s->pars[0], "env", 3) == 0 && s->sizefirst_pars == 3)
		ft_printf_env(s);
	else if (ft_strncmp(s->pars[0], "pwd", 3) == 0 && s->sizefirst_pars == 3)
	{
		if (s->pwd)
		{
			g_output = 0;
			printf("%s\n", s->pwd);
		}
		else
			g_output = 1;
	}
	else if (ft_strncmp(s->pars[0], "echo", 4) == 0 && s->sizefirst_pars == 4)
		printf("\n");
	else if (ft_strncmp(s->pars[0], "cd", 2) == 0 && s->sizefirst_pars == 2)
		ft_cd(s);
	else if (ft_strncmp(s->pars[0], "exit", 4) == 0 && s->sizefirst_pars == 4)
		ft_exit();
	else if (ft_strncmp(s->pars[0], "export", 6) == 0 && s->sizefirst_pars == 6)
		ft_sort_env(s);
	else if (ft_strncmp(s->pars[0], "$?", 2) == 0)
		ft_dollar(s);
	else
		g_output = ft_execve(s, 0, 0, NULL);
}

static void	handle_complex_builtin(t_struc *s)
{
	s->sizefirst_pars = (int)ft_strlen(s->pars[0]);
	if (ft_strncmp(s->pars[0], "echo", 4) == 0 && s->sizefirst_pars == 4)
		ft_echo(s);
	else if (ft_strncmp(s->pars[0], "export", 6) == 0
		&& s->sizefirst_pars == 6)
		ft_export(s);
	else if (ft_strncmp(s->pars[0], "unset", 5) == 0 && s->sizefirst_pars == 5)
		g_output = ft_unset(s);
	else if (ft_strncmp(s->pars[0], "cd", 2) == 0 && s->sizefirst_pars == 2)
		ft_cd(s);
	else if (ft_strncmp(s->pars[0], "exit", 4) == 0 && s->sizefirst_pars == 4)
		ft_exit_par(s);
	else if (ft_strncmp(s->pars[0], "$?", 2) == 0)
		ft_dollar(s);
	else if (ft_strncmp(s->pars[0], "env", 3) == 0 && s->sizefirst_pars == 3)
	{
		g_output = 1;
		printf ("Error: syntax error near unexpected token\n");
	}
	else
		g_output = ft_execve(s, 0, 0, NULL);
}

void	ft_builtins(t_struc *s)
{
	s->size_pars = ft_len_tab(s->pars);
	if (s->size_pars == 1)
		handle_single_builtin(s);
	else if (s->size_pars > 1)
		handle_complex_builtin(s);
	ft_free_array(s->pars, ft_len_tab(s->pars) - 1);
	//ft_free_array( s->path, ft_len_tab(s->path) - 1);
}
