/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:02:03 by amairia           #+#    #+#             */
/*   Updated: 2024/10/14 20:58:45 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == 0)
	{
		return ((char *)(s + ft_strlen(s)));
	}
	i = 0;
	while (s[i])
		if (ch == s[i++])
			return ((char *)(s + i - 1));
	return (NULL);
}
