/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:49:11 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/10/10 21:02:36 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	i = ft_strlen((char *) s) + 1;
	dup = malloc(i);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, i);
	return (dup);
}
