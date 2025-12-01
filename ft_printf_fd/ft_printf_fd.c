/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:18:13 by ledupont          #+#    #+#             */
/*   Updated: 2025/11/23 19:29:08 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	printf_fd_putnbr(int n, int fd)
{
	int	l;

	l = 0;
	if (n == -2147483648)
	{
		l = l + write(fd, "-2147483648", 11);
		return (l);
	}
	if (n < 0)
	{
		n = n * -1;
		l = l + printf_fd_putchar('-', fd);
	}
	if (n >= 10)
	{
		l = l + printf_fd_putnbr(n / 10, fd);
		l = l + printf_fd_putnbr(n % 10, fd);
	}
	else
		l = l + printf_fd_putchar(n + '0', fd);
	return (l);
}

int	printf_fd_putnbrui(unsigned int n, int fd)
{
	int	l;

	l = 0;
	if (n >= 10)
	{
		l = l + printf_fd_putnbrui(n / 10, fd);
		l = l + printf_fd_putnbrui(n % 10, fd);
	}
	else
		l = l + printf_fd_putchar(n + '0', fd);
	return (l);
}

int	printf_fd_flags(va_list arg, char type, int fd)
{
	int	l;

	l = 0;
	if (type == 'c')
		l = l + printf_fd_putchar(va_arg(arg, int), fd);
	if (type == 's')
		l = l + printf_fd_putstr(va_arg(arg, char *), fd);
	if (type == 'p')
		l = l + printf_fd_putptr(va_arg(arg, void *), fd);
	if (type == 'd' || type == 'i')
		l = l + printf_fd_putnbr(va_arg(arg, int), fd);
	if (type == 'u')
		l = l + printf_fd_putnbrui(va_arg(arg, unsigned int), fd);
	if (type == 'X' || type == 'x')
		l = l + printf_fd_puthexa(va_arg(arg, unsigned int), type, fd);
	if (type == '%')
		l = l + write(fd, "%", 1);
	return (l);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	int		i;
	int		l;
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	i = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] != '%')
			l = l + write(fd, &s[i], 1);
		else if (s[i] == '%')
		{
			i++;
			l = l + printf_fd_flags(args, s[i], fd);
		}
		if (s[i])
			i++;
	}
	va_end(args);
	return (l);
}
