/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:44:47 by viburton          #+#    #+#             */
/*   Updated: 2023/09/14 14:23:15 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	**pipes_utils_1(t_struc *s, char **commands, int nb_commands, int i)
{
	t_list	*c;
	int		**fd;

	fd = (int **)malloc(sizeof(int *) * (nb_commands));
	while (i < nb_commands)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i ++;
	}
	i = 0;
	c = init_list(s, NULL, 0);
	while (i < nb_commands)
	{
		commands[i] = ft_strdup(c->content);
		c = c->next;
		i ++;
	}
	return (fd);
}

static void	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	redirect_io(t_struc *s, int **fd, int i, char **commands)
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
	exit(EXIT_FAILURE);
}

static void	pipe_utils(t_struc *s, char **commands, int i, int num_commands)
{
	int		**fd;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * num_commands);
	fd = pipes_utils_1(s, commands, num_commands, i);
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
	free(pid);
}

void	pipes(t_struc *s, int num_commands)
{
	char	**commands;
	int		i;
	pid_t	wpid;
	int		status;

	i = 0;
	commands = malloc (sizeof (char *) * num_commands); // Proteger le malloc
	pipe_utils(s, commands, i, num_commands);
	wpid = wait(&status);
	while (wpid > 0)
		wpid = wait(&status);
	while (i < num_commands)
	{
		free(commands[i]);
		i++;
	}
}
