/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:25:31 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/08/18 15:47:52 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = (void *)(malloc(nmemb * size));
	if (!dest || (!nmemb && !size && ((nmemb * size) / size) != nmemb))
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
