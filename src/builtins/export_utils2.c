/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:45:50 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:46:10 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_export_2(t_mhstruct *mh, char *tdata)
{
	mh->utils = malloc(sizeof(t_utils));
	mh->utils->data = NULL;
	mh->utils->line = ft_strdup(tdata);
	mh->utils->tmp = ft_strchr(mh->utils->line, '=');
	mh->utils->tmp[0] = '\0';
	mh->utils->name = ft_strdup(mh->utils->line);
	mh->utils->tmp[0] = '0';
	mh->utils->tmp++;
}

void	add_export(t_mhstruct *mh, char *tdata)
{
	t_env	*node;

	node = NULL;
	add_export_2(mh, tdata);
	if (mh->utils->tmp[0] != '\0')
		mh->utils->data = ft_strdup(mh->utils->tmp);
	if (!check_env_name(&mh->env, mh->utils->name))
	{
		if (!mh->utils->data)
			node = create_env_node2(mh->utils->name, NULL);
		else
			node = create_env_node(mh->utils->name, mh->utils->data);
		if (node != NULL)
			insert_env_node(&mh->env, node);
	}
	else
		change_env_data(&mh->env, mh->utils->name, mh->utils->data);
	free(mh->utils->line);
	free(mh->utils->name);
	if (mh->utils->data != NULL)
		free(mh->utils->data);
	free(mh->utils);
	return ;
}
