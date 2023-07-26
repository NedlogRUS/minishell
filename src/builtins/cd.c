/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/26 21:16:38 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void do_cd(t_mhstruct *mh, char *path)
{
	(void) mh;
	(void) path;
	if (chdir(path) != 0)
		printf("minihell: cd: %s : No such file or directory\n", path);
	// int i = chdir(path);
	// printf("chdir: %d\n", i);
}

void do_cd_oldpwd(t_mhstruct *mh)
{
	t_env *temp = mh->env;
    while (temp != NULL) 
	{
        if(!ft_strcmp(temp->name, "OLDPWD"))
		{
			if(!temp->data)
			{
				mh->er_num = 1;
				printf("minihell: cd: OLDPWD not set\n");
				return;
			}
			do_cd(mh, temp->data);
			return;
		}
        temp = temp->next;
    }
	printf("minihell: cd: OLDPWD not set\n");
	mh->er_num = 1;
	return;
}

void do_cd_home(t_mhstruct *mh)
{
	t_env *temp = mh->env;
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
			do_cd(mh, temp->data);
			return;
		}
        temp = temp->next;
    }
	printf("minihell: cd: HOME not set\n");
	mh->er_num = 1;
	return;
}

void handling_cd(t_mhstruct *mh, char *path)
{
	if(!ft_strcmp(path, "-"))
		do_cd_oldpwd(mh);	
	else if(!ft_strcmp(path, "~"))
		do_cd_home(mh);
	// else if(!ft_strncmp(path, "~", 2))
	// 	change_path(mh, path);
	else
		do_cd(mh, path);
}

void builtin_cd(t_mhstruct *mh)
 {
	t_token	*token;
	token = mh->token; // token = mh->token->next;
	token = token->next;
	mh->er_num = 0;
	int i = 0;
	if(token == NULL )
	{	
		do_cd_home(mh);
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
		mh->er_num = 1;
		return ;
	}
	token = mh->token->next;
	handling_cd(mh, token->data);
	return ;
}

// если нет доступа в папку -  bash: cd: foldername/: Permission denied
// bash: cd: a: Not a directory
// bash: cd: as: No such file or directory
