/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:25:39 by felipenasse       #+#    #+#             */
/*   Updated: 2023/08/04 13:19:53 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_intlen(long int ln)
{
	int	count;
	int	sign;

	sign = 1;
	count = 0;
	if (ln == 0)
	{
		return (1);
	}
	if (ln < 0)
	{
		ln = -ln;
		sign = -1;
	}
	while (ln != 0)
	{
		ln = ln / 10;
		count++;
	}
	return (count * sign);
}

static char	*alloc(long int ln, int len)
{
	char	*buffer;

	if (len < 0)
		len = -len;
	if (ln < 0)
	{
		buffer = malloc(len + 2);
		if (!buffer)
			return (0);
		buffer[0] = '-';
		buffer[len + 1] = '\0';
	}
	else
	{
		buffer = malloc(len + 1);
		if (!buffer)
			return (0);
		buffer[0] = '0';
		buffer[len] = '\0';
		len--;
	}
	return (buffer + len);
}

char	*ft_itoa(int n)
{
	long int	ln;
	char		*ptr;
	int			len;

	ln = n;
	len = ft_intlen(ln);
	ptr = alloc(ln, len);
	if (!ptr)
		return (0);
	if (ln < 0)
	{
		ln = -ln;
	}
	while (ln > 9)
	{
		*ptr = (ln % 10) + '0';
		ln /= 10;
		ptr--;
	}
	*ptr = ln + '0';
	if (len < 0)
		ptr--;
	return (ptr);
}
