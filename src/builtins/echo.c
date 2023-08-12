/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:36:10 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/12 14:48:37 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_echo(t_token *token, int flag)
{
	t_token	*curr;

	curr = token;
	if (curr == NULL)
	{
		if (flag == 0)
			printf("\n");
		return ;
	}
	//while(curr != NULL && curr->next != NULL)
	while (curr->next != NULL) // don't forget chek for token type
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
	// don't forget chek for token type
	printf("%s", curr->data);
	if (flag == 0)
		printf("\n");
	return ;
}

// cfix case echo "-nnnn" nenie_ir
void	builtin_echo(t_mhstruct *mh)
{
	t_token	*token;
	int		i;

	token = mh->token->next;
	mh->er_num = 0;
	i = 0;
	if (token == NULL )
	{	
		printf("\n");
		return ;
	}
	while (token != NULL && !ft_strcmp(token->data, "-n")) // don't forget chek for token type
	{
		i = 1;
		token = token->next;
	}
	do_echo(token, i);
	return ;
}
