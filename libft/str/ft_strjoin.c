/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipenasser <felipenasser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:31:02 by felipenasse       #+#    #+#             */
/*   Updated: 2023/07/29 16:24:51 by felipenasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (0);
	*ptr = '\0';
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcpy(ptr + s1_len, s2, s2_len + 1);
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s1[] = "bom ";
// 	char	s2[] = "dia";

// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }