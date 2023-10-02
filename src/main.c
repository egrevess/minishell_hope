/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:01 by viburton          #+#    #+#             */
/*   Updated: 2023/10/02 14:47:31 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*read_user_input(void)
{
	char	*str;

	str = readline("burtonshell >$ ");
	if (!str)
		exit(EXIT_SUCCESS);
	printf("in execut\n");
	add_history(str);
	return (str);
}

int	process_user_input(char *input, t_struc *s, t_pipe *p)
{
	int		result;

	if (ft_parse(input, s, p) == 4)
		return (1);
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
	free(s->pwd);
	free(s->str);
	return (result);
}

void	handle_signal(char *s)
{
	if (s && ft_strncmp(s, "cat", 3) != 0 && ft_strncmp(s, "grep", 4) != 0)
	{
		signal(SIGINT, execut);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, execut1);
		signal(SIGQUIT, execut2);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_struc	s;
	t_pipe	p;
	int		i;

	(void) argv;
	s.index = 0;
	p.nb_pipe = 0;
	handle_signal(" ");
	if (argc != 1)
		exit(EXIT_FAILURE);
	i = put_head();
	while (42)
	{
		s.str = read_user_input();
		handle_signal(s.str);
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
