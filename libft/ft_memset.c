/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:01:12 by amairia           #+#    #+#             */
/*   Updated: 2024/10/14 16:02:52 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_int;
	size_t			i;
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = (unsigned char)c;
	s_int = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_int[i] = ch;
		i++;
	}
	return (s);
}
