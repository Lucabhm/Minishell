/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:50:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 13:48:18 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <errno.h>
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line_bonus.h"

// struct

typedef struct s_data
{
	char			**cmd_path;
	struct s_cmd	*s_n;
	char			*in;
	struct s_var	*envs;
	struct s_var	*export;
	char			*path_exe;
	int				e_code;
	int				fdin;
	int				fdout;
	int				fdpipe;
	int				fdhere;
	pid_t			*child;
	int				childnbr;
}				t_data;

typedef struct s_wild
{
	char	*befor;
	char	*middle;
	char	*after;
	int		d_q;
	int		s_q;
	char	*tmp2;
	int		j;
}				t_wild;

typedef struct s_cmd
{
	int	type;
}				t_cmd;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*nxt;
}				t_var;

typedef struct s_pipe
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_pipe;

typedef struct s_redir
{
	int				type;
	char			*f;
	int				mode;
	int				fd;
	struct s_cmd	*cmd;
}				t_redir;

typedef struct s_exe
{
	int		type;
	char	**argv;
}				t_exe;

typedef struct s_here_doc
{
	int				type;
	char			*l;
	struct s_cmd	*cmd;
}				t_here_doc;

typedef struct s_and_or
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_and_or;

typedef struct s_args
{
	char	*s;
	char	*q;
	char	*eq;
}				t_args;

typedef struct s_fill_right_sub
{
	char	**s;
	char	**q;
	char	**eq;
	t_cmd	*cmd;
}				t_fill_right_sub;

// global varible

extern int	g_signal;

// minishell

int		main(int argc, char **argv, char **env);
void	execute_command(t_data *data, pid_t id);
void	start_point(t_data *data, pid_t id);
int		check_builtin_main(t_data *data);
void	execute_cmd(t_cmd *t, t_data *data);

// cmd_prompt

char	*print_prompt(void);
char	*free_used_string(char *f, char *s, int ff, int sf);
char	*prompt_cwd(void);
int		find_s(char *pwd);
char	*get_username(char *cwd, t_data data);

// quotes

char	*check_for_quotes(char *input);
void	double_or_single(int *d, int *s, char quote);
char	*rm_quotes(char *q, char *eq);
void	rm_quotes_2(char *q, char **new, int *i, int *pos);

// quotes_utils

char	*c_env_2(char *ret, char *input, int *start, int end);
char	*get_env(char *value, t_var **env);
int		ft_strcmp(const char *s1, const char *s2);
char	*check_for_op(char *input);
char	*check_for_op_2(char *input, char *op);

// quotes_utils_2

char	*check_input(char *input, t_data *data);
char	*check_for_schar(char *input, t_data data);
char	*check_for_schar_2(char *token, t_data data);
char	*check_env(char *token, int *i, t_data data, int d_q);
char	*check_tilde(char *token, t_data data);

// quotes_utils_3

int		onlyop(char *input);
char	*get_home(t_data data);
void	count_pipe(char *input, t_data *data);

// token

void	token(char *input, t_data *data);
void	process_token(char token, t_args *args, t_data *data);
char	get_token(char **s, char **q, char **eq);
void	get_token_2(char **s, char *ret);
void	process_a(char **s, char *delimiter, int *d_q, int *s_q);

// fill_struct

t_cmd	*fill_exe(char **q, char **eq, char **s);
t_cmd	*fill_pipe(t_cmd *l, t_cmd *r);
t_cmd	*fill_redir(char **s, char **q, char **eq, t_cmd *s_n);
t_cmd	*fill_here_doc(char **s, char **q, char **eq, t_cmd *s_n);
t_cmd	*fill_and_or(t_cmd *l, t_cmd *r, int andor);

// fill_struct_utils

char	**alloc_argv(char *s);
void	check_for_mode(t_redir **cmd, char **q);
void	cat_struct(t_cmd *new, t_cmd *cmd);
char	**cat_struct_2(char **first, char **second, char **new);
int		count_argvs(char **argv);

// fill_struct_utils_2

t_cmd	*dup_struct(t_exe	*cmd);
t_cmd	*search_next(t_cmd *cmd, int type);
t_cmd	*fill_rightside(char **s, char **q, char **eq, char limit);
t_cmd	*process_token2(t_fill_right_sub *vars, char token);
t_cmd	*fill_right_sub(char **s, char **q, char **eq);

// fill_struct_utils_3

t_cmd	*fill_redir_2(t_fill_right_sub *sub, t_cmd *s_n, t_redir *cmd);
int		check_next(char *s, char t);
t_cmd	*fill_redir_at_fornt(t_redir *s_n, t_redir *cmd);

// execute

void	exe_execve(t_data *data, t_exe *cmd);
void	check_for_bultin(t_data *data, t_exe *cmd);
void	exe_redir(t_data *data, t_redir *cmd);
void	handle_input(t_data *data, t_here_doc *cmd);
void	exe_here_doc(t_data *data, t_here_doc *cmd);

// execute_2

void	exe_and_or(t_data *data, t_and_or *cmd);
void	execute_and(t_data *data, t_and_or *cmd, int id, int status);
void	execute_or(t_data *data, t_and_or *cmd, int id, int status);

// pipe

