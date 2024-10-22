/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:52:55 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/09/29 20:27:06 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printptr(unsigned long num)
{
	char	*base;
	int		print_len;

	base = HEXA_LOW;
	print_len = 0;
	if (num == 0)
		return (ft_printstr("(nil)"));
	if (num >= 16)
		print_len += ft_printptr(num / 16);
	else
		print_len += ft_printstr(LOW_HASH);
	print_len += ft_printchar(base[num % 16]);
	return (print_len);
}
