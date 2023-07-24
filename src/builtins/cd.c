/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/24 20:28:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cd(t_mhstruct *mh, cahr **path)
{
	
}

void cd_home(t_mhstruct *mh)
{
	t_env *temp = mh->env;
	int i = 0;
    while (temp != NULL) 
	{
        if(!ft_strcmp(temp->name, "HOME"))
		{
			if(!temp->data)
			{
				mh->er_num = 1;
				printf("minihell: cd: HOME not set\n");
				return;
			}
			cd(mh, temp->data)
		}
        temp = temp->next;
    }
}

void builtin_cd(t_mhstruct *mh)
 {
	t_token	*token;
	token = mh->token; // token = mh->token->next;
	token = token->next;
	mh->er_num = 0;
	int i = 0;
	if(token == NULL )// нужно проверить на маке, на линуксе если нет аргументов
	// сд выходит в коренвую папку // yes on mac too
	{	
		cd_home(mh)
		return ;
	}
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