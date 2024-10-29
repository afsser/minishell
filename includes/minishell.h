/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:40:49 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/29 17:52:46 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// colors
# define ORANGE "\001\033[38;5;208m\002"
# define BLUE   "\001\033[38;5;27m\002"
# define GREEN  "\001\033[38;5;46m\002"
# define RST	"\001\033[0m\002"

// libs
# include "../libft/libft.h"
# include "environment.h"
# include "parsing.h"
# include "tokenizer.h"
# include "expander.h"
# include "executor.h"

# include <stdlib.h>
# include <unistd.h>
# include "fcntl.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// global
extern volatile int			g_signal;		

// typedefs
typedef struct s_env		t_env;
typedef struct s_token_list	t_token_list;
typedef struct s_tree		t_tree;
typedef struct termios		t_termios;
typedef struct s_str_list	t_str_list;

// enums
enum	e_bool
{
	FALSE,
	TRUE
};

// structs
typedef struct s_minishell
{
	t_tree			*tree;
	t_env			*envs;
	t_list			*fd_list;
}				t_minishell;

typedef struct s_main
{
	int				ret_code;
	int				backup_fd_in;
	char			*line;
	char			*line_to_readline;
	t_token_list	*token_list;
	t_tree			*tree;
	t_minishell		data;
	t_termios		term;
}				t_main;

// utils.c
char	*get_line_to_readline(t_env *env_list);
int		str_is_space(char *str);

#endif
