// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   concatenate_tokens.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/17 13:11:30 by vtavitia          #+#    #+#             */
// /*   Updated: 2023/07/17 13:45:45 by vtavitia         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	ft_tokenlstsize(t_token *lst)
// {
// 	int		i;
// 	t_token	*j;

// 	j = lst;
// 	i = 0;
// 	if (!lst)
// 		return (0);
// 	while (j != 0)
// 	{
// 		i++;
// 		j = j->next;
// 	}
// 	return (i);
// }

// int count_chars(t_mstruct mh, i, j);

// void	cat_tokens(t_mhstruct *mh, int *i, int *j, int *quote_found)
// {
// 	int	i;
// 	int	j;
// 	int	quote_found;
// 	int	count_chars;

// 	i = *i;
// 	j = *j;
// 	quote_found = *quote_found;
// 	count_chars = count_chars(mh, i, j);
	
	
// }

// void	begin_cat(t_mhstruct *mh, int size)
// {
// 	int		i;
// 	int		j;
// 	int		quote_found;
// 	char	c;

// 	i = 1;
// 	j = 0;
// 	quote_found = 0;

// 	while (i < size)
// 	{
// 		while (mh->token[j])
// 		{
// 			if (mh->token[j] == '\'' || mh->token[j] == "\'")
// 			{
// 				c = mh->token[j];
// 				quote_found = 1;
// 				while (quote_found)
// 					cat_tokens(mh, &i, &j, &quote_found)
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// }

// void	concatenate_tokens(t_mhstruct *mh)
// {
// 	int	tok_lst_size;

// 	tok_lst_size = ft_tokenlstsize(mh->token);
// 	\\printf("list size is %d\n", tok_lst_size);
// 	begin_cat(mh, tok_lst_size);
// }