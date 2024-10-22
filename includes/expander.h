/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:42:26 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 12:44:50 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// libs
# include "minishell.h"
# include "environment.h"
# include "parsing.h"
# include "tokenizer.h"
# include "executor.h"
# include "../libft/libft.h"

// structs
typedef struct s_str_list
{
	char				letter;
	struct s_str_list	*next;
}				t_str_list;

// expand_heredoc.c
char	*expand_heredoc(char *str, t_env *envp_list);

// expand_string.c
char	*expand_string(char *str, t_env *head);

// expand_cmd.c
char	*expand_command(char *command, t_env *envp_list);

// string_list.c
void	add_letter_list(t_str_list **lst, char letter);
int		size_list(t_str_list *lst);
void	add_string_to_list(t_str_list **lst, char *str);
void	clear_str_list(t_str_list **head);
char	*create_string_from_list(t_str_list *lst);

// utils.c
int		ternary(int condition, int if_true, int if_false);
int		is_valid_var(char letter);
char	*remove_quotes(char	*delimiter);

#endif