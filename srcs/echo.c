/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 06:57:21 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 06:57:22 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	display_echo(char **tab_echo, int n)
{
	int i;
	int pos;

	i = n;
	while(tab_echo[i])
	{
		pos = 0;
		while(tab_echo[i][pos])
		{
			if (tab_echo[i][pos] == '"')
				pos++;
			else
			{
				ft_putchar(tab_echo[i][pos]);
				pos++;
			}
		}
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	echo_builtin(char *echo)
{
	int i;
	char *new_echo;
	char **tab_echo;

	i = -1;
	while(echo[++i])
		if (ft_isspace(echo[i]) == 1)
			break ;
	new_echo = ft_strsub(echo, i, ft_strlen(echo));
	tab_echo = ft_strsplit_space(new_echo);
	i = 0;
	if (!tab_echo[i])
	{
		ft_putendl("");
		return ;
	}
	if (ft_strcmp(tab_echo[i], "-n") == 0)
		i++;
	display_echo(tab_echo, i);
}

