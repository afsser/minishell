/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:06:08 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:33:45 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_and(t_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);
	if (ret_code == 0)
		ret_code = exec_tree(tree->right, data);
	return (ret_code);
}

int	exec_or(t_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);
	if (ret_code != 0)
		ret_code = exec_tree(tree->right, data);
	return (ret_code);
}
