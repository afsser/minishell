/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:38:42 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/07/25 14:04:00 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s;
	size_t	d;
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	d = d_len;
	s = 0;
	while (src[s] && d < size - 1 && size)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	if (size < d_len)
		return (s_len + size);
	else
		return (d_len + s_len);
}
