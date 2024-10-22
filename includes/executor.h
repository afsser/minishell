/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:37:12 by educastro         #+#    #+#             */
/*   Updated: 2024/10/18 14:41:42 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// libs
# include "minishell.h"
# include "environment.h"
# include "parsing.h"
# include "tokenizer.h"
# include "expander.h"
# include "../libft/libft.h"

// typedefs
typedef struct s_token_list	t_token_list;
typedef struct s_minishell	t_minishell;
typedef struct s_env		t_env;
typedef struct s_tree		t_tree;
typedef struct s_aux_tree	t_aux_tree;

// structs
typedef struct s_cmd_for_fork
{
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;
}				t_cmd_for_fork;

typedef struct s_builtin
{
	int		ret_code;
	int		fd_redir;
	int		args_num;
	char	*cmd;
	char	**argv;
	char	**envp;
}	t_builtin;

// signals.c
void			sig_handler_heredoc(int signal __attribute__((unused)));
void			sig_handler_sigint(int signal __attribute__((unused)));
void			sig_handler_redo_readline(int signal __attribute__((unused)));

// signals_handler.c
void			init_signals(void);
void			heredoc_signals(void);
void			execution_signals(int pid);

// signals_macros.c
int				term_by_signal(int status);
int				term_normaly(int status);
int				exit_status(int status);
int				term_signal(int status);
int				get_return_value(int status);

// create_argv.c
t_token_list	*get_command_list(t_token_list *token_list);
char			**create_argv(t_tree *tree, t_minishell *data);

// exec_pipe.c
int				exec_pipe(t_tree *tree, t_minishell *data);

// exec_tree.c
int				exec_tree(t_tree *tree, t_minishell *data);

// exec_cmd.c
int				exec_cmd(t_tree *tree, t_minishell *data);

// exec_and_or.c
int				exec_and(t_tree *tree, t_minishell *data);
int				exec_or(t_tree *tree, t_minishell *data);

// exec_cmd_fork.c
int				exec_cmd_fork(t_tree *tree, t_minishell *data);
int				execute_command(t_tree *tree, t_minishell *data);
int				exec_execve(t_tree *tree, t_minishell *data);
int				display_error(char *cmd);

// fd_list.c
int				close_fd(int fd);
void			close_pipe(int *pipe_fd);
void			fd_list_add_fd(t_list **fd_list, int fd);
void			fd_list_close_clear(t_list **fd_list);

// utils.c
int				open_redir(char *path_to_file, int type);
int				is_directory(char *path);
void			specific_error(char *cmd, char *error);

// builtins
int				builtin_echo(char **args);
int				builtin_cd(char *args[], t_minishell *data);
int				builtin_env(t_minishell *data);
int				builtin_exit(char **argv, t_minishell *data);
int				builtin_export(char **argv, t_minishell *data);
int				builtin_pwd(void);
int				builtin_unset(char **argv, t_env **envp_list);

int				process_redirections(t_tree *tree, t_minishell *data);
int				builtin_process(t_tree *tree, t_minishell *data);
int				is_builtin(t_tree *tree);
int				verify_builtin(char *command);

int				key_is_valid(char *key);
void			print_sorted_envp(t_minishell *data);
void			print_envp(char **envp);
void			export_print_error_message(char *key_value);
int				key_exist(char *name, t_env *envs);

#endif