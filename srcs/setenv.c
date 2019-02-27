/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:17:20 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:43:59 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tabdel(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void	add_env(char **tab, t_elem *envir)
{
	char	**copy;
	char	*tmp;
	int		i;

	if (!(copy = (char**)malloc(sizeof(char*) *
		((len_env(envir->envi) + 1) + 1))))
		return ;
	i = 0;
	while (envir->envi[i])
	{
		copy[i] = ft_strdup(envir->envi[i]);
		i++;
	}
	tmp = ft_strjoin(tab[1], "=");
	if (tab[2])
		copy[i] = ft_strjoin(tmp, tab[2]);
	else
		copy[i] = ft_strdup(tmp);
	copy[++i] = 0;
	free(tmp);
	ft_tabdel(&(envir->envi));
	envir->envi = copy;
}

void	on_setenv(char **tab, t_elem *envir)
{
	char	**copy;
	char	*tmp;
	int		i;

	i = 0;
	copy = split_and_delete(envir);
	while (copy[i])
	{
		if (ft_strequ(copy[i], tab[1]))
		{
			free(envir->envi[i]);
			tmp = ft_strjoin(tab[1], "=");
			if (tab[2])
				envir->envi[i] = ft_strjoin(tmp, tab[2]);
			else
				envir->envi[i] = ft_strdup(tmp);
			free(tmp);
			ft_2dtabdel((void**)copy);
			return ;
		}
		i++;
	}
	add_env(tab, envir);
	ft_2dtabdel((void**)copy);
}

void	setenv_builtin(char *setenv, t_elem *envir)
{
	char	**tab;
	int		i;

	tab = ft_strsplit_space(setenv);
	i = len_env(tab);
	if (i >= 4)
		ft_putendl("setenv: Too many arguments");
	else if (tab[1] == NULL)
		print_env(envir);
	else
	{
		i = -1;
		while (tab[1][++i])
			if (ft_isalnum(tab[1][i]) == 0)
			{
				ft_putstr("setenv: Variable ");
				ft_putendl("name must contain alphanumeric characters.");
				ft_2dtabdel((void**)tab);
				return ;
			}
		on_setenv(tab, envir);
	}
	ft_2dtabdel((void**)tab);
}
