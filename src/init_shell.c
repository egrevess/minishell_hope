/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:43:05 by viburton          #+#    #+#             */
/*   Updated: 2023/09/18 11:50:38 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	put_head(void)
{
	write(1, "\n██████╗ ██╗   ██╗██████╗ ████████╗ ██████╗ ███╗   ██╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n\
██╔══██╗██║   ██║██╔══██╗╚══██╔══╝██╔═══██╗████╗  ██║    ██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██████╔╝██║   ██║██████╔╝   ██║   ██║   ██║██╔██╗ ██║    ███████╗███████║█████╗  ██║     ██║     \n\
██╔══██╗██║   ██║██╔══██╗   ██║   ██║   ██║██║╚██╗██║    ╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██████╔╝╚██████╔╝██║  ██║   ██║   ╚██████╔╝██║ ╚████║    ███████║██║  ██║███████╗███████╗███████╗\n\
╚═════╝  ╚═════╝ ╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═══╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n\
", 1475);
	return (1);
}
