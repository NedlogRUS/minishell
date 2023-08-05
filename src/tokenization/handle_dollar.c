/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/05 18:56:13 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	slice_term(t_token **current, t_mhstruct *mh, int i, int termlen)
{
	int			size;
	t_token		*new_term;

	new_term = init_token("", NULL_VAL);
	size = ft_strlen((*current)->data) - termlen;
	new_term->data = (char *)malloc(sizeof(char) * size + 1);
	if (!new_term)
		return ;
	new_term->data[do_copy_inject(&i, termlen, &new_term, current)] = '\0';
	new_term->next = (*current)->next;
	if ((mh)->token == *current)
		(mh)->token = new_term;
	(*current)->data = ft_strdup(new_term->data);
	i++;
	free(new_term->data);
	free(new_term);
	//return (new_term->data);
}

char	*term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t)
{
	int		location;
	int		i;
	t_token	*new_term;
	int		k;
	int		size;

	i = 0;
	k = 0;
	new_term = init_token(NULL, NULL_VAL);
	location = get_location(search, curr);
	size = get_size(search, mh->env, &env_t, mh)
		- ft_strlen(search) - 1 + ft_strlen((*curr)->data);
	
		new_term->data = (char *)malloc(sizeof(char) * size + 1);
		//ft_bzero(new_term->data, size + 1);
		i = inject_helper(&k, location, curr, &new_term);

		if (ft_strcmp(search, "$") && ft_strcmp(search, "?"))
			inject_without_dollar(&k, size, &env_t, &new_term);
		else if (!ft_strcmp(search, "?"))
			i = inject_exit_msg(&k, size, &new_term, &mh);
		else if (!ft_strcmp(search, "$"))
			i = inject_pid(&k, size, &new_term, &mh);
		i = location + ft_strlen(search) + 1;
		if ((*curr)->data[i])
			copy_remaining(&i, &k, curr, &new_term);
		if ((*curr)->data[i])
			free((*curr)->data);
		// free(*curr);
		finalise_newterm(new_term, curr, mh, k);
		//free(new_term->data);
	//free(new_term);
		// printf("here\n");
	
	return (NULL);
}

void	inject_term(char *search, t_token **curr, t_mhstruct *mh)
{
	t_env	*env_term;
	//char 	*term_hlpr_ptr = NULL;

	env_term = NULL;
	if (is_there_dollar((*curr)->data))
		term_helper(search, mh, curr, env_term);
	
}

void	convert_dollars(t_token **current, t_token **previous, t_mhstruct *mh)
{
	int		i;
	int		qty;
	char	*search_term;
	//char	*slice_term_ptr = NULL;
	//  char	*inject_term_ptr = NULL;

	i = 0;
	search_term = NULL;
	qty = num_of_dollars((*current)->data);
	while (is_there_dollar((*current)->data) && !(*current)->s_quote)
	{
		while ((*current)->data[i] != '$' && (*current)->data[i])
			i++;
		i++;
		search_term = get_search_term(&i, &qty, *current, &search_term);
		if (check_term_exists(search_term, mh->env))
			inject_term(search_term, current, mh);
		else if (check_term_exists(search_term, mh->env) == 0)
			slice_term(current, mh, i, ft_strlen(search_term));
		i = 0;
		free(search_term);
		//free(slice_term_ptr);
		//free(inject_term_ptr);
	}
	if ((*previous) != (*current) && *current)
		(*previous)->next = *current;

}

void handle_dollar(t_mhstruct **mh)
{
	t_token	*previous;
	t_token	*current;
	// t_token *tmp;

	current = (*mh)->token;

	previous = current;
	while (current->next)
	{
		if (is_there_dollar(current->data))
		{
			// if (current == (*mh)->token)
			// {
				
			// 	convert_dollars(&tmp, &previous, *mh);
			// 	free(current->data);
			// 	free(current);
			// 	current = tmp;
			// }
			// else
			convert_dollars(&current, &previous, *mh);
		}
		previous = current;
		current = current->next;
	}
	if (is_there_dollar(current->data))
	{
		convert_dollars(&current, &previous, *mh);
		previous = current;
		current = current->next;
	}
	
}
