/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:07:33 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/18 14:12:25 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	verify_built_in(char *command)
{
	int			i;
	const char	*built_ins[] = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit"};

	i = 0;
	while (command && i < 7)
	{
		if (ft_strncmp(command, built_ins[i], -1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(t_tree *tree)
{
	int	command_is_built_in;

	if (!tree)
		return (0);
	command_is_built_in = 0;
	if (tree->type == COMMAND && tree->command)
		command_is_built_in = verify_built_in(tree->command->token.lexeme);
	else
		command_is_built_in = is_builtin(tree->right);
	return (command_is_built_in);
}

int	key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[0]))
		return (0);
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	if (key[i] == '\0')
		return (1);
	return (0);
}
