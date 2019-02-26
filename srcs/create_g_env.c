/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envir->envi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:31:23 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 09:31:24 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/*
**LEAK OK
*/

int			len_env(char **envt)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (envt[++i])
		len++;
	return (len);
}

void		create_genv(char **env, t_elem *envir)
{
	int		i;

	if (!(envir->envi = (char **)malloc(sizeof(char *) * (len_env(env) + 1))))
		return ;
	i = -1;
	while (env[++i])
	{
		if (!(envir->envi[i] = ft_strdup(env[i])))
			exit_shell(envir);
	}
	envir->envi[i] = 0;
}
