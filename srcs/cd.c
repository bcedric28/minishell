/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 08:14:29 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:57:20 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	many_arguments(char **tab, char *home)
{
	ft_putendl("cd: too many arguments");
	if (home)
		free(home);
	ft_2dtabdel((void **)tab);
	return ;
}

void	cd_go_back(char **tab, t_elem *envir, char *home)
{
	char	*old;

	old = NULL;
	if (home)
		free(home);
	if (ft_strcmp(tab[1], "-") == 0)
	{
		old = ft_search_env("OLDPWD", envir);
		if (old != NULL)
		{
			change_dir(old, 1, envir);
			free(old);
		}
		else
			ft_putendl("OLDPWD is not set");
	}
	else
	{
		ft_putstr("cd : no such file or directory: ");
		ft_putendl(tab[1]);
	}
	ft_2dtabdel((void **)tab);
	return ;
}

void	only_cd(char *home, t_elem *envir, char **tab)
{
	if (home == NULL)
		ft_putendl("HOME is not set");
	else
		change_dir(home, 0, envir);
	free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_towards(char *home, char **tab, t_elem *envir)
{
	change_dir(tab[1], 0, envir);
	if (home)
		free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_builtin(char *cd, t_elem *envir)
{
	char	**tab;
	char	*home;

	tab = ft_strsplit_space(cd);
	home = ft_search_env("HOME", envir);
	if (tab[1] == NULL)
		return (only_cd(home, envir, tab));
	else
	{
		if (ft_strequ(tab[1], "--"))
			return (only_cd(home, envir, tab));
		else if (tab[1][0] == '-')
			return (cd_go_back(tab, envir, home));
		else if (tab[1][0] == '$' && tab[1][1])
			return (ft_dollar(tab, envir, home));
		else if (tab[1][0] == '~')
			return (cd_vag(tab, home, envir));
		else if (tab[2] == NULL)
			return (cd_towards(home, tab, envir));
	}
	return (many_arguments(tab, home));
}
