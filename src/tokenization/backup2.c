// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   backup2.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/18 12:40:07 by vtavitia          #+#    #+#             */
// /*   Updated: 2023/07/20 18:08:25 by vtavitia         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "vtavitia.h"

// int	ft_strnstr_mod(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	n = 0;
// 	if (needle[n] == '\0')
// 		return (-1);
// 	while (i < len && haystack[i])
// 	{
// 		while (haystack[i + n] == needle[n] && needle[n] != '\0' && n + i < len)
// 			n++;
// 		if (needle[n] == '\0')
// 			return (i);
// 		i++;
// 		n = 0;
// 	}
// 	return (-1);
// }

// int		num_of_dollars(char *str)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// int		is_there_dollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	get_search_term(int *i, int *qty, t_token *current, char **search_term)
// {
// 	int	size;

// 	size = 0;
// 	if (ft_isdigit(current->data[*i]))
// 	{
// 		size++;
// 		(*i)++;
// 	}
// 	else
// 	{
// 		while (current->data[*i] != '$' && current->data[*i] != '\0')
// 		{
// 			size++;
// 			(*i)++;
// 		}
// 	}
// 	(*qty)--;
// 	*search_term = (char *)malloc(sizeof(char) * size);
// 	if (!search_term)
// 		return ;
// 	*search_term = ft_substr(current->data, (*i) - size, size);
// 	//printf(">>>%s<<<\n", current->data);
// 	size = 0;
// }

// int	check_term_exists(char *term, t_env *env_lst)
// {
// 	if (!env_lst->data)
// 		return (0);
// 	while (env_lst->next)
// 	{
// 		if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
// 			return (1);
// 		env_lst = env_lst->next;
// 	}
// 	if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
// 		return (1);
// 	return (0);
// }

// int	get_size(char *term, t_env *env_lst, t_env **env_term)
// {
// 	int	i;
// 	int	found;

// 	i = 0;
// 	found = 0;
// 	while (env_lst->next)
// 	{
// 		if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0)
// 		{
// 			*env_term = env_lst;
// 			found = 1;
// 			while (env_lst->data[i])
// 				i++;			
// 			break ;
// 		}
// 		env_lst = env_lst->next;
// 	}

// 	if (ft_strncmp(env_lst->name, term, ft_strlen(term)) == 0 && !found)
// 		{
// 			while (env_lst->data[i])
// 				i++;
// 		}
// 	//printf("FOUND %s which is %s - size is %d\n", term, env_lst->data, i);
// 	return (i);
// }

// void	slice_term(t_token **current, t_token **previous, t_mhstruct *mh, int i, int term)
// {
// 	int start;
// 	int	size;
// 	int	k;
// 	t_token	*new_term;

// 		(void)mh;
// 	new_term = init_token("", NULL_VAL);
// 	start = 0;
// 	k = 0;
		
// 	size = ft_strlen((*current)->data) - term;

// 	new_term->data = (char *)malloc(sizeof(char) * size + 1);
// 	while (start < i - term - 1 && (*current)->data[start])
// 	{
// 		new_term->data[k] = (*current)->data[start];
// 		start++;
// 		k++;
// 		printf("HERE %s start is %d and i is %d\n", new_term->data, start, i);

// 	}
// 	while ((*current)->data[i])
// 	{
// 		new_term->data[k] = (*current)->data[i];
// 		i++;
// 		k++;
// 			printf("NOW HERE %s\n", new_term->data);
// 	}
// 	//printf("newterm is %s\n", new_term->data);
// 	new_term->data[k] = '\0';
// 	new_term->next = (*current)->next;
// 		//printf("newterm next is %p\n", new_term->next);
// 	free(*current);
// 	*current = new_term;
// 	//if ((*current) != (*previous))
// 	(*previous)->next = *current;
// 	i++;
// }

// void	inject_term(char *search_term,t_token **current, t_token **previous, t_mhstruct *mh)
// {
// 	int		i;
// 	int		location;
// 	t_token	*new_term;
// 	t_env	*env_term;
// 	int		size;
// 	int		k;
// 	i = 0;
// 	k = 0;
// 	//new_term = init_token(" ", NULL_VAL);
// 	env_term = NULL;
// 	new_term = init_token("", NULL_VAL);
// 	size = get_size(search_term, mh->env, &env_term);
// 	printf("!!!size is %d\n", size);
// 		if (is_there_dollar((*current)->data))
// 		 {
			
