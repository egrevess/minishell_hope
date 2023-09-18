/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:01 by viburton          #+#    #+#             */
/*   Updated: 2023/09/18 11:50:10 by viburton         ###   ########.fr       */
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
	if (s->pars)
	{
		if (result == 0 && p->nb_pipe == 0)
			ft_builtins(s);
		else if (result != 1 && p->nb_pipe != 0)
			pipes(s, ft_count_pipe1(s) + 1);
	}
	s->index += 1;
	return (result);
}

int	main(int argc, char **argv, char **env)
{
	t_struc	s;
	t_pipe	p;
	int		i;

	(void) argv;
	s.index = 0;
	i = put_head();
	p.nb_pipe = 0;
	//signal(SIGINT, execut);
	//signal(SIGQUIT,execut1);
	if (argc != 1)
		exit(EXIT_FAILURE);
	while (42)
	{
		s.str = read_user_input();
		if (s.index == 0)
		{
			s.result = ft_init_env(&s, env);
			s.path = NULL;
			if (s.result == 0)
				exit (EXIT_FAILURE);
		}
		s.result = process_user_input(s.str, &s, &p);
		wait(&i);
	}
}
