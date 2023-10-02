/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:52:03 by viburton          #+#    #+#             */
/*   Updated: 2023/10/02 14:06:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char **ft_redirc(char *str)
{
    int i;
    char *res;

    i = 0;
    res = malloc(ft_strlen(str) * 
    while (str[i])
    {
        if (str[i] == '<' || str[i] == '>')
        {
            if (str[i+1] && (str[i+1] == '<' || str[i+1] == '>'))
                res[i]
        }
        
    }
    return (s->pars);
}