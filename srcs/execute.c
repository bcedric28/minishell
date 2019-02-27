/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:08:13 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:08:14 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_commands(char *execute, char **execute_path, t_elem *envir)
{
	pid_t		pid;
	struct stat	file;

	pid = fork();
	lstat(execute, &file);
	if ((S_ISREG(file.st_mode)) && !(file.st_mode & S_IXUSR))
	{
		ft_putstr(execute);
		ft_putendl(": Permission denied.");
		kill(pid, SIGINT);
		return (1);
	}
	if (pid == 0)
		execve(execute, execute_path, envir->envi);
	else if (pid < 0)
		return (-1);
	wait(&pid);
	return (1);
}

void	main_commands(char *excve, t_elem *envir)
{
	int		i;
	int		j;
	char	**path;
	char	**execute_path;
	char	*tmp;

	i = -1;
	execute_path = ft_strsplit_space(excve);
	while (envir->envi[++i])
	{
		j = 0;
		if (ft_strstr(envir->envi[i], "PATH") != NULL)
		{
			path = ft_strsplit(envir->envi[i], ':');
			tmp = path[0];
			path[0] = ft_strsub(tmp, 5, ft_strlen(tmp));
			free(tmp);
			if (track_path(path, execute_path, envir) == 0)
				ft_error(excve, 0);
			ft_2dtabdel((void **)path);
			ft_2dtabdel((void **)execute_path);
			return ;
		}
	}
	if (track_without_path(execute_path, envir) == 0)
		ft_error(excve, 0);
	ft_2dtabdel((void **)execute_path);
}
