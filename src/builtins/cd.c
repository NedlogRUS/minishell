/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/22 23:11:48 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void builtin_cd(t_mhstruct *mh)
 {
	t_token	*token;
	token = mh->token; // token = mh->token->next;
	token = token->next;
	int i = 0;
	if(token == NULL )// нужно проверить на маке, на линуксе если нет аргументов
	// сд выходит в коренвую папку
		return ;
	while(token != NULL) //здесь нужно будет проверять что сд получает только стрингу или команду
	// если аргументов больше одного должен выводить ошибку -bash: cd: too many arguments
	{
			token = token->next;
			i++;
	}
	if(i > 1)
	{
		printf("minihell: cd: too many arguments\n");
		return ;
	}
	do_cd(mh, token->data);
	return ;
}

// если нет доступа в папку -  bash: cd: foldername/: Permission denied