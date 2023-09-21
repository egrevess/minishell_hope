/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:44:47 by viburton          #+#    #+#             */
/*   Updated: 2023/09/21 18:35:21 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

static int	**pipes_utils_2(t_struc *s, char **commands, int nb_cmds, int **fd)
{
	t_list	*temp;
	t_list	*c;
	int		i;

	i = 0;
	while (i < nb_cmds)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			exit(EXIT_FAILURE);
		i ++;
	}
	i = 0;
	c = init_list(s, NULL, 0);
	while (i < nb_cmds)
	{
		commands[i] = ft_strdup(c->content);
		temp = c->next;
		free (c->content);
		free (c);
		c = temp;
		i ++;
	}
	free(c);
	return (fd);
}

static int	**pipes_utils_1(t_struc *s, char **cmds, int nb_cmds, pid_t	*pid)
{
	int		**fd;
	int		i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (nb_cmds));
	if (!fd)
		exit(EXIT_FAILURE);
	fd = pipes_utils_2(s, cmds, nb_cmds, fd);
	while (i < nb_cmds)
	{
		setup_pipe(fd[i]);
		pid[i] = fork();
		if (pid[i] == -1)
			exit(EXIT_FAILURE);
		else if (pid[i] == 0)
			redirect_io(s, fd, i, cmds);
		else if (i > 0)
		{
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
		}
		i ++;
	}
	return (fd);
}

void	pipe_util(t_struc *s, char **commands, int i, int num_commands)
{
	int		**fd;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * num_commands);
	if (!pid)
		exit(EXIT_FAILURE);
	fd = pipes_utils_1(s, commands, num_commands, pid);
	close(fd[s->nb_pipe - 1][1]);
	free(pid);
	i = 0;
	while (i < num_commands)
	{
		free((void *)fd[i]);
		i++;
	}
	free(fd);
}
