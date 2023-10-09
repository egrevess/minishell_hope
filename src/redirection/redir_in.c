/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:15 by viburton          #+#    #+#             */
/*   Updated: 2023/10/09 16:01:09 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// static char	**pars_redir(char *str)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
// 	res = ft_split(str, ' ');
// 	while (res[i] && res[i][0] != '<')
// 		i++;
// 	while (res[i])
// 	{
// 		res[i] = NULL;
// 		free(res[i]);
// 		i++;
// 	}
// 	return (res);
// }

int	redir_in(char *filename, char *str, t_struc *s)
{
	// //printf("filename = %s|\n", filename);
	// int file_fd = open(filename, O_RDONLY);
    
    // s->pars = pars_redir(str);
    // if (file_fd == -1) {
    //     perror("Erreur lors de l'ouverture du fichier");
    //     exit(EXIT_FAILURE);
    // }

    // // Rediriger l'entrée standard (0) vers le descripteur de fichier du fichier ouvert
    // if (dup2(file_fd, STDIN_FILENO) == -1) {
    //     perror("Erreur lors de la redirection de l'entrée standard");
    //     exit(EXIT_FAILURE);
    // }

    // // Fermer le descripteur de fichier du fichier ouvert (il reste ouvert dans l'entrée standard)
    // close(file_fd);

    // // Lire l'entrée standard (qui est maintenant redirigée depuis le fichier)
    // char buffer[4096];
	// read(STDIN_FILENO, buffer, sizeof(buffer));
    
    // // ajouter recuperer dans command !!
	// //printf("s->pars = %s == buffer = %s\n", s->pars[1], buffer);
	// s->pars[1] = buffer;
	// s->pars[2] = NULL;
    // ft_execve(s, 0, 0, NULL);
	// s->pars[1] = NULL;
    // free(STDIN_FILENO);
	free(filename);
	(void) str;
	(void) s;
	printf("\n");
	return (4);
}

int	heredocs(int i, char *delimiter, char *str, t_struc *s)
{
	if (str[i + 1] == '<' && str[i + 2])
	{
		if (str[i + 2] == ' ')
			delimiter = ft_substr(str, i + 3, ft_strlen(str));
		else
			delimiter = ft_substr(str, i + 2, ft_strlen(str));
	}
	else
	{
		if (str[i + 1] == ' ')
			redir_in(ft_substr(str, i + 2, ft_strlen(str)), str, s);
		else
			redir_in(ft_substr(str, i + 1, ft_strlen(str)), str, s);
		return (4);
	}
	if (delimiter)
	{
		s->pars = ft_split(str, ' ');
		heredoc_handle(s, delimiter);
	}
	return (4);
}
