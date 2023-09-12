/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:12 by viburton          #+#    #+#             */
/*   Updated: 2023/09/12 15:48:39 by viburton         ###   ########.fr       */
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

int	g_output;

typedef struct s_struc
{
	char	**pars;
	char	**env;
	char	**path;
	char	**copy_env;
	int		size_first_pars;
	int		size_second_pars;
	int		size_pars;
	int		lenght_env;
	char	*pwd;
	char	**history;
	int		checker_export;
	char	**new_pars_pipe;
	int		nb_pipe;
	int		echo_quotes;
	char	*heredoc_content;
}		t_struc;

typedef struct s_var
{
	char	*data;
	char	*value;
}		t_var;

typedef struct s_pipe
{
	int		nb_pipe;
	int		i;
	int		j;
	int		until;
	int		start;
	char	**temp;
	int		index;
}		t_pipe;

typedef struct s_command
{
	char				*command;
	struct t_command	*next;
}		t_command;

void	put_head(void);
char	**ft_parse(char *str, t_struc *s);
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
void	pipes(t_struc *s, int num_commands);
int		ft_execve_pipe(t_struc *s, char **command);
void	parse_and_execute(t_struc *s, t_list *c);
void	heredoc_handle(t_struc *s, char *delimiter);
t_list	*init_list(t_struc *s, t_list *c, int i);
int		ft_count_pipe1(t_struc *s);
int		check_only_quo(char *str, char c, int i, int one);
int		ft_check_other(const char *s, char c);
char	*ft_del_quotes(char	*s, char c, char d);
int		ft_count_pipe(char **line, t_pipe *p, int j, int i);
int		split_pipe_command_utils(char **pars, char **temp, int i);

#endif