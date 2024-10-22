/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:20:14 by educastro         #+#    #+#             */
/*   Updated: 2024/10/15 13:26:07 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	index_to_close_parenthesis(t_token_list *token_list)
{
	int				index;
	int				close_parenthis_to_count;
	t_token_list	*aux;

	index = 1;
	close_parenthis_to_count = 1;
	aux = token_list;
	while (aux && close_parenthis_to_count > 0)
	{
		if (aux->token.type == OPEN_PARENTHESIS)
			close_parenthis_to_count++;
		else if (aux->token.type == CLOSE_PARENTHESIS)
			close_parenthis_to_count--;
		if (close_parenthis_to_count != 0)
			index++;
		aux = aux->next;
	}
	if (close_parenthis_to_count != 0)
		return (-1);
	return (index);
}

int	index_to_open_parenthesis(t_token_list *token_list)
{
	int				index;
	int				open_parenthis_to_count;
	t_token_list	*aux;

	index = 1;
	open_parenthis_to_count = 1;
	aux = token_list;
	while (aux && open_parenthis_to_count > 0)
	{
		if (aux->token.type == OPEN_PARENTHESIS)
			open_parenthis_to_count--;
		else if (aux->token.type == CLOSE_PARENTHESIS)
			open_parenthis_to_count++;
		if (open_parenthis_to_count != 0)
			index++;
		aux = aux->next;
	}
	if (open_parenthis_to_count != 0)
		return (-1);
	return (index);
}

t_tree	*get_tree(t_token_list *token_list, t_minishell *data)
{
	t_tree			*tree;
	t_token_list	*inverted_list;

	inverted_list = invert_list(token_get_sublist(token_list, 0, \
			token_list_size(token_list)));
	tree = make_tree(inverted_list, data);
	token_clear_list(&inverted_list);
	return (tree);
}

void	*free_tree(t_tree **tree)
{
	if (*tree == NULL)
		return (NULL);
	if ((*tree)->left)
		free_tree(&(*tree)->left);
	if ((*tree)->right)
		free_tree(&(*tree)->right);
	if ((*tree)->command)
		token_clear_list(&(*tree)->command);
	free(*tree);
	*tree = NULL;
	return (NULL);
}

void	*free_tree_all(t_tree **tree)
{
	if (*tree == NULL)
		return (NULL);
	if ((*tree)->left)
	{
		if ((*tree)->type == REDIRECT_HEREDOC)
			unlink((*tree)->left->command->token.lexeme);
		free_tree_all(&(*tree)->left);
	}
	if ((*tree)->right)
		free_tree_all(&(*tree)->right);
	if ((*tree)->command)
		token_clear_list(&(*tree)->command);
	free(*tree);
	*tree = NULL;
	return (NULL);
}
