/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:41:17 by bcedric           #+#    #+#             */
/*   Updated: 2018/10/08 18:12:22 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **ap)
{
	if (*ap != NULL && ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
	else
		return ;
}
