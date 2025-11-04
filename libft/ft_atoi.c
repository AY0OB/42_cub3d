/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:33:10 by amairia           #+#    #+#             */
/*   Updated: 2024/10/14 17:12:19 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	tst_ng;

	if (!nptr)
		return (0);
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	tst_ng = 1;
	if (nptr[i] == '-')
	{
		i++;
		tst_ng = -1;
	}
	else if (nptr[i] == '+')
		i++;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10;
		res += nptr[i++] - '0';
	}
	return (res * tst_ng);
}
