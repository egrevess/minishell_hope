/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:09:09 by viburton          #+#    #+#             */
/*   Updated: 2023/10/09 16:26:59 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	**pars_redir(char *str)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_split(str, ' ');
	while (res[i] && res[i][0] != '>')
		i++;
	while (res[i])
	{
		res[i] = NULL;
		free(res[i]);
		i++;
	}
	return (res);
}

static void	process_parent(int pipe_fd[2], char *filename, int choice)
{
	char	buffer[4096];
	int		fd;
	ssize_t	bytesread;

	close(pipe_fd[1]);
	bytesread = read(pipe_fd[0], buffer, sizeof(buffer));
	close(pipe_fd[0]);
	wait(NULL);
	if (choice == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 000777);
	if (choice == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 000777);
	write(fd, buffer, bytesread);
	close(fd);
}

static void	pipe_redir(t_struc *s, char *filename, int choice)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		ft_execve_pipe(s, s->pars);
		exit(EXIT_FAILURE);
	}
	else
		process_parent(pipe_fd, filename, choice);
}

static void	redir(char *filename, int choice, char *str, t_struc *s)
{
	s->pars = pars_redir(str);
	pipe_redir(s, filename, choice);
}

int	redirection(int i, char *str, t_struc *s)
{
	if (str[i + 1] == '>')
	{
		if (str[i + 2] == ' ')
			redir(ft_substr(str, i + 3, ft_strlen(str)), 2, str, s);
		else
			redir(ft_substr(str, i + 2, ft_strlen(str)), 2, str, s);
	}
	else
	{
		if (str[i + 1] == ' ')
			redir(ft_substr(str, i + 2, ft_strlen(str)), 1, str, s);
		else
			redir(ft_substr(str, i + 1, ft_strlen(str)), 1, str, s);
	}
	return (4);
}