void	exe_pipe(t_data *data, t_pipe *cmd);
void	pipe_middle(t_data *data, t_cmd *cmd, int last);
void	fork_and_exe(t_data *data, t_cmd *cmd, int last);
void	child_process(int *pfd, t_data *data, t_cmd *cmd, int last);
void	wait_for_child(t_data *data);

// check_access

char	*check_for_access(t_data data, char **cmd);
char	*handle_nonexistent_path(char **cmd);
char	*handle_no_executable_in_path(char **paths, char **cmd);
char	*search_executable_in_paths(char **paths, char **cmd);

// cd

void	update_pwd(t_var *data);
void	update_oldpwd(t_var *data);
void	update_oldpwd_value(t_var *ptr, int pwd_found,
			t_var *new_node, t_var *data);
void	check_cd_access(char *directory, char *cmd);
void	exe_cd(t_data *data, t_exe *cmd);

// cd_utils

int		cd_only(t_data *data, t_exe *cmd);
int		cd_minus(t_data *data, t_exe *cmd);
int		cd_minus_minus(t_data *data, t_exe *cmd);

// echo

void	print_echo(int i, int nline, t_exe *cmd);
void	exe_echo(t_exe *cmd);

// env

void	check_env_access(char *directory, char *cmd);
void	exe_env(t_var *envs, t_exe *cmd);

// exit

void	exit_free(t_data data);
void	exe_exit(t_data data, t_exe *cmd);
int		is_word(char *str);
void	c_fds(int i);

// export_env_utils

t_var	*search_variable(t_data *data, char *name_to_search);
void	update_variable(t_var *ptr_env, char *arg, int len_name);
void	add_variable(t_data *data, char *arg, int len_name);

// export_env

int		is_valid(char *str);
void	process_env_argument(t_data *data, t_exe *cmd, int i);
void	exe_export_env(t_data *data, t_exe *cmd);
void	print_export_element(t_var *element);
void	print_export(t_var **export);

// export_export_utils

void	process_export_argument(t_data *data, char *argument);
void	process_export_with_equal(t_data *data, char *argument);
void	process_export_without_equal(t_data *data, char *argument);
void	handle_export_null(t_data *data, char *argument, int len_name);
t_var	*ft_lstlast_test(t_var *lst);

// export_export

void	exe_export_export(t_data *data, t_exe *cmd);

// sort_export

void	swap_a(t_var **a);
void	rotate_a(t_var **a);
int		check_sort(t_var **export);
void	sort_export(t_var **export);
char	*biggest(t_var **export);

// pwd

void	exe_pwd(void);

// unset

int		is_valid_unset(char *str);
void	exe_unset(t_data *data, t_exe *cmd);
void	unset_var(t_var **list, t_exe *cmd);

// free

char	**freeupm(char	**arr);
void	free_ast_helper(t_cmd *cmd);
void	free_ast(t_cmd *cmd);

// free_2

void	free_exe(t_exe *node);
void	free_redir(t_redir *node);
void	free_here(t_here_doc *node);
void	free_lst(t_var	**lst);
void	free_for_new_cmd(t_data *data);

// init_env

void	del(void *var);
void	ft_lstdelone_new(t_var **head,
			t_var	*node_to_remove, void (*del)(void *));
t_var	*ft_lstnew_new(char *name, char *value);
void	ft_lstadd_back_new(t_var **lst, t_var *new);
void	init_env(char **env, t_var **envs, int a);

// init_env_utils

void	add_oldpwd(t_var **export);
void	init_env_without(char **env, t_var **envs, int a);

// init_data

void	init_data(t_data *data, char **env);
void	init_data_structure(t_data *data);
void	init_cmd_path_and_env(t_data *data, char **env);
void	welcome_message(void);

// signals

void	handle_signals_heredoc(void);
void	handle_signals(void);
void	handle_signals2(void);

// signals_2

void	control_c(int signum);
void	control_c_2(int signum);
void	control_c_heredoc(int signum);

// error

void	error_msg_without_e(char *cmd, char *msg, char *msg2, int error_code);
void	error_msg(char *cmd, char *msg, char *msg2, int error_code);
void	error(char *msg, int error_code);
char	*error_quotes(int par, int double_q, int single_q, char *input);

// wildcard

char	*check_dir(char *token, int *i);
void	star_at_front(t_wild *wild, char *tmp, int *i);
void	star_in_middle(t_wild *wild, char *tmp, int *i);
char	*rm_star_and_quotes(char *str);
void	check_empty_str(char **str);

// wildcard_2

char	*get_dir(char *b, char *m, char *a);
char	*rm_star(char *token);
int		match(char *b, char *m, char *a, struct dirent *i);
char	*loop_for_wild(char *b, char *m, char *a, DIR *dir);

// struct nbr

# define EXECVE 0
# define PIPE 1
# define REDIR 2
# define HERE 3
# define AND 4
# define OR 5
# define SUBSHELL 6

// Error

# define ERROR_0 "Invalid number of arguments\n"
# define ERROR_1 "malloc"
# define ERROR_2 "open"
# define ERROR_3 "dup2"
# define ERROR_4 "execve"
# define ERROR_5 "pipe"
# define ERROR_6 "fork"
# define ERROR_7 "Env path not found !\n"
# define ERROR_8 "access"
# define ERROR_9 "wait"
# define ERROR_10 "Empty String\n"
# define ERROR_11 "pwd"
# define ERROR_12 "cd"

#endif