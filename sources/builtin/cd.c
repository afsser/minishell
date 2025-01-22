/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:22:44 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/01/22 19:59:08 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

static void	cd_print_error_message(char *folder)
{
	ft_putstr_fd("ERROR: cd: ", STDERR_FILENO);
	ft_putstr_fd(folder, STDERR_FILENO);
	if (access(folder, F_OK) != 0)
		ft_putendl_fd(": file or directory does not exist", STDERR_FILENO);
	else if (access(folder, X_OK) != 0)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": An unknown error occurred", STDERR_FILENO);
}

static int	add_envp_list(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (1);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

static int	set_env(char *name, char *value, t_minishell *data)
{
	if (att_existing_value(data->envs, name, value) == 0)
		add_envp_list(&data->envs, name, value);
	return (0);
}

static int	builtin_cd_util(char *args[], t_minishell *data, char **path)
{
	char	*home;

	if (args[1] && args[2])
	{
		ft_putendl_fd("ERROR: cd: Too many arguments", STDERR_FILENO);
		return (1);
	}
	home = search_value(data->envs, "HOME");
	if (!home[0])
	{
		ft_putendl_fd("ERROR: cd: HOME not defined", STDERR_FILENO);
		free(home);
		return (1);
	}
	*path = NULL;
	if (args[1] == NULL)
		*path = ft_strdup(home);
	else if (args[1] && ft_strchr(args[1], '~'))
		*path = ft_strjoin(home, args[1] + 1);
	else
		*path = ft_strdup(args[1]);
	free (home);
	return (0);
}

int	builtin_cd(char *args[], t_minishell *data)
{
	char	*path;
	char	*oldpwd;

	if (builtin_cd_util(args, data, &path) == 1)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		oldpwd = search_value(data->envs, "PWD");
	if (chdir(path) == -1)
	{
		cd_print_error_message(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	free(path);
	set_env("OLDPWD", oldpwd, data);
	free(oldpwd);
	path = getcwd(NULL, 0);
	set_env("PWD", path, data);
	free(path);
	return (0);
}
