/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:15 by viburton          #+#    #+#             */
/*   Updated: 2023/10/06 19:06:26 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	**pars_redir(char *str)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_split(str, ' ');
	while (res[i] && res[i][0] != '<')
		i++;
	while (res[i])
	{
		res[i] = NULL;
		free(res[i]);
		i++;
	}
	return (res);
}

int	redir_in(char *filename, char *str, t_struc *s)
{
	int file_fd = open(filename, O_RDONLY);
    ssize_t	bytesread;
    
    s->pars = pars_redir(str);
    if (file_fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Rediriger l'entrée standard (0) vers le descripteur de fichier du fichier ouvert
    if (dup2(file_fd, STDIN_FILENO) == -1) {
        perror("Erreur lors de la redirection de l'entrée standard");
        exit(EXIT_FAILURE);
    }

    // Fermer le descripteur de fichier du fichier ouvert (il reste ouvert dans l'entrée standard)
    close(file_fd);

    // Lire l'entrée standard (qui est maintenant redirigée depuis le fichier)
    char buffer[4096];
    ssize_t bytesRead;

    bytesread = read(STDIN_FILENO, buffer, sizeof(buffer));
    
    // ajouter recuperer dans command !!
    ft_execve(s, 0, 0, NULL);
    
	return (4);
}

int	heredocs(int i, char *delimiter, char *str, t_struc *s)
{
	if (str[i + 1] == '<')
	{
		if (str[i + 2] == ' ')
			delimiter = ft_substr(str, i + 3, ft_strlen(str));
		else
			delimiter = ft_substr(str, i + 2, ft_strlen(str));
		return (1);	
	}
	else
	{
		if (str[i + 1] == ' ')
			redir_in(ft_substr(str, i + 2, ft_strlen(str)), str, s);
		else
			redir_in(ft_substr(str, i + 1, ft_strlen(str)), str, s);
		return (4);
	}
}