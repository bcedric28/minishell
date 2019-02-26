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
**LEAK OK AND NORME OK
*/

void	add_env(char **tab)
{
	char **copy;
	char *tmp;
	int i;

	if (!(copy = (char**)malloc(sizeof(char*) *
		((len_env(g_env) + 1) + 1))))
		return ;
	i = 0;
	while (g_env[i])
	{
			copy[i] = ft_strdup(g_env[i]);
			i++;
	}
	tmp = ft_strjoin(tab[1], "=");
	if (tab[2])
		copy[i] = ft_strjoin(tmp, tab[2]);
	else
		copy[i] = ft_strdup(tmp);
	free(tmp);
	g_env = copy;
}

void	on_setenv(char **tab)
{
	char **copy;
	char *tmp;
	int i;

	i = 0;
	copy = split_and_delete();
	while (copy[i])
	{
		if (ft_strequ(copy[i], tab[1]))
		{
			free(g_env[i]);
			tmp = ft_strjoin(tab[1], "=");
			if (tab[2])
				g_env[i] = ft_strjoin(tmp, tab[2]);
			else
				g_env[i] = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		i++;
	}
	add_env(tab);
	ft_2dtabdel((void**)copy);
}

void 	setenv_builtin(char *setenv)
{
	char **tab;
	int i;

	tab = ft_strsplit_space(setenv);
	i = len_env(tab);
	if (i >= 4)
		ft_putendl("setenv: Too many arguments");
	else if (tab[1] == NULL)
		print_env();
	else
		on_setenv(tab);
	ft_2dtabdel((void**)tab);
}