/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:00:37 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:00:39 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_elem *envir)
{
	int	i;

	i = 0;
	while (envir->envi[i])
	{
		ft_putendl(envir->envi[i]);
		i++;
	}
}

void	env_bultin(char *env, t_elem *envir)
{
	char	**tab;

	tab = ft_strsplit_space(env);
	if (tab[1] == NULL)
		print_env(envir);
	else
	{
		ft_putstr("env: ");
		ft_putstr(env);
		ft_putendl(": No such file or directory");
	}
	ft_2dtabdel((void **)tab);
}
