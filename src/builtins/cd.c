/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/28 21:11:02 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void change_pwd(t_mhstruct *mh)
{
	t_env *temp = mh->env;
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
    while (temp != NULL) 
	{
        if(!ft_strcmp(temp->name, "PWD"))
		{
			if(temp->data != NULL)
				free(temp->data);
			if(getcwd(cwd, sizeof(cwd)) == NULL)
				temp->data = ft_strdup("\0");
			else
				temp->data = ft_strdup(cwd);
		}
        temp = temp->next;
    }
	return;
}

void change_oldpwd(t_mhstruct *mh, char *old)
{
	t_env *temp = mh->env;
    while (temp != NULL) 
	{
        if(!ft_strcmp(temp->name, "OLDPWD"))
		{
			if(temp->data != NULL)
				free(temp->data);
			if(!old)
				temp->data = ft_strdup("\0");
			else
				temp->data = ft_strdup(old);
		}
        temp = temp->next;
    }
	return;
}
void error_opendir(t_mhstruct *mh, char *path)
{
	if(errno == 13)
	{
		mh->er_num = 1;
		printf("minihell: cd: %s : Permission denied\n", path);
	}
	else
	{
		mh->er_num = 1;
		printf("minihell: cd: %s : Not a directory\n", path);
	}
	return ;
}

void do_cd(t_mhstruct *mh, char *path)
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	DIR	*dir;
	if(access(path, F_OK) != 0)
	{
		mh->er_num = 1;
		printf("minihell: cd: %s : No such file or directory\n", path);
		return ;
	}
	dir = opendir(path);
    if (!dir)
	{
		error_opendir(mh, path);
		return ;
	}
    else
 		closedir(dir);
	if (chdir(path) != 0)
	{
		mh->er_num = 1;
		printf("minihell: cd: %s : Permission denied\n", path);
		return ;
	}
	change_oldpwd(mh, cwd);
	change_pwd(mh);
	return ;
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

char	*find_home(t_mhstruct *mh)
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
				return NULL;
			}
			return (ft_strdup(temp->data));
		}
        temp = temp->next;
    }
	printf("minihell: cd: HOME not set\n");
	mh->er_num = 1;
	return NULL;
}

void change_path(t_mhstruct *mh, char *path)
{
	char	*line = ft_strdup(path);
    char	*out = NULL;
	char 	*tmp;
	tmp = line;
	out = find_home(mh);
	if(!out)
		return;
	tmp++;
	out = ft_mhjoin(out, tmp);
	free (line);
	do_cd(mh, out);
	free(out);
	return ;
}

void handling_cd(t_mhstruct *mh, char *path)
{
	if(!ft_strcmp(path, "-"))
		do_cd_oldpwd(mh);	
	else if(!ft_strcmp(path, "~"))
		do_cd_home(mh);
	else if(!ft_strncmp(path, "~", 1))
		change_path(mh, path);
	else
		do_cd(mh, path);
	return ;
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
