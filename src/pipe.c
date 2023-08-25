/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorburton <victorburton@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:56:16 by emmagrevess       #+#    #+#             */
/*   Updated: 2023/08/25 18:55:11 by victorburto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_pipes(t_struc *s, t_pipe *p)
{
	if (check_pipe(s, p) == 1)
	{
		printf("Error: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

t_list	*init_list(t_struc *s, t_list *c)
{
	int		i;
	char	*command;

	i = 0;
	command = NULL;
	while (s->pars[i])
	{
		if (s->pars[i][0] != '|')
		{
			if (command == NULL)
				command = ft_strjoin(s->pars[i], " ");
			else
			{
				command = ft_strjoin(command, s->pars[i]);
				command = ft_strjoin(command, " ");
			}
		}
		else
		{
			ft_lstadd_back(&c, ft_lstnew(command));
			command = NULL;
		}
		i++;
	}
	ft_lstadd_back(&c, ft_lstnew(command));
	ft_lstadd_back(&c, ft_lstnew(NULL));
	return (c);
}

int	ft_execve_pipe(t_struc *s, char **command)
{
	int		i;

	i = 0;
	if (ft_in_env(s, "PATH") != -1)
		s->path = ft_split(ft_find_in_env(s, ft_in_env(s, "PATH")), ':');
	if (!s->path)
	{
		printf("minishell: %s: command not found\n", command[0]);
		exit(EXIT_FAILURE);
	}
	while (s->path[i])
	{
		//printf("s->path[i]= %s <=====> command[0]= %s <=====> command[1] = %s\n ",s->path[i],command[0], command[1]);
		if (access(ft_strjoin(ft_strjoin(s->path[i], "/"),
					command[0]), X_OK) == 0)
			return (execve(ft_strjoin(ft_strjoin(s->path[i], "/"),
						command[0]), command, s->env));
		else if (access(command[0], X_OK) == 0)
			return (execve(command[0], command, s->env));
		i++;
	}
	printf("minishell: %s: command not found\n", command[0]);
	return (1);
}

int	ft_count_pipe1(t_struc *s) //METTRE DANS PIPE.C LE NOUVEAU FT_COUNT_PIPE (QUI EST UNE NOUVELLE FONCTION )
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s->pars[i])
	{
		if (s->pars[i][0] == '|' && (int) ft_strlen(s->pars[i]) == 1)
			j++;
		i++;
	}
	s->nb_pipe = j;
	return (j);
}

void	pipes(t_struc *s)
{
	int		num_commands = (ft_count_pipe1(s) + 1);
	char	*commands[num_commands];
	int		fd[num_commands - 1][2];
	pid_t	pid[num_commands];
	int		i = 0;
	t_list	*c = init_list(s, NULL);

	while (i < num_commands)
	{
		commands[i] = ft_strdup(c->content);
		c = c->next;
		i ++;
	}
	i = 0;
	while (i < num_commands)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
		{
			if (i == 0)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][0]);
				close(fd[i][1]);
			}
			else if (i == num_commands - 1)
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
		else
		{
			if (i > 0)
			{
				close(fd[i - 1][0]);
				close(fd[i - 1][1]);
			}
		}
		i ++;
	}
	close(fd[s->nb_pipe - 1][1]); // Ferme l'extrémité d'écriture du dernier pipe
	pid_t	wpid;
	int		status;
	while ((wpid = wait(&status)) > 0);
	i = 0;
	while (i < num_commands)
	{
		free(commands[i]);
		i++;
	}
}
