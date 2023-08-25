/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/25 18:40:50 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gemsg(char *cmndname, char *errmsg, char *data)
{
	char	*out;

	out = ft_strdup("miniHell: ");
	if(cmndname != NULL)
		out = ft_mhjoin(out, cmndname);
	if (data)
		out = ft_mhjoin(out, data);
	out = ft_mhjoin(out, errmsg);
	return (out);
}

void	pr_err(t_mhstruct *mh, int i, char *errmsg)
{
	(void) mh;
	GLOBAL_ERROR = i;
	ft_putstr_fd(errmsg, 2);
	free(errmsg);
	return ;
}

void	change_pwd(t_mhstruct *mh)
{
	t_env	*temp;
	char	cwd[PATH_MAX];

	temp = mh->env;
	getcwd(cwd, sizeof(cwd));
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "PWD"))
		{
			if (temp->data != NULL)
				free(temp->data);
			if (getcwd(cwd, sizeof(cwd)) == NULL)
				temp->data = ft_strdup("\0");
			else
				temp->data = ft_strdup(cwd);
		}
		temp = temp->next;
	}
	return ;
}

void	change_oldpwd(t_mhstruct *mh, char *old)
{
	t_env	*temp;

	temp = mh->env;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "OLDPWD"))
		{
			if (temp->data != NULL)
				free(temp->data);
			if (!old)
				temp->data = ft_strdup("\0");
			else
				temp->data = ft_strdup(old);
		}
		temp = temp->next;
	}
	return ;
}

void	error_opendir(t_mhstruct *mh, char *path)
{
	if (errno == 13)
		pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[7], path));
	else
		pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[8], path));
	return ;
}

int	do_cd(t_mhstruct *mh, char *path)
{
	char	cwd[PATH_MAX];
	DIR		*dir;

	getcwd(cwd, sizeof(cwd));
	if (access(path, F_OK) != 0)
		return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[9], path)), 1);
	dir = opendir(path);
	if (!dir)
	{
		error_opendir(mh, path);
		return (1);
	}
	else
		closedir(dir);
	if (chdir(path) != 0)
		return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[7], path)), 1);
	change_oldpwd(mh, cwd);
	change_pwd(mh);
	return (0);
}

void	do_cd_oldpwd(t_mhstruct *mh)
{
	t_env	*temp;

	temp = mh->env;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "OLDPWD"))
		{
			if (!temp->data)
				return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[5], NULL)));
			if (!do_cd(mh, temp->data))
				builtin_pwd(mh);
			return ;
		}
		temp = temp->next;
	}
	return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[5], NULL)));
}

void	do_cd_home(t_mhstruct *mh)
{
	t_env	*temp;

	temp = mh->env;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "HOME"))
		{
			if (!temp->data)
				return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[4], NULL)));
			do_cd(mh, temp->data);
			return ;
		}
		temp = temp->next;
	}
	return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[4], NULL)));
}

char	*find_home(t_mhstruct *mh)
{
	t_env	*temp;

	temp = mh->env;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "HOME"))
		{
			if (!temp->data)
				return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[4] \
				, NULL)), NULL);
			return (ft_strdup(temp->data));
		}
		temp = temp->next;
	}
	return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[4], NULL)), NULL);
}

void	change_path(t_mhstruct *mh, char *path)
{
	char	*line;
	char	*out;
	char	*tmp;

	line = ft_strdup(path);
	tmp = line;
	out = find_home(mh);
	if (!out)
		return ;
	tmp++;
	out = ft_mhjoin(out, tmp);
	free (line);
	do_cd(mh, out);
	free(out);
	return ;
}

void	handling_cd(t_mhstruct *mh, char *path)
{
	if (!ft_strcmp(path, "-"))
		do_cd_oldpwd(mh);
	else if (!ft_strcmp(path, "~"))
		do_cd_home(mh);
	else if (!ft_strncmp(path, "~", 1))
		change_path(mh, path);
	else
		do_cd(mh, path);
	return ;
}

void	builtin_cd(t_mhstruct *mh)
{
	t_token	*token;
	int		i;

	token = mh->token->next;
	GLOBAL_ERROR = 0;
	i = 0;
	if (token == NULL )
	{	
		do_cd_home(mh);
		return ;
	}
	while (token != NULL)
	{
			token = token->next;
			i++;
	}
	if (i > 1)
		return (pr_err(mh, 1, gemsg(mh->emsg[0], mh->emsg[6], NULL)));
	token = mh->token->next;
	handling_cd(mh, token->data);
	return ;
}
