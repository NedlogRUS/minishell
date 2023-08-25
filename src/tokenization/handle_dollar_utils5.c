/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:51:16 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 20:00:55 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	inject_term(char *search, t_token **curr, t_mhstruct *mh)
{
	t_env	*env_term;

	env_term = NULL;
	if (is_there_dollar((*curr)->data))
		term_helper(search, mh, curr, env_term);
}

void	shift_i(t_token **current, int *i)
{
	if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == '\0')
	{
		(*i)++;
		return ;
	}
	else if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == ' ')
		(*i)++;
	while ((*current)->data[*i] != '$' && (*current)->data[*i])
	{
		(*i)++;
		if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == '\0')
			(*i)++;
		else if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == ' ')
			(*i)++;
	}
	(*i)++;
}

void	update_car(t_token **prev, t_token **curr)
{
	*prev = *curr;
	*curr = (*curr)->next;
}

void	convert_dollars(t_token **current, t_mhstruct *mh)
{
	int		i;
	int		qty;
	char	*search_term;

	i = 0;
	search_term = NULL;
	qty = num_of_dollars((*current)->data);
	while (is_there_dollar((*current)->data) && !(*current)->s_quote)
	{
		shift_i(current, &i);
		get_search_term(&i, &qty, *current, &search_term);
		if (check_term_exists(search_term, mh->env))
			inject_term(search_term, current, mh);
		else if (check_term_exists(search_term, mh->env) == 0)
			slice_term(current, mh, i, ft_strlen(search_term));
		i = 0;
		free(search_term);
	}
}
