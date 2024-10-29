/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 02:19:54 by educastro         #+#    #+#             */
/*   Updated: 2024/10/29 18:40:47 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*ft_replacer(char *path, char *home)
{
	char	*new_path;
	int		new_path_len;

	new_path_len = 1 + ft_strlen(path) - ft_strlen(home);
	new_path = malloc(new_path_len + 1);
	if (!new_path)
		return (NULL);
	ft_strlcpy(new_path, "~", new_path_len + 1);
	ft_strlcat(new_path, path + ft_strlen(home), new_path_len + 1);
	return (new_path);
}

static char	*replace_home_path(t_env *env_list)
{
	char	*home;
	char	*path;
	char	*new_path;

	new_path = NULL;
	path = search_value(env_list, "PWD");
	if (!path)
		return (NULL);
	home = search_value(env_list, "HOME");
	if (!home)
	{
		free(path);
		return (NULL);
	}
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
		new_path = ft_replacer(path, home);
	else
		new_path = ft_strdup(path);
	free(path);
	free(home);
	return (new_path);
}

char	*get_line_to_readline(t_env *env_list)
{
	int			i;
	int			length;
	char		*line;
	const char	*path;
	const char	*to_print[] = {ORANGE, NULL, RST, GREEN, " ──> ", RST, NULL};

	i = 0;
	length = 0;
	path = replace_home_path(env_list);
	if (!path)
		return (NULL);
	to_print[1] = path;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	free((char *)path);
	return (line);
}

int	str_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
