/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:10:17 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:10:18 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_echo_vag(char *vag, t_elem *envir)
{
	char	*home;

	home = ft_search_env("HOME", envir);
	if (home == NULL)
	{
		ft_putstr("HOME is not set");
		return ;
	}
	if (!vag[1])
		ft_putstr(home);
	else if (vag[1] == '/')
	{
		vag = ft_strjoin(home, &vag[1]);
		ft_putstr(vag);
		free(vag);
	}
	else
		ft_putstr("minishell: not enough directory stack entries");
	free(home);
	return ;
}

void	display_echo_env(int i, t_elem *envir)
{
	int	j;

	j = 0;
	while (envir->envi[i][j])
	{
		if (envir->envi[i][j - 1] == '=')
			break ;
		j++;
	}
	ft_putstr(&envir->envi[i][j]);
}

void	display_echo(char **tab_echo, int i, int n, t_elem *envir)
{
	int	pos;
	int	condition;

	if (n == 1)
		i++;
	while (tab_echo[++i])
	{
		pos = 0;
		while (tab_echo[i][pos])
		{
			condition = condition_loop(pos, i, tab_echo, envir);
			if (condition == 1)
				break ;
			else
				pos++;
		}
		ft_putchar(' ');
	}
	if (n == 0)
		ft_putchar('\n');
}
