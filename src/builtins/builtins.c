/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:47 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/06/22 16:32:17 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_find_pdw(t_struc *s)
{
	s->pwd = malloc(sizeof(*s->pwd) * 1024);
	getcwd(s->pwd, 1024);
	return (s->pwd);
}

// à transformer pour que ça puisse marcher pour autre chose que le parsing !! / ou a voir si on se fait pas baiser à la correction 
void	ft_builtins(t_struc *s)
{
	s->size_pars = len_pars(s->pars);
	if (s->size_pars == 1)
	{
		s->size_first_pars = (int) ft_strlen(s->pars[0]);
		if (ft_strncmp(s->pars[0], "env", (size_t) 3) == 0 && (int) ft_strlen(s->pars[0]) == 3)
			ft_printf_env(s);
		else if(ft_strncmp(s->pars[0], "pwd", (size_t) 3) == 0 && (int) ft_strlen(s->pars[0]) == 3)
		{
			if (s->pwd)
			{
				g_output = 0;
				printf("%s\n",s->pwd);
			}
			else 
				g_output = 1;
		}
		else if (ft_strncmp(s->pars[0], "echo", (size_t) 4) == 0 && (int) ft_strlen(s->pars[0]) == 4)
		{
			g_output = 0;
			printf("\n");
		}
		else if (ft_strncmp(s->pars[0], "cd", (size_t) 2) == 0 && (int) ft_strlen(s->pars[0]) == 2)
			ft_cd(s);
		else if (ft_strncmp(s->pars[0], "exit", (size_t) 4) == 0 && (int) ft_strlen(s->pars[0]) == 4)
			ft_exit();
		else if (ft_strncmp(s->pars[0], "export", (size_t) 6) == 0 && (int) ft_strlen(s->pars[0]) == 6)
			ft_sort_env(s);
		else if (ft_strncmp(s->pars[0], "$?", (size_t) 2) == 0)
			ft_dollar(s);
		else 
			g_output = ft_execve(s);
	}
	else if (s->size_pars > 1)
	{
		s->size_first_pars = (int) ft_strlen(s->pars[0]);
		if (ft_strncmp(s->pars[0], "echo", (size_t) 4) == 0 && (int) ft_strlen(s->pars[0]) == 4)
			ft_echo(s);
		else if (ft_strncmp(s->pars[0], "export", (size_t) 6) == 0 && (int) ft_strlen(s->pars[0]) == 6)
			ft_export(s);
		else if (ft_strncmp(s->pars[0], "unset", (size_t) 5) == 0 && (int) ft_strlen(s->pars[0]) == 5)
			g_output = ft_unset(s);
		else if (ft_strncmp(s->pars[0], "cd", (size_t) 2) == 0 && (int) ft_strlen(s->pars[0]) == 2)
			ft_cd(s);
		else if (ft_strncmp(s->pars[0], "exit", (size_t) 4) == 0 && (int) ft_strlen(s->pars[0]) == 4)
			ft_exit_par(s);
		else
			g_output = ft_execve(s);
	}
}