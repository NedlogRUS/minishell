/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:44:40 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:35:43 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	g_error = 0;
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
