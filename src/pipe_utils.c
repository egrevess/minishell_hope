/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:44:47 by viburton          #+#    #+#             */
/*   Updated: 2023/09/05 12:04:15 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	pipes_utils_1(t_struc *s, char **commands, int num_commands, int i)
{
	t_list	*c;

	c = init_list(s, NULL);
	while (i < num_commands)
	{
		commands[i] = ft_strdup(c->content);
		c = c->next;
		i ++;
	}
}

static void	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	redirect_io(t_struc *s, int fd[][2], int i, char **commands)
{
	if (i == 0)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	else if (i == ft_count_pipe1(s))
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	else
	{
		dup2(fd[i][1], STDOUT_FILENO);
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	ft_execve_pipe(s, ft_split(commands[i], ' '));
	perror("ft_execve_pipe");
	exit(EXIT_FAILURE);
}

static void	pipe_utils(t_struc *s, char **commands, int i, int num_commands)
{
	int		fd[num_commands - 1][2];
	pid_t	pid[num_commands];

	pipes_utils_1(s, commands, num_commands, i);
	while (i < num_commands)
	{
		setup_pipe(fd[i]);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
			redirect_io(s, fd, i, commands);
		else if (i > 0)
		{
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
		}
		i ++;
	}
	close(fd[s->nb_pipe - 1][1]);
}

void	pipes(t_struc *s, int num_commands)
{
	char	*commands[num_commands];
	int		i;
	pid_t	wpid;
	int		status;

	i = 0;
	pipe_utils(s, commands, i, num_commands);
	while ((wpid = wait(&status)) > 0);
	while (i < num_commands)
	{
		free(commands[i]);
		i++;
	}
}
