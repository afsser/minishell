/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:16:23 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/08/08 17:02:55 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	count;
	size_t	l_len;

	count = 0;
	l_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (*big && count < len)
	{
		i = 0;
		while (big[i] && big[i] == little[i] && count + i < len)
		{
			i++;
			if (i == l_len)
				return ((char *)big);
		}
		count++;
		big++;
	}
	return ((void *)0);
}
