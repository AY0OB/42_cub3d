/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:42:50 by amairia           #+#    #+#             */
/*   Updated: 2024/10/12 22:57:18 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;

	res = ft_strlen(src);
	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size > res)
	{
		dst[i] = 0;
	}
	else
		dst[i - 1] = 0;
	return (res);
}
