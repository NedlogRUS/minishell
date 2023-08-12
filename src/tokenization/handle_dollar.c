/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/12 17:19:34 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	term_helper3(t_token **tmp, t_token **new_term)
{
	free((*tmp)->data);
	free(*tmp);
	free(*new_term);
}

void	term_helper2(t_token **tmp, t_token **new_term, t_token **curr)
{
	*tmp = init_token("", NULL_VAL);
	*new_term = init_token(NULL, NULL_VAL);
	(*tmp)->data = ft_strdup((*curr)->data);
	(*tmp)->s_quote = (*curr)->s_quote;
	(*tmp)->d_quote = (*curr)->d_quote;
	free((*curr)->data);
	(*curr)->data = (*tmp)->data;
}

void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t)
{
	t_token	*new_term;
	t_token *tmp;
	int		location;
	int		i;
	int		k;
	int		size;

	i = 0;
	k = 0;
	term_helper2(&tmp, &new_term, curr);
	location = get_location(search, curr);
	if (!ft_strcmp(search, "$"))
		location--;
	size = get_size(search, mh->env, &env_t, mh)
		- ft_strlen(search) - 1 + ft_strlen((*curr)->data);
	new_term->data = (char *)malloc(sizeof(char) * size + 1);
	i = inject_helper(&k, location, curr, &new_term);
	if (ft_strcmp(search, "$") && ft_strcmp(search, "?"))
		inject_without_dollar(&k, size, &env_t, &new_term);
	else if (!ft_strcmp(search, "?"))
		i = inject_exit_msg(&k, size, &new_term, &mh);
	else if (!ft_strcmp(search, "$"))
		i = inject_pid(&k, size, &new_term, &mh);
	i = location + ft_strlen(search) + 1;
	if ((*curr)->data[i] != '\0')
		copy_remaining(&i, &k, curr, &new_term);
	finalise_newterm(new_term, curr, mh, k);
	term_helper3(&tmp, &new_term);
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
 
void	handle_dollar(t_mhstruct **mh)
{
	t_token	*previous;
	t_token	*current;
	t_token	*tmp;
	int		mark;

	tmp = NULL;
	if (is_there_dollar((*mh)->token->data))
		mark = 1;
	else
		mark = 0;
	current = (*mh)->token;
	previous = current;
	while (current)
	{
		if (current == (*mh)->token)
		mark = is_there_dollar((*mh)->token->data);
		if (is_there_dollar(current->data) && !(current->s_quote))
		{
			convert_dollars(&current, *mh);
			if (!ft_strlen(current->data) && !(current->s_quote || current->d_quote))
			{
				if (previous == current && mark && (current->next == NULL))
				{
					free(current->data);
					free(current);
					(*mh)->token = NULL;
					return ;
				}
				else if (previous == current && mark && (current->next != NULL))
				{
					tmp = current->next;
					free(current->data);
					free((*mh)->token);
					current = tmp;
					previous = current;
					(*mh)->token = current;
					mark = 0;
				}
				else
				{
					if (current->next)
					{
						current = current->next;
						previous = current;
					}
					else if (current->next == NULL)
					{
						free(current->data);
						free(current);
						current = NULL;
						previous->next = current;
					}
				}
			}
			else if (current->next)
			{
				previous = current;
				current = current->next;
			}
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}


// char	*term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t)
// {
// 	int		location;
// 	int		i;
// 	t_token	*new_term;
// 	int		k;
// 	int		size;
// 	t_token *tmp;
// 	tmp = init_token("", NULL_VAL);
// 	new_term = init_token(NULL, NULL_VAL);
// 	tmp->data = ft_strdup((*curr)->data);
// 	tmp->s_quote = (*curr)->s_quote;
// 	tmp->d_quote = (*curr)->d_quote;
// 	free((*curr)->data);
// 	(*curr)->data = tmp->data;
// 	i = 0;
// 	k = 0;
// 	location = get_location(search, curr);
// 	if (!ft_strcmp(search, "$"))
// 		location--;
// 	size = get_size(search, mh->env, &env_t, mh)
// 		- ft_strlen(search) - 1 + ft_strlen((*curr)->data);
// 	new_term->data = (char *)malloc(sizeof(char) * size + 1);
// 	i = inject_helper(&k, location, curr, &new_term);
// 	if (ft_strcmp(search, "$") && ft_strcmp(search, "?"))
// 		inject_without_dollar(&k, size, &env_t, &new_term);
// 	else if (!ft_strcmp(search, "?"))
// 		i = inject_exit_msg(&k, size, &new_term, &mh);
// 	else if (!ft_strcmp(search, "$"))
// 		i = inject_pid(&k, size, &new_term, &mh);
// 	i = location + ft_strlen(search) + 1;
// 	if ((*curr)->data[i] != '\0')
// 		copy_remaining(&i, &k, curr, &new_term);
// 	finalise_newterm(new_term, curr, mh, k);
// 	free(tmp->data);
// 	free(tmp);
// 	free(new_term);
// 	return (NULL);
// }


// void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t)
// {
// 	int		i;
// 	t_token	*new_term;
// 	int		k;
// 	int		size;
// 	t_token	*tmp;

// 	new_term = NULL;
// 	tmp = NULL;
// 	term_helper2(&tmp, &new_term, curr);
// 	k = 0;
// 	size = get_size(search, mh->env, &env_t, mh)
// 		- ft_strlen(search) - 1 + ft_strlen((*curr)->data);
// 	new_term->data = (char *)malloc(sizeof(char) * size + 1);
// 	i = inject_helper(&k, get_location(search, curr), curr, &new_term);
// 	if (ft_strcmp(search, "$") && ft_strcmp(search, "?"))
// 		inject_without_dollar(&k, size, &env_t, &new_term);
// 	else if (!ft_strcmp(search, "?"))
// 		i = inject_exit_msg(&k, size, &new_term, &mh);
// 	else if (!ft_strcmp(search, "$"))
// 		i = inject_pid(&k, size, &new_term, &mh);
// 	i = get_location(search, curr) + ft_strlen(search) + 1;
// 	if ((*curr)->data[i])
// 		copy_remaining(&i, &k, curr, &new_term);
// 	finalise_newterm(new_term, curr, mh, k);
// 	term_helper3(&tmp, &new_term);
// }

// void	convert_dollars(t_token **current, t_mhstruct *mh)
// {
// 	int		i;
// 	int		qty;
// 	char	*search_term;

// 	i = 0;
// 	search_term = NULL;
// 	qty = num_of_dollars((*current)->data);
// 	while (is_there_dollar((*current)->data) && !(*current)->s_quote)
// 	{
// 		//shift_i(current, &i);
// 		if ((*current)->data[i] == '$' && (*current)->data[i + 1] == ' ')  
// 				i++;
// 		while ((*current)->data[i] != '$' && (*current)->data[i])
// 		{
// 			i++;
// 			if ((*current)->data[i] == '$' && (*current)->data[i + 1] == ' ')
// 				i++;
// 			// else if ((*current)->data[i] == '$' && (*current)->data[i + 1] == '\'')
// 			// {
// 			// 		printf("at %c\n", (*current)->data[i]);
// 			// 	i++;}
// 		}
// 		i++;
	
// 		get_search_term(&i, &qty, *current, &search_term);
// 		if (check_term_exists(search_term, mh->env))
// 			inject_term(search_term, current, mh);
// 		else if (check_term_exists(search_term, mh->env) == 0)
// 			slice_term(current, mh, i, ft_strlen(search_term));
// 		i = 0;
// 		free(search_term);
// 	}
// }