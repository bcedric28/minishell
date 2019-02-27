/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:32:06 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 09:32:07 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/*
**Wait_input : fonction qui permet de lire ce que l'on m'envoie en arguments
**je fais un ft_strsplit pour savoir si il y a plusieur commande a excecuter;
**
**parse_commande : prend commande par commande et enleve les espace devant et
**derriere puis elle fait appel a parse_command_built cette fonction 
**permet de verifier si la command que l'on me demande d'executer n'est
**pas une fonction de mes builtin, si c'est le cas j'appel
**la fonction en question ou sinon je fait appel a main_commands.
**
**Main_command me permet de split ma commande en question avec les argument
**passer. Je verifie d'abord grace a track_path si la commande que l'on ma
**envoyer n'est pas un binaire deja existant dans un dossier courant.
**si ce n'est pas le cas je verifie si le binaire existe si il existe
**j'execute la commande ou sinon je renvoie une erreur
*/

/*
**leak is ok
*/

int track_without_path(char **excve, t_elem *envir)
{
	struct stat file;

	if (lstat(excve[0], &file) == 0)
		return(execute_commands(excve[0], excve, envir));
	return(0);
}

int	track_path(char **path, char **excve, t_elem *envir)
{
	int i;
	struct stat file;
	char *tmp;

	i = 0;
	if (lstat(excve[0], &file) == 0)
		return(execute_commands(excve[0], excve, envir));
	while(path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(tmp, excve[0]);
		free(tmp);
		if (lstat(path[i], &file) == 0)
			return(execute_commands(path[i], excve, envir));
		i++;
	}
	return (0);
}

void	main_commands(char *excve, t_elem *envir)
{
	int i;
	int j;
	char **path;
	char **execute_path;
	char *tmp;

	i = -1;
	execute_path = ft_strsplit_space(excve);
	while(envir->envi[++i])
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

void	ft_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(path);
	}
	else
	{
		ft_putstr("Permission denied: ");
		ft_putendl(path);
	}
}

int		ft_dollar_first(char *dollar, t_elem *envir)
{
	char **tab_dollar;
	char *path;

	path = NULL;
	if (ft_strncmp(dollar, "$", 1) != 0)
		return (1);
	tab_dollar = ft_strsplit(dollar, '$');
	path = ft_search_env(tab_dollar[0], envir);
	if (path == NULL)
	{
		ft_2dtabdel((void**)tab_dollar);
		return (0);
	}
	ft_access(path);
	free(path);
	ft_2dtabdel((void**)tab_dollar);
	return (0);
}

int 	ft_vag_first(char *vag, t_elem *envir)
{
	char *path;

	if (ft_strcmp(vag, "~") == 0)
	{
		path = ft_search_env("HOME", envir);
		if (path == 0)
		{
			ft_putendl("HOME is not set");
			return (0);
		}
		ft_access(path);
		return (0);
	}
	return(1);
}

int 	is_point(char *excve)
{
	char **tab;

	tab = ft_strsplit_space(excve);
	if (ft_strcmp(tab[0], ".") == 0 || ft_strcmp(tab[0], "..") == 0)
	{
		ft_2dtabdel((void **)tab);
		return (0);
	}
	ft_2dtabdel((void **)tab);
	return (1);
}

void	return_and_free(char ***tab)
{
	if (tab)
		ft_2dtabdel((void**)*tab);
	return ;
}

void 	parse_commands_built(char *excve, t_elem *envir, char **commands)
{
	char **tab;

	tab = ft_strsplit_space(excve);
	if (is_point(excve) == 0)
		return(return_and_free(&tab));
	if (ft_dollar_first(excve, envir) == 0)
		return(return_and_free(&tab));
	if (ft_vag_first(excve, envir) == 0)
		return(return_and_free(&tab));
	else if (ft_strequ(tab[0], "echo"))
		echo_builtin(excve, envir);
	else if (ft_strequ(tab[0], "cd"))
		cd_builtin(excve, envir);
	else if (ft_strequ(tab[0], "exit"))
		exit_shell(envir, commands);
	else if (ft_strequ(tab[0], "env"))
		env_bultin(excve, envir);
	else if (ft_strequ(tab[0], "unsetenv"))
		unsetenv_builtin(excve, envir);
	else if (ft_strequ(tab[0], "setenv"))
		setenv_builtin(excve, envir);
	else
		main_commands(excve, envir);
	ft_2dtabdel((void**)tab);
}

void parse_commands(char *commands, t_elem *envir, char **command)
{
	int 	i;
	char	*excve;

	i = 0;
	while(commands[i] == ' ' || commands[i] == '\t')
		i++;
	if (!commands[i])
		return ;
	excve = ft_strtrim(&commands[i]);
	parse_commands_built(excve, envir, command);
	if (excve)
	{
		free(excve);
		excve = NULL;
	}
}

void	wait_input(t_elem *envir)
{
	char *line;
	char **commands;
	int 	i;

	commands = NULL;
	if (get_next_line(0, &line) <= 0)
		return ;
	i = 0;
	if (line)
	{
		commands = ft_strsplit(line, ';');
		free(line);
		while(commands[i])
			parse_commands(commands[i++], envir, commands);
		ft_2dtabdel((void **)commands);
	}
	else
		free(line);
}