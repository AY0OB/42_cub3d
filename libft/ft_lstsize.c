/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:53:25 by amairia           #+#    #+#             */
/*   Updated: 2024/10/16 08:57:40 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	cpt;

	if (!lst)
		return (0);
	cpt = 1;
	while (lst->next)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}
