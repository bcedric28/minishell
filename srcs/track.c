/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:07:10 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:07:11 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		track_without_path(char **excve, t_elem *envir)
{
	struct stat file;

	if (lstat(excve[0], &file) == 0)
		return (execute_commands(excve[0], excve, envir));
	return (0);
}

int		track_path(char **path, char **excve, t_elem *envir)
{
	int			i;
	struct stat	file;
	char		*tmp;

	i = 0;
	if (lstat(excve[0], &file) == 0)
		return (execute_commands(excve[0], excve, envir));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(tmp, excve[0]);
		free(tmp);
		if (lstat(path[i], &file) == 0)
			return (execute_commands(path[i], excve, envir));
		i++;
	}
	return (0);
}
