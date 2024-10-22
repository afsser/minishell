/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:21:47 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/09/11 16:49:52 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*clean_buffer(char *buffer);
static char	*ft_gnl_strjoin(const char *s1, const char *s2);
static char	*read_line(int fd, char *line);
static char	*treat_line(char *cache, char *line);

char	*get_next_line(int fd)
{
	static char	*cache[1024];
	char		*line;

	if (!BUFFER_SIZE || fd < 0)
		return (NULL);
	line = (char *)ft_calloc((1), sizeof(char));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	if (cache[fd])
	{
		line = ft_gnl_strjoin(line, cache[fd]);
		free(cache[fd]);
		cache[fd] = NULL;
	}
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	if (ft_strchr(line, '\n'))
		cache[fd] = ft_strdup(ft_strchr(line, '\n') + 1);
	return (treat_line(cache[fd], line));
}

static char	*read_line(int fd, char *line)
{
	int		rd;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (clean_buffer(buffer));
	rd = BUFFER_SIZE;
	while (!ft_strchr(line, '\n') && rd != 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
		{
			free(line);
			line = NULL;
			return (clean_buffer(buffer));
		}
		buffer[rd] = '\0';
		line = ft_gnl_strjoin(line, buffer);
	}
	free(buffer);
	buffer = NULL;
	return (line);
}

static char	*treat_line(char *cache, char *line)
{
	char	*temp;

	if (ft_strchr(line, '\n'))
	{
		temp = line;
		line = ft_calloc(ft_strlen(temp) - ft_strlen(cache) + 1, 1);
		if (!line)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		ft_strlcpy(line, temp, ft_strlen(temp) - ft_strlen(cache) + 1);
		free(temp);
		temp = NULL;
		return (line);
	}
	else if (ft_strlen(line))
		return (line);
	else
	{
		free(line);
		line = NULL;
		return (NULL);
	}
}

static char	*clean_buffer(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (NULL);
}

static char	*ft_gnl_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
	{
		free((void *)s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free((void *)s1);
	return (str);
}
