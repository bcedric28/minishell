/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:44:38 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/24 19:44:40 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countletter(char const *s)
{
	size_t	i;
	size_t	countletter;

	i = 0;
	countletter = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) == 0 && ft_isspace(s[i + 1]) == 0 && s[i + 1] != '\0')
			countletter++;
		else if (ft_isspace(s[i]) == 1 && ft_isspace(s[i - 1]) == 0)
			break ;
		i++;
	}
	countletter++;
	return (countletter);
}

static size_t	ft_countwords(char const *s)
{
	size_t	i;
	size_t	countwords;

	countwords = 0;
	i = 0;
	if (ft_isspace(s[0]) == 0)
	{
		countwords++;
		i++;
	}
	while (s[i])
	{
		if (ft_isspace(s[i]) == 0 && ft_isspace(s[i - 1]) == 1)
			countwords++;
		i++;
	}
	return (countwords);
}

static char		*ft_word(char const *s)
{
	char	*str;
	size_t	i;
	size_t	letter;

	letter = ft_countletter(s);
	str = ft_strnew(letter);
	i = 0;
	while (i < letter)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

static void		*ft_remove(char **str, int index)
{
	while (index >= 0)
	{
		free(str[index]);
		index--;
	}
	free(str);
	return (NULL);
}

char			**ft_strsplit_space(char const *s)
{
	size_t	i;
	size_t	k;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = 0;
	k = 0;
	str = (char**)malloc(sizeof(char*) * (ft_countwords(s)) + 1);
	if (str == NULL)
		return (NULL);
	while (s[k])
	{
		if ((ft_isspace(s[k]) == 1 && ft_isspace(s[k + 1]) == 0 && s[k + 1] != '\0') ||
			(k == 0 && ft_isspace(s[k]) == 0))
		{
			str[i] = ft_word((k == 0 && ft_isspace(s[k]) == 0) ? &s[k] : &s[k + 1]);
			if (str[i] == NULL)
				return (ft_remove(str, i));
			i++;
		}
		k++;
	}
	str[i] = 0;
	return (str);
}
