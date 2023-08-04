/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:13:48 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/04 15:23:28 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

char	*ft_putword(const char *s, char c)
{
	int		j;
	char	*word;

	j = 0;
	while (*s && *s == c)
		s++;
	while (s[j] && s[j] != c)
		j++;
	word = malloc(sizeof(char) * (j + 1));
	if (!word)
		return (0);
	j = 0;
	while (s[j] && s[j] != c)
	{
		word[j] = s[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

void	ft_free(int i, char **new)
{
	while (i > 0)
	{
		free(new[i - 1]);
		i--;
	}
	free(new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		wc;
	int		i;

	if (!s)
		return (0);
	i = 0;
	wc = ft_wordcount(s, c);
	new = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!new)
		return (NULL);
	while (i < wc)
	{
		while (*s && *s == c)
			s++;
		new[i] = ft_putword(s, c);
		if (!new[i])
			ft_free(i, new);
		while (*s && *s != c)
			s++;
		i++;
	}
	new[i] = NULL;
	return (new);
}
