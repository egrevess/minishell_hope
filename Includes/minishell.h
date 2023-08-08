/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmagrevesse <emmagrevesse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:12 by viburton          #+#    #+#             */
/*   Updated: 2023/05/19 11:55:12 by emmagrevess      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <signal.h>
# include <limits.h>

int g_output; 

typedef struct s_struc
{
	char	**pars;
	char	**env;
	char	**path;
	char	**copy_env;
	int		size_first_pars; // pour les builtins comme ca je peux comparer et utiliser la longueur du seul pars
	int		size_second_pars;
	int		size_pars;// le nombre de pars 
	int		lenght_env; // variable utile pour ajouter des nouvelles varibales 
	char	*pwd;
	char	**history;
	int		checker_export;
	char	**new_pars_pipe;
	int		nb_pipe;
	int		echo_quotes;
	//t_var	*var;
}		t_struc;

typedef struct s_var
{
	char	*data;
	char	*value;
}		t_var;

typedef	struct s_pipe
{
	int	nb_pipe;
	int		i;
	int		j;
	int		until;
	int		start;
	char	**temp;
	int		index;
}		t_pipe;

typedef struct s_command
{
	char		*command;
	struct t_command	*next;
}		t_command;

void    put_head(void);
char    **ft_parse(char *str);
char	**ft_parse_quotes(t_struc *s);
void	ft_builtins(t_struc *s);
int		len_pars(char **pars);
int		ft_free_array(char **tab, int index);
void	ft_printf_env(t_struc *s);
int		ft_init_env(t_struc *s, char **env);
char	*ft_find_in_env(t_struc *s, int i);
int		ft_find_in_env_export(t_struc *s, int index);
char	*ft_find_pdw(t_struc *s);
void	ft_echo(t_struc *s);
void	ft_export(t_struc *s);
int		ft_len_tab(char **tab);
void	ft_exit(void);
void	ft_signal(int sig);
int		ft_execve(t_struc *s);
int		ft_unset(t_struc *s);
int		ft_find_in_env_unset(t_struc *s, int index);
void	ft_cd(t_struc *s);
void	change_value_env(t_struc *s, char *temp);
char	**ft_pipe(t_struc *s, t_pipe *p);
int		ft_pipes(t_struc *s, t_pipe *p);
int		check_pipe(t_struc *s, t_pipe *p);
void	ft_sort_env(t_struc *s);
void	ft_copy_env(t_struc	*s);
void	ft_exit_par(t_struc *s);
void	ft_dollar(t_struc *s);
void	ft_sub_dollar(t_struc *s);
int		ft_find_in_env_dollar(t_struc *s, int index);
int		ft_in_env(t_struc *s, char *var);
void 	pipes(t_struc *s/*char *in, char *out*/);
void	parse_and_execute(t_struc *s, t_list *c);
void 	pipes5(t_struc *s/*char *in, char *out*/);

#endif