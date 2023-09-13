/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorburton <victorburton@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:01 by viburton          #+#    #+#             */
/*   Updated: 2023/09/13 15:22:56 by victorburto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*
void	execut(int sig)
{
	(void) sig;

	g_output = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	execut1(int sig)
{
	(void) sig;
	exit (EXIT_FAILURE);
}

void	execut2(int sig)
{
	(void) sig;
	//censé rien faire 
}
*/

char	*read_user_input(void)
{
	char	*str;

	str = readline("burtonshell >$ ");
	if (!str)
		ft_exit();
	add_history(str);
	return (str);
}

int	process_user_input(char *input, t_struc *s, t_pipe *p)
{
	int		result;

	s->pars = ft_parse(input, s);
	s->pars = ft_pipe(s, p);
	result = ft_pipes(s, p);
	ft_sub_dollar(s);
	s->pars = ft_parse_quotes(s);
	ft_find_pdw(s);
	return (result);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int		result;
	t_struc	s;
	t_pipe	p;
	//pid_t	pid;
	//char *arg;
	int		index;
	int		i = 1;
	int		result_bis;
	(void) argv;

	index = 0;
	put_head();
	p.nb_pipe = 0;
	//signal(SIGINT, execut);
	//signal(SIGQUIT,execut);
	if (argc == 1)
	{
		while (42)
		{
			str = read_user_input();
			if (index == 0)
			{
				result = ft_init_env(&s, env);
				s.path = NULL;
				if (result == 0)
					exit (EXIT_FAILURE);
			}
			result_bis = process_user_input(str, &s, &p);
			if (s.pars)
			{
				//printf("nb pipe %d\n", p.nb_pipe);
				if (result_bis == 0 && p.nb_pipe == 0)
				{
					ft_builtins(&s);
				}
				else if (result_bis != 1 && p.nb_pipe != 0)
				{
					pipes(&s, ft_count_pipe1(&s) + 1);
				}	
			}
			index++;
			wait(&i);
		}
	}
}
