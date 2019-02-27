/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_g_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:53:10 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 12:53:27 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*only_path(int pos, t_elem *envir)
{
	char	*str;
	int		j;

	j = 0;
	while (envir->envi[pos][j])
	{
		if (j != 0 && envir->envi[pos][j - 1] == '=')
			break ;
		j++;
	}
	str = ft_strdup(&envir->envi[pos][j]);
	return (str);
}

char	*ft_search_env(char *path, t_elem *envir)
{
	int		i;
	char	**copy;

	copy = split_and_delete(envir);
	i = 0;
	while (copy[i])
	{
		if (ft_strequ(copy[i], path))
		{
			ft_2dtabdel((void**)copy);
			return (only_path(i, envir));
		}
		i++;
	}
	ft_2dtabdel((void**)copy);
	return (NULL);
}

char	**split_and_delete(t_elem *envir)
{
	char	**copy;
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	if (!(copy = (char**)malloc(sizeof(char*) * (len_env(envir->envi)) + 1)))
		return (NULL);
	while (envir->envi[++i])
	{
		j = -1;
		while (envir->envi[i][++j])
		{
			if (envir->envi[i][j + 1] != '\0' && envir->envi[i][j + 1] == '=')
			{
				copy[k] = ft_strsub(envir->envi[i], 0, j + 1);
				k++;
				break ;
			}
		}
	}
	copy[k] = 0;
	return (copy);
}

int		len_env(char **envt)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (envt[++i])
		len++;
	return (len);
}

void	create_genv(char **env, t_elem *envir)
{
	int	i;

	if (!(envir->envi = (char **)malloc(sizeof(char *)
					* (len_env(env) + 1))))
		return ;
	i = -1;
	while (env[++i])
	{
		if (!(envir->envi[i] = ft_strdup(env[i])))
			return ;
	}
	envir->envi[i] = 0;
}
