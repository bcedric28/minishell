/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:47:52 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:46:54 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *excve, int i)
{
	if (i == 1)
	{
		ft_putstr("env: ");
		ft_putstr(excve);
		ft_putendl(": No such file or directory");
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(excve);
	}
}
