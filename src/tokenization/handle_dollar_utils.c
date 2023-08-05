/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:08:46 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 18:25:32 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	ft_strnstr_mod(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (needle[n] == '\0')
		return (-1);
	while (i < len && haystack[i])
	{
		while (haystack[i + n] == needle[n] && needle[n] != '\0' && n + i < len)
			n++;
		if (needle[n] == '\0')
			return (i);
		i++;
		n = 0;
	}
	return (-1);
}

int	num_of_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	is_there_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

void	get_search_term(int *i, int *qty, t_token *current, char **search_term)
{
	int		size;
	char	*delim_chars;

	size = 0;
	delim_chars = " \t$;|\n\\.=";
	if (ft_isdigit(current->data[*i]) || current->data[(*i)] == '$'
		|| current->data[(*i)] == '?')
	{
		size++;
		(*i)++;
	}
	else
	{
		while (!ft_strchr(delim_chars, current->data[*i]))
		{
			size++;
			(*i)++;
		}
	}
	(*qty)--;
	*search_term = (char *)malloc(sizeof(char) * size);
	if (!search_term)
		return ;
	*search_term = ft_substr(current->data, (*i) - size, size);
}

int	check_term_exists(char *term, t_env *env_lst)
{
	if (!ft_strcmp(term, "&") || !ft_strcmp(term, "_"))
		return (0);
	else if (!ft_strcmp(term, "$") || !ft_strcmp(term, "?"))
		return (1);
	if (!env_lst->data)
		return (0);
	while (env_lst->next)
	{
		if (!ft_strcmp(env_lst->name, term))
			return (1);
		env_lst = env_lst->next;
	}
	if (!ft_strcmp(env_lst->name, term))
		return (1);
	return (0);
}
