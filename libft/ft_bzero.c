/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:23:45 by amairia           #+#    #+#             */
/*   Updated: 2024/10/15 14:25:46 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*res;

	if (!s)
		return ;
	i = 0;
	res = (unsigned char *)s;
	while (i < n)
	{
		res[i] = 0;
		i++;
	}
}
