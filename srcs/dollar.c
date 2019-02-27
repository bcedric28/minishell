/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:03:08 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:03:11 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar_complement(char **tab_dollar, char **dollar, t_elem *envir)
{
	char	*home;

	home = ft_search_env("HOME", envir);
	if (home == NULL)
	{
		ft_putendl("HOME is not set");
		ft_2dtabdel((void **)tab_dollar);
		ft_2dtabdel((void **)dollar);
		return ;
	}
	change_dir(home, 0, envir);
	ft_2dtabdel((void **)tab_dollar);
	ft_2dtabdel((void **)dollar);
	free(home);
	return ;
}

void	ft_dollar(char **dollar, t_elem *envir, char *home)
{
	char	**tab_dollar;
	char	*path;

	path = NULL;
	if (home)
		free(home);
	tab_dollar = ft_strsplit(dollar[1], '$');
	if (ft_strcmp(tab_dollar[0], "~") == 0)
		return (ft_dollar_complement(tab_dollar, dollar, envir));
	path = ft_search_env(tab_dollar[0], envir);
	if (path == NULL)
	{
		ft_2dtabdel((void**)tab_dollar);
		ft_2dtabdel((void **)dollar);
		return ;
	}
	else
	{
		change_dir(path, 0, envir);
		ft_2dtabdel((void**)tab_dollar);
		ft_2dtabdel((void **)dollar);
		free(path);
	}
	return ;
}

int		ft_dollar_first(char *dollar, t_elem *envir)
{
	char	**tab_dollar;
	char	*path;

	path = NULL;
	if (ft_strncmp(dollar, "$", 1) != 0)
		return (1);
	tab_dollar = ft_strsplit(dollar, '$');
	path = ft_search_env(tab_dollar[0], envir);
	if (path == NULL)
	{
		ft_2dtabdel((void**)tab_dollar);
		return (0);
	}
	ft_access(path);
	free(path);
	ft_2dtabdel((void**)tab_dollar);
	return (0);
}
