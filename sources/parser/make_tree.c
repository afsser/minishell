/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:12:53 by educastro         #+#    #+#             */
/*   Updated: 2024/10/15 13:02:29 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	divide_tree(t_aux_tree *aux_tree, t_token_list *token_list, \
	t_minishell *data)
{
	aux_tree->aux = token_get_node_index(token_list, aux_tree->idx);
	if (aux_tree->aux)
		aux_tree->tree->type = aux_tree->aux->token.type;
	aux_tree->sublist_left = token_get_sublist(token_list, 0, aux_tree->idx);
	aux_tree->sublist_right = token_get_sublist(token_list, aux_tree->idx + 1, \
		token_list_size(token_list));
	aux_tree->tree->left = make_tree(aux_tree->sublist_right, data);
	if (aux_tree->tree->left)
		aux_tree->tree->right = make_tree(aux_tree->sublist_left, data);
	token_clear_list(&aux_tree->sublist_left);
	token_clear_list(&aux_tree->sublist_right);
	if (aux_tree->tree->left == NULL || aux_tree->tree->right == NULL)
		free_tree(&aux_tree->tree);
}

static void	find_division_index(t_aux_tree *aux_tree)
{
	while (aux_tree->aux)
	{
		if (aux_tree->aux->token.type == CLOSE_PARENTHESIS)
		{
			aux_tree->parenthesis_idx = \
				index_to_open_parenthesis(aux_tree->aux->next);
			if (aux_tree->parenthesis_idx == -1)
			{
				aux_tree->idx += 1;
				aux_tree->aux = token_get_node_index(aux_tree->aux, \
					aux_tree->idx);
			}
			else
				free_tree(&aux_tree->tree);
		}
		else if (aux_tree->and_or_idx == -1 && (aux_tree->aux->token.type \
					== AND || aux_tree->aux->token.type == OR))
			aux_tree->and_or_idx = aux_tree->idx;
		else if (aux_tree->pipe_idx == -1 && \
			(aux_tree->aux->token.type == PIPE))
			aux_tree->pipe_idx = aux_tree->idx;
		aux_tree->idx++;
		if (aux_tree->aux)
			aux_tree->aux = aux_tree->aux->next;
	}
}

static void	init_values(int *i, t_aux_tree *aux_tree, t_token_list *token_list)
{
	*i = 0;
	aux_tree->parenthesis_idx = 0;
	aux_tree->and_or_idx = -1;
	aux_tree->pipe_idx = -1;
	aux_tree->aux = token_list;
	aux_tree->tree = NULL;
}

t_tree	*make_tree(t_token_list *token_list, t_minishell *data)
{
	t_aux_tree	aux_tree;

	init_values(&aux_tree.idx, &aux_tree, token_list);
	if (token_list == NULL)
		return (NULL);
	aux_tree.tree = malloc(sizeof(t_tree));
	ft_bzero(aux_tree.tree, sizeof(t_tree));
	find_division_index(&aux_tree);
	if (aux_tree.tree == NULL)
		return (NULL);
	if (aux_tree.and_or_idx != -1)
		aux_tree.idx = aux_tree.and_or_idx;
	else if (aux_tree.pipe_idx != -1)
		aux_tree.idx = aux_tree.pipe_idx;
	else
	{
		free(aux_tree.tree);
		aux_tree.aux = invert_list(token_get_sublist(token_list, 0, \
						token_list_size(token_list)));
		aux_tree.tree = make_tree_cmd(aux_tree.aux, data);
		token_clear_list(&aux_tree.aux);
		return (aux_tree.tree);
	}
	divide_tree(&aux_tree, token_list, data);
	return (aux_tree.tree);
}
