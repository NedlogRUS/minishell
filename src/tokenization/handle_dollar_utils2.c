/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:18:22 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 21:27:16 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	get_location(char *search, t_token **curr)
{
	int	location;

	location = 0;
	if (ft_strcmp(search, "$"))
		location = ft_strnstr_mod((*curr)->data, search,
				ft_strlen((*curr)->data)) - 1;
	else
		location = ft_strnstr_mod((*curr)->data, search,
				ft_strlen((*curr)->data));
	return (location);
}

int	inject_helper(int *k, int location, t_token **curr, t_token **new_term)
{
	int		i;

	i = 0;
	while (i < location && (*curr)->data[i])
	{
		(*new_term)->data[*k] = (*curr)->data[i];
		(i)++;
		(*k)++;
	}
	return (0);
}

void	copy_remaining(int *i, int *k, t_token **curr, t_token **new_term)
{
	while ((*curr)->data[*i])
	{
		(*new_term)->data[*k] = (*curr)->data[*i];
		(*i)++;
		(*k)++;
	}
}

int	inject_without_dollar(int *k, int size, t_env **env_term, t_token **new_t)
{
	int	i;

	i = 0;
	while (*k <= size && (*env_term)->data[i])
	{
		(*new_t)->data[*k] = (*env_term)->data[i];
		i++;
		(*k)++;
	}
	return (i);
}

int	do_copy_inject(int *i, int termlen, t_token **new_term, t_token **curr)
{
	int			start;
	int			k;

	start = 0;
	k = 0;
	while (start < *i - termlen - 1 && (*curr)->data[start])
	{
		(*new_term)->data[k] = (*curr)->data[start];
		start++;
		(k)++;
	}
	while ((*curr)->data[*i])
	{
		(*new_term)->data[k] = (*curr)->data[*i];
		(*i)++;
		(k)++;
	}
	return (k);
}
