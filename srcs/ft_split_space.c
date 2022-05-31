/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltsaros <baltsaros@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:33:11 by abuzdin           #+#    #+#             */
/*   Updated: 2022/05/31 17:47:04 by baltsaros        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_charset(char c, char *charset)
{
	unsigned int	i;

	i = 0;
	
	if (!charset)
		return (0);
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		++i;
	}
	return (0);
}

static size_t	check_str(char const *s, char *charset)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && check_charset(s[i], charset))
			++i;
		if (s[i])
		{
			++n;
			printf("n is %lu, i is %lu\n", n, i);
		}
		if (s[i] == '"' || s[i] == '\'')
		{
			++i;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				++i;
			// ++i;
		}
		while (s[i] && !(check_charset(s[i], charset)))
			++i;
	}
	return (n);
}

static char	**ft_create_str(char **spl, char const *s, int i, char *charset)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start])
	{
		end = 0;
		while (s[start + end] && check_charset(s[start + end], charset))
			++start;
		while (s[start + end] && !check_charset(s[start + end], charset) && s[start + end] != '"' && s[start + end] != '\'')
			++end;
		if (s[start + end] && (s[start + end] == '"' || s[start + end] == '\''))
		{
			++end;
			while (s[start + end] && s[start + end] != '"' && s[start + end] != '\'')
				++end;
			++end;
		}
		if (end > 0)
		{
			spl[i] = ft_strndup(s + start, end);
			if (!spl[i])
			{
				ft_free(spl);
				return (NULL);
			}
			++i;
			start = start + end;
		}
	}
	spl[i] = NULL;
	return (spl);
}

char	**ft_split_space(char const *s, char *charset)
{
	char	**spl;
	size_t	size;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	size = check_str(s, charset);
	printf("words to create is %lu\n", size);
	spl = (char **)malloc(sizeof(*spl) * (size + 1));
	if (!spl)
		return (NULL);
	spl = ft_create_str(spl, s, i, charset);
	return (spl);
}
