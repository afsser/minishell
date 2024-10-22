/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:43:48 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:26:35 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_error_message(char *delimiter)
{
	int			length;
	char		*message_to_print;
	const char	*message[2] = {"Expecting delimiter (required '", "')"};

	length = ft_strlen(message[0]) + ft_strlen(delimiter) \
						+ ft_strlen(message[1]) + 1;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message[0], length);
	ft_strlcat(message_to_print, delimiter, length);
	ft_strlcat(message_to_print, message[1], length);
	ft_putendl_fd(message_to_print, STDERR_FILENO);
	free(message_to_print);
}

void	write_on_file(int fd, char *line, int need_to_expand, \
						t_env *envp_list)
{
	char	*expanded_line;

	if (need_to_expand)
	{
		expanded_line = expand_heredoc(line, envp_list);
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
	}
	else
		ft_putendl_fd(line, fd);
}

void	heredoc_fork(char *file_name, char *delimiter, t_env *envp_list)
{
	int		fd;
	int		need_to_expand;
	char	*line;
	char	*delimiter_without_quotes;

	need_to_expand = !(ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'));
	delimiter_without_quotes = remove_quotes(delimiter);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter_without_quotes, -1) == 0)
		{
			if (!line && g_signal == 0)
				print_error_message(delimiter);
			break ;
		}
		write_on_file(fd, line, need_to_expand, envp_list);
		free(line);
	}
	free(delimiter_without_quotes);
	close(fd);
}

char	*create_heredoc_name(char *delimiter)
{
	int				length;
	char			*prefix;
	char			*file_name;
	const char		*path = "/tmp/";
	unsigned long	num;

	num = (unsigned long) delimiter;
	prefix = ft_itoa((int) num);
	length = ft_strlen(path) + ft_strlen(prefix) + 1;
	file_name = malloc(length);
	ft_strlcpy(file_name, path, length);
	ft_strlcat(file_name, prefix, length);
	free(prefix);
	return (file_name);
}

char	*create_heredoc(char *delimiter, t_minishell *data)
{
	char	*file_name;

	file_name = create_heredoc_name(delimiter);
	heredoc_signals();
	heredoc_fork(file_name, delimiter, data->envs);
	if (g_signal == SIGINT)
	{
		unlink(file_name);
		free(file_name);
		file_name = NULL;
	}
	execution_signals(1);
	return (file_name);
}
