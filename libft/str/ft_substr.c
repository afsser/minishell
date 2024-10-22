/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:20:10 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/07/27 19:17:25 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start || *s == '\0')
	{
		sub = malloc(1);
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s) - start > len)
		i = len + 1;
	else
		i = ft_strlen(s) - start + 1;
	sub = (char *)malloc(i);
	if (!sub)
		return (0);
	ft_strlcpy(sub, (s + start), i);
	return (sub);
}
