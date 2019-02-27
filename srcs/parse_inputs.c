/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:32:06 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:42:03 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parse_commands_built(char *excve, t_elem *envir, char **commands)
{
	char	**tab;

	tab = ft_strsplit_space(excve);
	if (is_point(excve) == 0)
		return (return_and_free(&tab));
	if (ft_dollar_first(excve, envir) == 0)
		return (return_and_free(&tab));
	if (ft_vag_first(excve, envir) == 0)
		return (return_and_free(&tab));
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

void	parse_commands(char *commands, t_elem *envir, char **command)
{
	int		i;
	char	*excve;

	i = 0;
	while (commands[i] == ' ' || commands[i] == '\t')
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
	char	*line;
	char	**commands;
	int		i;

	commands = NULL;
	if (get_next_line(0, &line) <= 0)
		return ;
	i = 0;
	if (line)
	{
		commands = ft_strsplit(line, ';');
		free(line);
		while (commands[i])
			parse_commands(commands[i++], envir, commands);
		ft_2dtabdel((void **)commands);
	}
	else
		free(line);
}
