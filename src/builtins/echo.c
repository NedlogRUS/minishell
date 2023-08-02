/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:36:10 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/31 18:49:49 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_echo(t_token *token, int flag)
{
	t_token	*curr;
	curr = token; 
	if(curr == NULL)
	{
		if(flag == 0)
			printf("\n");
		return ;
	}
	while(curr != NULL && curr->next != NULL)
	while(curr->next != NULL) // don't forget chek for token type
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
	// don't forget chek for token type
	printf("%s", curr->data);
	if(flag == 0)
		printf("\n");
	return ;
}

void builtin_echo(t_mhstruct *mh)
 {
	t_token	*token;
	token = mh->token; // token = mh->token->next;
	token = token->next;
	mh->er_num = 0;
	int i = 0;
	if(token == NULL )
	{	
		printf("\n");
		return ;
	}
	while(token != NULL && !ft_strcmp(token->data, "-n")) // don't forget chek for token type
	{
		i = 1;
		token = token->next;
	}
	do_echo(token, i);
	return ;
}