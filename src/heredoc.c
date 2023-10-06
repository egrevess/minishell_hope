/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:12:05 by viburton          #+#    #+#             */
/*   Updated: 2023/10/06 17:22:05 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	execute_with_heredoc(t_struc *s, char *command, char *heredoc_content)
{
	int		pipefd[2];
	char	*com[2];
	pid_t	pid;

	pid = fork();
	pipe(pipefd);
	com[0] = command;
	com[1] = heredoc_content;
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		ft_execve_pipe(s, com);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipefd[0]);
		write(pipefd[1], heredoc_content, ft_strlen(heredoc_content));
		close(pipefd[1]);
		wait(NULL);
	}
}

void	heredoc_handle(t_struc *s, char *delimiter)
{
	char	**tmp;
	char	*tmp2;
	int		i = 0;

	tmp = ft_split(delimiter, ' ');
	i = 0;
	while (tmp[i])
	{
		if (i == 0)
			delimiter = tmp[i];
		else
		{
			if (i == 1)
				s->heredoc_content = tmp[i];
			else
			{
				s->heredoc_content = ft_strjoin(s->heredoc_content, " ");
				s->heredoc_content = ft_strjoin(s->heredoc_content, tmp[i]);
			}
		}
		i++;
	}
	tmp2 = readline("> ");
	while (ft_strncmp(delimiter, tmp2, ft_strlen(delimiter)))
	{
		s->heredoc_content = ft_strjoin(s->heredoc_content, tmp2);
		s->heredoc_content = ft_strjoin(s->heredoc_content, "\n");
		tmp2 = readline("> ");
	}
	execute_with_heredoc(s, s->pars[0], s->heredoc_content); //!! pas encore au point
}
