/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viburton <viburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:29:12 by viburton          #+#    #+#             */
/*   Updated: 2023/10/02 16:01:30 by viburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
#include <fcntl.h>

void	rl_replace_line(const char *text, int clear_undo);

int	g_output;

typedef struct s_ij
{
	int	i;
	int	j;
	int	start;
	int	until;
	int	index;
}	t_ij;

typedef struct s_struc
{
	char	*str;
	char	**pars;
	char	**env;
	char	**path;
	char	**copy_env;
	int		sizefirst_pars;
	int		size_second_pars;
	int		size_pars;
	int		lenght_env;
	int		result;
	int		index;
	char	*pwd;
	char	**history;
	int		checker_export;
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

int		put_head(void);
int		ft_parse(char *str, t_struc *s, t_pipe *p);
char	**ft_parse_quotes(t_struc *s);
void	ft_builtins(t_struc *s);
int		ft_free_array(char **tab, int index);
void	ft_printf_env(t_struc *s);
int		ft_init_env(t_struc *s, char **env);
char	*ft_find_in_env(t_struc *s, int i);
int		ft_find_in_env_export(t_struc *s, int index);
char	*ft_find_pdw(t_struc *s);
int		ft_echo(t_struc *s, int index);
void	ft_export(t_struc *s);
int		ft_len_tab(char **tab);
void	ft_exit(void);
int		ft_execve(t_struc *s, int res, int status, char *str);
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
int		ft_count_pipe(char **line, t_pipe *p);
void	ft_free(t_struc *s, t_pipe *p);
void	pipe_util(t_struc *s, char **commands, int i, int num_commands);
void	execut(int sig);
void	execut1(int sig);
void	execut2(int sig);
int		ft_expr(t_struc *s);
void	free_path(t_struc *s);
void	handle_pwd(t_struc *s);
void 	redirection(char *filename, int choice, char *str);

#endif