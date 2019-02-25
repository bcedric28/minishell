/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:47:52 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 09:47:53 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/*
**LEAK OK
*/

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
		ft_putstr("\033[92mminishell->\033[0m command not found: ");
		ft_putendl(excve);
	}
}