/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:38:39 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/10/15 12:43:36 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// libs
# include "minishell.h"
# include "environment.h"
# include "tokenizer.h"
# include "expander.h"
# include "executor.h"

// typedefs
typedef struct s_token_list	t_token_list;
typedef struct s_minishell	t_minishell;
typedef struct s_env		t_env;
typedef struct s_tree		t_tree;
typedef struct s_aux_tree	t_aux_tree;
typedef struct s_str_list	t_str_list;

// structs
typedef struct s_tree
{
	int				type;
	t_token_list	*command;
	struct s_tree	*subshell;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_aux_tree
{
	int				idx;
	int				parenthesis_idx;
	int				and_or_idx;
	int				pipe_idx;
	int				redir_counter;
	t_token_list	*aux;
	t_token_list	*aux2;
	t_token_list	*args;
	t_token_list	*redir_list;
	t_token_list	*sublist_left;
	t_token_list	*sublist_right;
	t_tree			*tree;
}	t_aux_tree;

// get_tree.c
t_tree	*get_tree(t_token_list *token_list, t_minishell *data);
int		index_to_close_parenthesis(t_token_list *token_list);
int		index_to_open_parenthesis(t_token_list *token_list);
void	*free_tree(t_tree **tree);
void	*free_tree_all(t_tree **tree);

// make_tree.c
t_tree	*make_tree(t_token_list *token_list, t_minishell *data);

// make_tree_cmd.c
t_tree	*make_tree_cmd(t_token_list *token_list, t_minishell *data);

// make_tree_cmd_recursive.c
t_tree	*make_tree_cmd_recursive(t_token_list *redir_list, t_token_list *args, \
	t_minishell *data);

// here_doc.c
void	print_error_message(char *delimiter);
void	write_on_file(int fd, char *line, int need_to_expand, t_env *envp_list);
void	heredoc_fork(char *file_name, char *delimiter, t_env *envp_list);
char	*create_heredoc_name(char *delimiter);
char	*create_heredoc(char *delimiter, t_minishell *data);

#endif
