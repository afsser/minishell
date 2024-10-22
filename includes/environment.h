/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:37:12 by educastro         #+#    #+#             */
/*   Updated: 2024/10/15 12:50:21 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

// libs
# include "minishell.h"
# include "parsing.h"
# include "tokenizer.h"
# include "expander.h"
# include "executor.h"
# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;
typedef struct s_env		t_env;

// structs
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

// env_func1.c
void	env_insert_node(t_env **head, char *key, char *value);
void	env_delete_value(t_env **head, char *key);
char	**create_envp(t_env *head);
t_env	*env_create_list(char *envp[]);
t_env	*env_create_node(char *key, char *value);

// env_func2.c
void	env_clear_list(t_env **head);
int		att_existing_value(t_env *head, char *key, char *value);
char	*search_value(t_env *head, char *key);
int		envp_list_size(t_env *head);
void	free_envp(char **envp);

#endif
