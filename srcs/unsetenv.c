/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 08:47:42 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:48:56 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(int pos, t_elem *envir)
{
	int		i;
	int		k;
	char	**copy;

	if (!(copy = (char**)ft_memalloc(sizeof(char*) * (len_env(envir->envi)))))
		return ;
	i = 0;
	k = 0;
	while (envir->envi[i])
	{
		if (i == pos)
			i++;
		else
		{
			copy[k] = ft_strdup(envir->envi[i]);
			i++;
			k++;
		}
	}
	copy[k] = 0;
	ft_tabdel(&(envir->envi));
	envir->envi = copy;
}

void	befor_delete_env(t_elem *envir, char **tab, char **copy)
{
	int k;
	int j;
	int i;

	j = 0;
	k = 0;
	while (tab[++j])
	{
		i = -1;
		while (copy[++i])
		{
			if (ft_strequ(copy[i], tab[j]))
			{
				delete_env(i - k, envir);
				k++;
			}
		}
	}
}

void	unsetenv_builtin(char *unsetenv, t_elem *envir)
{
	char	**tab;
	char	**copy;

	copy = NULL;
	tab = ft_strsplit_space(unsetenv);
	if (tab[1] == NULL)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		copy = split_and_delete(envir);
		befor_delete_env(envir, tab, copy);
		ft_2dtabdel((void **)copy);
	}
	ft_2dtabdel((void **)tab);
	return ;
}
