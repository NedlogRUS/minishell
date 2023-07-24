/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:11:30 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/24 13:46:03 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenlstsize(t_token *lst)
{
	int		i;

	i = 0;
	if (!lst || lst->data[0] == '\0')
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}

	return (i);
}

int	find_range(t_mhstruct *mh, int range)
{
	int	count;
	int	mark;

	count = 1;
	mark = 0;
	while (mh->token->next && mark == 0)
	{
		printf("here");
		if (!(is_special(mh->token->next->data[0])))
		{
			mark = 1;
			mh->token = mh->token->next;
			while (mh->token->next)
			{
				if (is_special(mh->token->next->data[0]))
					break ;
				mark++;
				mh->token = mh->token->next;
			}	
		}
		count++;
		mh->token = mh->token->next;
	}
	printf("mark is %d - count is %d - size is %d\n", mark, count, range);
	return (mark);
}

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

void	concatenate_tokens(t_mhstruct *mh)
{
	int	lst_size;

	lst_size = ft_tokenlstsize(mh->token);
	find_range(mh, lst_size);
	printf("list size is %d\n", lst_size);
	//begin_cat(mh, tok_lst_size);
}