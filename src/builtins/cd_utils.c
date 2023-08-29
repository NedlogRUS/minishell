/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:33:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:36:56 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
