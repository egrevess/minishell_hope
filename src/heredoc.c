/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:12:05 by viburton          #+#    #+#             */
/*   Updated: 2023/10/02 16:09:02 by viburton         ###   ########.fr       */
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
	//printf("s->heredoc_content = %s", s->heredoc_content);
	//execute_with_heredoc(s, "echo", "Contenu du heredoc\n"); //fonctionne mais des erreures sorte. N'imprime pas...
	//printf(" s->pars[0] = \n s->heredoc_content = %s\n",   s->heredoc_content);
	execute_with_heredoc(s, s->pars[0], s->heredoc_content); //!! pas encore au point
}

void redirection(char *filename, int choice, char *str)
{
	int descripteurFichier;
	(void) str;

	// Ouvrir le fichier en mode écriture (O_CREAT : créer le fichier s'il n'existe pas)
	if (choice == 2)
		descripteurFichier = open(filename, O_WRONLY | O_CREAT, O_APPEND, S_IRUSR | S_IWUSR);

	if (choice == 1)
		descripteurFichier = open(filename, O_WRONLY | O_CREAT, O_TRUNC, S_IRUSR | S_IWUSR);
	
	// Vérifier si l'ouverture du fichier a réussi
	if (descripteurFichier == -1) {
		perror("Erreur lors de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	// Écrire dans le fichier
	write(descripteurFichier, "Bonjour, monde !\n", 17);
	printf("coucou\n");
	// Fermer le fichier
	close(descripteurFichier);
}