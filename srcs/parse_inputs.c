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

int track_without_path(char **excve)
{
	struct stat file;

	if (lstat(excve[0], &file) == 0)
		return(execute_commands(excve[0], excve));
	return(0);
}

int	track_path(char **path, char **excve)
{
	int i;
	struct stat file;

	i = 0;
	if (lstat(excve[0], &file) == 0)
		return(execute_commands(excve[0], excve));
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], excve[0]);
		if (lstat(path[i], &file) == 0)
			return(execute_commands(path[i], excve));
		i++;
	}
	return (0);
}

void	main_commands(char *excve)
{
	int i;
	int j;
	char **path;
	char **execute_path;

	i = 0;
	j = 0;

	execute_path = ft_strsplit_space(excve);
	while(g_env[i])
	{
		j = 0;
		if (ft_strstr(g_env[i], "PATH") != NULL)
		{
			path = ft_strsplit(g_env[i], ':');
			path[0] = ft_strsub(path[0], 5, ft_strlen(path[0]));
			if (track_path(path, execute_path) == 0)
				ft_error(excve, 0);
			return ;
		}
		i++;
	}
	if (track_without_path(execute_path) == 0)
		ft_error(excve, 0);
}

void 	parse_commands_built(char *excve)
{
	char **tab;

	tab = ft_strsplit_space(excve);
	if (ft_strequ(tab[0], "echo"))
		echo_builtin(excve);
	/*else if (ft_strequ(tab[0], "cd"))
		excute_built_cd(excve);*/
	else if (ft_strequ(tab[0], "exit"))
		exit_shell();
	else if (ft_strequ(excve, "env"))
		env_bultin(excve);
	else if (ft_strequ(tab[0], "unsetenv"))
		unsetenv_builtin(excve);
	else if (ft_strequ(tab[0], "setenv"))
		setenv_builtin(excve);
	else
		main_commands(excve);
}

void parse_commands(char *commands)
{
	int i;
	char	*excve;

	i = 0;
	while(commands[i] == ' ' || commands[i] == '\t')
		i++;
	if (!commands[i])
		return ;
	excve = ft_strtrim(&commands[i]);
	parse_commands_built(excve);
}

void	wait_input()
{
	char *line;
	char **commands;
	int 	i;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return ;
	i = 0;
	if (line)
	{
		commands = ft_strsplit(line, ';');
		while(commands[i])
			parse_commands(commands[i++]);
	}
	free(line);
}