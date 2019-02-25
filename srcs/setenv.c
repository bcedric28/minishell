/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:17:20 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 11:17:22 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**LEAK OK
*/

void	delete_and_replace(int pos, char **tab)
{
	int i;
	char **copy;

	copy = (char**)malloc(sizeof(char*) * (len_env(g_env)) + 1);
	i = 0;
	while(g_env[i])
	{
		if (i == pos)
		{
			copy[i] = ft_strdup(tab[1]);
			copy[i] = ft_strjoin(copy[i], "=");
			if (tab[2] != NULL)
				copy[i] = ft_strjoin(copy[i], tab[2]);
		}
		else
			copy[i] = ft_strdup(g_env[i]);
		free(g_env[i++]);
	}
	g_env = copy;
}

void	add_env(char **tab)
{
	char **copy;
	int i;

	copy = (char**)malloc(sizeof(char*) * ((len_env(g_env) + 1) + 1));
	i = 0;
	while(g_env[i])
	{
			copy[i] = ft_strdup(g_env[i]);
			free(g_env[i++]);
	}
	copy[i] = ft_strdup(tab[1]);
	copy[i] = ft_strjoin(copy[i], "=");
	if (tab[2] != NULL)
		copy[i] = ft_strjoin(copy[i], tab[2]);
	g_env = copy;
}

void 	setenv_builtin(char *setenv)
{
	char **tab;
	char **copy;
	int i;

	copy = NULL;
	tab = ft_strsplit_space(setenv);
	if (tab[3] != NULL)
		ft_putendl("setenv: Too many arguments");
	else if (tab[1] == NULL)
		print_env();
	else
	{
		i = 0;
		copy = split_and_delete();
		while(copy[i])
		{
			if (ft_strequ(copy[i], tab[1]))
			{
				delete_and_replace(i, tab);
				return ;
			}
			i++;
		}
		add_env(tab);
	}
	ft_2dtabdel((void**)tab);
	if (copy)
		ft_2dtabdel((void**)copy);
}