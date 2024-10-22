/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:57:43 by nasser            #+#    #+#             */
/*   Updated: 2024/10/09 15:36:10 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_words(const char *s, char c)
{
	int	trigger;
	int	i;

	trigger = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && !trigger)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*word_dup(const char *s, int start, int finish, char **split)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(sizeof(char), (finish - start + 1));
	if (!word)
	{
		while (split)
		{
			free(split[i]);
			i++;
		}
		free(split);
		return (0);
	}
	i = 0;
	while (start < finish)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		start;

	split = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			split[j] = word_dup(s, start, i, split);
			start = -1;
			j++;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
