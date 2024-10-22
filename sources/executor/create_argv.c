/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:06:17 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/18 19:19:19 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*get_command_list(t_token_list *token_list)
{
	char			*expanded_string;
	t_token_list	*aux;
	t_token_list	*expanded_list;

	aux = token_list;
	expanded_list = NULL;
	while (aux)
	{
		expanded_string = aux->token.lexeme;
		if (ft_strlen(expanded_string) != 0)
			add_token_to_list(&expanded_list, ft_strdup(expanded_string), WORD);
		aux = aux->next;
	}
	return (expanded_list);
}

static void	populate_new_argv(char **argv, char **new_argv)
{
	int	i;
	int	valid_count;

	i = 0;
	valid_count = 0;
	while (argv[i] && argv[i][0] == '\0')
	{
		free(argv[i]);
		i++;
	}
	while (argv[i] != NULL)
	{
		new_argv[valid_count] = argv[i];
		valid_count++;
		i++;
	}
	new_argv[valid_count] = NULL;
}

static char	**remove_empty_args(char **argv)
{
	int		i;
	int		valid_count;
	char	**new_argv;

	i = 0;
	valid_count = 0;
	while (argv[i] && argv[i][0] == '\0')
		i++;
	while (argv[i] != NULL)
	{
		valid_count++;
		i++;
	}
	new_argv = malloc((valid_count + 1) * sizeof(char *));
	if (!new_argv)
		return (NULL);
	populate_new_argv(argv, new_argv);
	free(argv);
	return (new_argv);
}

char	**create_argv(t_tree *tree, t_minishell *data)
{
	int				i;
	int				args_num;
	char			**argv;
	t_token_list	*expanded_list;

	i = 0;
	expanded_list = get_command_list(tree->command);
	args_num = token_list_size(expanded_list);
	argv = malloc((args_num + 1) * sizeof(char *));
	argv[args_num] = NULL;
	while (i < args_num)
	{
		argv[i] = expand_string(token_get_node_index(\
			expanded_list, i)->token.lexeme, data->envs);
		i++;
	}
	token_clear_list(&expanded_list);
	argv = remove_empty_args(argv);
	return (argv);
}
