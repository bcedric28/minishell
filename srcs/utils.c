/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:09:15 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 14:23:17 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(path);
	}
	else
	{
		ft_putstr("Permission denied: ");
		ft_putendl(path);
	}
}

int		is_point(char *excve)
{
	char	**tab;

	tab = ft_strsplit_space(excve);
	if (ft_strcmp(tab[0], ".") == 0 || ft_strcmp(tab[0], "..") == 0)
	{
		ft_2dtabdel((void **)tab);
		return (0);
	}
	ft_2dtabdel((void **)tab);
	return (1);
}

void	return_and_free(char ***tab)
{
	if (tab)
		ft_2dtabdel((void**)*tab);
	return ;
}
