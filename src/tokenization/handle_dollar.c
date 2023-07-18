/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:40:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/18 17:50:22 by vtavitia         ###   ########.fr       */
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

int		num_of_dollars(char *str)
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

int		is_there_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	get_search_term(int *i, int *qty, t_token *current, char **search_term)
{
	int	size;

	size = 0;
	if (ft_isdigit(current->data[*i]))
	{
		size++;
		(*i)++;
	}
	else
	{
		while (current->data[*i] != '$' && current->data[*i] != '\0')
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
	size = 0;
}

int	check_term_exists(char *term, t_env *env_lst)
{
	if (!env_lst->data)
		return (0);
	while (env_lst->next)
	{
		if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
			return (1);
		env_lst = env_lst->next;
	}
	if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
		return (1);
	return (0);
}

int	get_size(char *term, t_env *env_lst, t_env **env_term)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (env_lst->next)
	{
		if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
		{
			*env_term = env_lst;
			found = 1;
			while (env_lst->data[i])
				i++;			
			break ;
		}
		env_lst = env_lst->next;
	}

	if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0 && !found)
		{
			while (env_lst->data[i])
				i++;
		}
	//printf("FOUND %s which is %s - size is %d\n", term, env_lst->data, i);
	return (i);
}

void	inject_term(char *search_term,t_token **current, t_token **previous, t_mhstruct *mh)
{
	int		i;
	int		location;
	t_token	*new_term;
	t_env	*env_term;
	(void) previous;
	int		size;
	int		k;
	
	i = 0;
	k = 0;
	new_term = init_token(" ", NULL_VAL);
	env_term = NULL;
	size = get_size(search_term, mh->env, &env_term);
	
		while ((*current)->data[i] && is_there_dollar((*current)->data + i))
		{
			
			location = ft_strnstr_mod((*current)->data, search_term, ft_strlen((*current)->data)) - 1;
			//printf("size is %d\n", size);
			//printf("@@@@@@@@@@@@@@@@@@@@@@@@@here\n");
			size = (location + size); //+ ft_strlen((*current)->data) - location;
		
			new_term->data = (char *)malloc(sizeof(char) * size + 1);
			//	printf("here 1 %d\n---\n", size);
			// if (size)
			// {
				while (i < location && (*current)->data[i])
				{
					new_term->data[k] = (*current)->data[i];
					i++;
					k++;
				}
				//printf("here 2 %d\n---\n", size);
				i = 0;
				if (check_term_exists(search_term, mh->env))
				{
					while (k <= size && env_term->data[i])
					{
						new_term->data[k] = env_term->data[i];
						i++;
						k++;
					}
				}
			// }
			//printf("size is here%d\n---\n", size);
			new_term->data[k] = '\0';
			(*previous)->next = new_term;
			new_term->next = (*current)->next;
			free(*current);
			*current = new_term;
			
			
			printf("newterm is %s\n", new_term->data);
				//printf("envterm is %s\n", env_term->data);
			i++;
		}
	
}

void	convert_dollars(t_token *current, t_token *previous, t_mhstruct *mh)
{
	int		i;
	int		qty;
	
	char	*search_term;

	i = 0;
	search_term = NULL;
	qty = num_of_dollars(current->data);
	printf("CURRENT IS %s qty is %d\n", current->data, qty);
	while (current->data[i] && qty > 0)
	{
		if (current->data[i] == '$' && qty)
		{
			i++;
			printf("i is now %d\n", i);
			get_search_term(&i, &qty, current, &search_term);
			printf("Search term is %s len = %d\n", search_term, (int)ft_strlen(search_term));
			if (check_term_exists(search_term, mh->env))
			{
				inject_term(search_term, &current, &previous, mh);
				if (current->data[i])
					i = ft_strnstr_mod(current->data, "$", ft_strlen(current->data)) - 1;
			}
			else if (check_term_exists(search_term, mh->env) == 0)
			{
				i += ft_strlen(search_term) - 1;
				printf("here %s = i is now %d\n", search_term, i);
			}
			//printf("CURRENT IS now %s qty is %d\n", current->data, qty);
			
			free(search_term);
		}
		else
			i++;
	}
}

void	handle_dollar(t_mhstruct **mh)
{
	t_token	*previous;
	t_token	*current;

	previous = (*mh)->token;
	current = (*mh)->token;
	while (current->next)
	{
		if (is_there_dollar(current->data))
			convert_dollars(current, previous, *mh);
		previous = current;
		current = current->next;
	}
	if (is_there_dollar(current->data))
			convert_dollars(current, previous, *mh);
}