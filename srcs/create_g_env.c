/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_g_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:31:23 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 09:31:24 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int			len_env(char **env)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (env[++i])
		len++;
	return (len);
}

void		create_g_env(char **env)
{
	int		i;

	g_env = (char **)malloc(sizeof(char *) * (len_env(env) + 1));
	i = -1;
	while (env[++i])
	{
		if (!(g_env[i] = ft_strdup(env[i])))
			exit_shell();
	}
}