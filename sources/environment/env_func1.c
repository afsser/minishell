/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:11:02 by educastro         #+#    #+#             */
/*   Updated: 2024/10/10 20:37:40 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/environment.h"

t_env	*env_create_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = ft_strdup(name);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	env_insert_node(t_env **head, char *name, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	if (!head || !name)
		return ;
	if (att_existing_value(*head, name, value) == 1)
		return ;
	new_node = env_create_node(name, value);
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env	*env_create_list(char *envp[])
{
	int		idx[3];
	char	*name;
	char	*value;
	t_env	*head;

	head = NULL;
	idx[0] = -1;
	while (envp && envp[++idx[0]])
	{
		idx[1] = 0;
		while (envp[idx[0]][idx[1]] != '=')
			idx[1]++;
		name = malloc(sizeof(char) * (idx[1] + 1));
		idx[2] = idx[1] + 1;
		while (envp[idx[0]][idx[2]] != '\0')
			idx[2]++;
		value = malloc(sizeof(char) * (idx[2] + 1));
		ft_strlcpy(name, envp[idx[0]], idx[1] + 1);
		ft_strlcpy(value, envp[idx[0]] + idx[1] + 1, idx[2]);
		env_insert_node(&head, name, value);
		free(name);
		free(value);
	}
	return (head);
}

char	**create_envp(t_env *head)
{
	int			i;
	int			full_size;
	char		**new_envp;
	t_env		*temp;

	i = 0;
	temp = head;
	new_envp = ft_calloc(sizeof(char *), envp_list_size(head));
	while (temp)
	{
		if (ft_strncmp(temp->name, "?", -1) != 0)
		{
			full_size = ft_strlen(temp->name) + ft_strlen(temp->value) + 2;
			new_envp[i] = malloc(sizeof(char) * full_size);
			ft_strlcpy(new_envp[i], temp->name, full_size);
			if (temp->value)
			{
				ft_strlcat(new_envp[i], "=", full_size);
				ft_strlcat(new_envp[i], temp->value, full_size);
			}
			i++;
		}
		temp = temp->next;
	}
	return (new_envp);
}

void	env_delete_value(t_env **head, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	while (temp != NULL && name)
	{
		if (ft_strncmp(temp->name, name, -1) == 0)
		{
			if (prev == NULL)
				*head = temp->next;
			else
				prev->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}
