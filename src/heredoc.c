/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorburton <victorburton@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:18:36 by victorburto       #+#    #+#             */
/*   Updated: 2023/08/25 16:46:59 by victorburto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	execute_with_heredoc(t_struc *s, char *command, char *heredoc_content)
{
	int		pipefd[2];
	char	*com[2];
	pid_t	pid = fork();

	pipe(pipefd);
	com[0] = command;
	com[1] = heredoc_content;
	if (pid == 0)
	{
		// Enfant
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		// Exécute la commande
		ft_execve_pipe(s, com);
		exit(0);
	}
	else if (pid > 0)
	{
		// Parent
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
	//printf("s->heredoc_content = %s", s->heredoc_content);
	//execute_with_heredoc(s, "echo", "Contenu du heredoc\n"); //fonctionne mais des erreures sorte. N'imprime pas...
	//printf(" s->pars[0] = \n s->heredoc_content = %s\n",   s->heredoc_content);
	execute_with_heredoc(s, s->pars[0], s->heredoc_content); //!! pas encore au point
}
