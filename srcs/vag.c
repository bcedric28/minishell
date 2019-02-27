/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vag.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:05:01 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 14:22:40 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_vag_suits(char *home, char **tab, t_elem *envir)
{
	char *tmp;

	if (home == NULL)
	{
		ft_putendl("HOME is not set");
		free(home);
		ft_2dtabdel((void**)tab);
		return ;
	}
	else
	{
		tmp = tab[1];
		tab[1] = ft_strjoin(home, &tmp[1]);
		free(tmp);
	}
	change_dir(tab[1], 0, envir);
	free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_vag(char **tab, char *home, t_elem *envir)
{
	if (!tab[1][1])
	{
		if (home == NULL)
			ft_putendl("HOME is not set");
		else
			change_dir(home, 0, envir);
		ft_2dtabdel((void**)tab);
		return ;
	}
	if (tab[1][1] == '/')
		return (cd_vag_suits(home, tab, envir));
}

int		ft_vag_first(char *vag, t_elem *envir)
{
	char	*path;

	if (ft_strcmp(vag, "~") == 0)
	{
		path = ft_search_env("HOME", envir);
		if (path == 0)
		{
			ft_putendl("HOME is not set");
			return (0);
		}
		ft_access(path);
		return (0);
	}
	return (1);
}
