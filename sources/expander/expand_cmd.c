/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:12:01 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/10 20:47:13 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static char	*get_absolute_path(char *command, char **paths)
{
	int		i;
	int		full_path_len;
	char	*absolute_command;

	i = 0;
	absolute_command = NULL;
	while (paths[i])
	{
		full_path_len = ft_strlen(paths[i]) + ft_strlen(command) + 2;
		absolute_command = malloc(full_path_len);
		ft_strlcpy(absolute_command, paths[i], full_path_len);
		ft_strlcat(absolute_command, "/", full_path_len);
		ft_strlcat(absolute_command, command, full_path_len);
		if (access(absolute_command, F_OK | X_OK) == 0)
			break ;
		free(absolute_command);
		absolute_command = NULL;
		i++;
	}
	return (absolute_command);
}

char	*expand_command(char *command, t_env *envp_list)
{
	char	*path_env;
	char	*absolute_command;
	char	**paths;

	absolute_command = NULL;
	if (ft_strlen(command) > 0 && ft_strchr(command, '/') == NULL)
	{
		path_env = search_value(envp_list, "PATH");
		paths = ft_split(path_env, ':');
		free(path_env);
		absolute_command = get_absolute_path(command, paths);
		ft_free_split(paths);
	}
	if (!absolute_command)
		return (ft_strdup(command));
	return (absolute_command);
}