// 			location = ft_strnstr_mod((*current)->data, search_term, ft_strlen((*current)->data)) - 1;
//  			//printf("location is %d\n", location );
// 					//printf("ENTERED %s\n", (*current)->data);
// 			size = (location + size); //+ ft_strlen((*current)->data) - location;
// 			new_term->data = (char *)malloc(sizeof(char) * size + 1);
// 			//	printf("here 1 %d\n---\n", size);
// 			// if (size)
// 			// {
// 				while (i < location && (*current)->data[i])
// 				{
// 					new_term->data[k] = (*current)->data[i];
// 					i++;
// 					k++;
// 				}
			
// 				i = 0;
				
// 				// if (check_term_exists(search_term, mh->env))
// 				// {
// 					while (k <= size && env_term->data[i])
// 					{
// 						new_term->data[k] = env_term->data[i];
// 						i++;
// 						k++;
// 					}
// 					i = location + ft_strlen(search_term) + 1;
// 					//	printf("here  %d and k is %d location is %d\n---\n", i, k, location);
// 					if ((*current)->data[i])
// 					{
// 						while ((*current)->data[i])
// 						{
// 							new_term->data[k] = (*current)->data[i];
// 							i++;
// 							k++;
// 						}
// 					}
// 				// }
// 			// }
// 			//printf("size is here%d\n---\n", size);
// 			new_term->data[k] = '\0';
// 			new_term->next = (*current)->next;
// 			printf("newterm  %s \n", new_term->data);
// 			printf("newterm 2 next is %p (*previous)->next is %p\n", new_term->next, (*previous)->next);
// 			free(*current);
// 			*current = new_term;
// 			//if ((*current) != (*previous))
// 			(*previous)->next = *current;
// 			printf("current data is now %s\n", (*current)->data);
// 			// printf("newterm is %s and next is %s\n", new_term->data, new_term->data);
// 			i++;
// 		//	printf("finish@@@@!!!\n");
// 		 }
// }

// void	convert_dollars(t_token **current_p, t_token **previous_p, t_mhstruct *mh)
// {
// 	int		i;
// 	int		qty;
	
// 	char	*search_term;
// 	t_token *current;
// 	t_token *previous;
// 	current = *current_p;
// 	previous = * previous_p;
// 	i = 0;
// 	search_term = NULL;
// 	qty = num_of_dollars(current->data);
// 	printf("\n\nSTART Search term is '%s' qty = %d\n", search_term,qty);
// 	printf("checking now %s\n", current->data);
// 	while (is_there_dollar(current->data))
// 	{
// 		while (current->data[i] != '$' && current->data[i])
// 			i++;
// 		i++;

// 		get_search_term(&i, &qty, current, &search_term);
// 				printf("\n\nSearch term is '%s' qty = %d\n", search_term,qty);
// 		if (check_term_exists(search_term, mh->env))
// 		{
// 			// i++;
// 			printf("FOUND\n");
// 			inject_term(search_term, &current, &previous, mh);
// 			// if (current->data[i])
// 			// 		i = ft_strnstr_mod(current->data, "$", ft_strlen(current->data)) - 1;
// 			//printf("Current data is %s\n", current->data);
// 		}
// 		else if (check_term_exists(search_term, mh->env) == 0)
// 		{
// 			printf("FAIL\n");
// 			slice_term(&current, &previous, mh, i, ft_strlen(search_term));
// 		}
// 		printf("\n\nOK SO Current is '%s' next is %p\n",current->data, current->next);
// 		i = 0;
// 	}
// }

// void	handle_dollar(t_mhstruct **mh)
// {
// 	t_token	*previous;
// 	t_token	*current;

// 	previous = (*mh)->token;
// 	current = (*mh)->token;
// 	while (current->next)
// 	{
// 		printf("ENTERED333!\n");
// 		if (is_there_dollar(current->data))
// 			convert_dollars(&current, &previous, *mh);
// 		current = current->next;
// 		previous = current;		
// 	}
// 	if (is_there_dollar(current->data))
// 	{
			
// 			convert_dollars(&current, &previous, *mh);
// 				current = current->next;
// 		previous = current;
			
// 			//	printf("Final is %s \n", current->data);
// 	}
// 	printf("Final is %s \n", current->data);	
// 	// printf("Final is %s and next is %s\n", current->data, current->next->data);
// }