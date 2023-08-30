/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:08:46 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 21:52:30 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

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
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\''))
			{
				i++;
				if (str[i] != ' ' && str[i] != '\0' && str[i] != '\'')
					return (1);
			}
			else if (str[i + 1] != ' ' && str[i + 1] != '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	get_search_term_checks(t_token	*current, int *i, int *sizep)
{
	char	*delim_chars;

	delim_chars = " \'\t$;|\n\\.3=#:\\!/";
	if (ft_isdigit(current->data[*i]) || current->data[(*i)] == '$'
		|| current->data[(*i)] == '?' || current->data[(*i)] == '\0')
	{
		(*sizep)++;
		(*i)++;
	}
	else if (current->data[(*i)] == ' ')
	{
		(*sizep)++;
		(*i)++;
	}
	else
	{
		while (!ft_strchr(delim_chars, current->data[*i]))
		{
			(*sizep)++;
			(*i)++;
		}
	}
}

char	*get_term(int *i, int *qty, t_token *current, char **search_term)
{
	int		size;

	size = 0;
	(void)qty;
	*search_term = NULL;
	get_search_term_checks(current, i, &size);
	if (!search_term)
		return (NULL);
	if (size)
		*search_term = ft_substr(current->data, (*i) - size, size);
	return (*search_term);
}

int	check_term_exists(char *term, t_env *env_lst)
{
	if (term)
	{
		if (!ft_strcmp(term, "&"))
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
	}
	return (0);
}
