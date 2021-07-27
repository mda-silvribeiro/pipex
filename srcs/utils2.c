/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 09:38:05 by mda-silv          #+#    #+#             */
/*   Updated: 2021/07/26 13:00:14 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	c;
	size_t	aux;

	c = (size * count);
	aux = 0;
	ptr = (void *)malloc(c);
	if (ptr)
	{
		while (aux < c)
		{
			((unsigned char *)ptr)[aux] = 0;
			aux++;
		}
		return (ptr);
	}
	else
		return (0);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	n;
	int		i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((i > 0 && s[i - 1] == c && s[i] != c) || (i == 0 && s[i] != c))
			n++;
		i++;
	}
	return (n);
}

static void	ft_fill(char **res, const char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (j < words)
	{
		k = 0;
		while (s[i] == c)
			i++;
		while (s[i + k] && s[i + k] != c)
			k++;
		res[j] = ft_calloc(sizeof(char), k + 1);
		k = 0;
		while (s[i] && s[i] != c)
			res[j][k++] = s[i++];
		res[j][k] = '\0';
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	res = ft_calloc(sizeof(char *), words + 1);
	if (!res)
		return (NULL);
	ft_fill(res, s, c, words);
	res[words] = 0;
	return (res);
}
