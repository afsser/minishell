/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:11:21 by fcaldas-          #+#    #+#             */
/*   Updated: 2023/10/03 16:54:43 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	follow_str(const char *str, int i)
{
	if (str[i] == ' ' || str[i] == '+')
	{
		if (str[i + 1] == 'd' || str[i + 1] == 'i')
			return (1);
	}
	else if (str[i] == '#')
	{
		if (str[i + 1] == 'x' || str[i + 1] == 'X')
			return (1);
	}
	return (0);
}

int	print_var_continue(va_list args, const char *format, int i)
{
	int					print_len;
	unsigned long int	nbr;

	print_len = 0;
	if (format[i] == '#' && (format[i + 1] == 'x' || format[i + 1] == 'X'))
	{
		nbr = va_arg(args, unsigned int);
		if (format[i + 1] == 'x')
		{
			if (nbr != 0)
				print_len += ft_printstr(LOW_HASH);
			print_len += ft_putnbr_base(nbr, 'x');
		}
		if (format[i + 1] == 'X')
		{
			if (nbr != 0)
				print_len += ft_printstr(UP_HASH);
			print_len += ft_putnbr_base(nbr, 'X');
		}
	}
	return (print_len);
}

int	print_var(va_list args, const char *format, int i)
{
	int	print_len;

	print_len = 0;
	if (format[i] == 'c')
		print_len += ft_printchar(va_arg(args, int));
	else if (format[i] == 's')
		print_len += ft_printstr(va_arg(args, char *));
	else if (format[i] == 'p')
		print_len += ft_printptr(va_arg(args, unsigned long int));
	else if (format[i] == ' ' && (format[i + 1] == 'd' || format[i + 1] == 'i'))
		print_len += ft_printnbr(va_arg(args, int), 1, 0);
	else if (format[i] == '+' && (format[i + 1] == 'd' || format[i + 1] == 'i'))
		print_len += ft_printnbr(va_arg(args, int), 0, 1);
	else if (format[i] == 'd' || format[i] == 'i')
		print_len += ft_printnbr(va_arg(args, int), 0, 0);
	else if (format[i] == 'u')
		print_len += ft_putnbr_base(va_arg(args, unsigned int), format[i]);
	else if (format[i] == '%')
		print_len += ft_printchar('%');
	else if (format[i] == 'x' || format[i] == 'X')
		print_len += ft_putnbr_base(va_arg(args, unsigned int), format[i]);
	else
		print_len += print_var_continue(args, format, i);
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_len;

	va_start(args, str);
	i = 0;
	print_len = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != 0)
		{
			print_len = print_len + print_var(args, str, i + 1);
			i++;
			i += follow_str(str, i);
		}
		else
			print_len = print_len + ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}
