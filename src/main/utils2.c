/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:50:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:57:15 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_env_node2(const char *name, const char *data)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node != NULL)
	{
		node->name = ft_strdup((char *)name);
		if (!data)
			node->data = ft_strdup("\0");
		else
			node->data = ft_strdup((char *)data);
		node->next = NULL;
	}
	return (node);
}

t_env	*create_env_node(const char *name, const char *data)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node != NULL)
	{
		node->name = ft_strdup((char *)name);
		if (!data)
			node->data = NULL;
		else
			node->data = ft_strdup((char *)data);
		node->next = NULL;
	}
	return (node);
}

void	insert_env_node(t_env **head, t_env *node)
{
	t_env	*curr;

	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		curr = *head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = node;
	}
}

void	check_oldpwd(t_mhstruct *mh)
{
	t_env	*temp;
	int		i;

	temp = mh->env;
	i = 0;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, "OLDPWD"))
		{
			free(temp->data);
			temp->data = NULL;
			i++;
		}
		temp = temp->next;
	}
	if (i == 0)
		add_oldpwd_node(mh);
}

void	initializer_env(char **env, t_mhstruct *mh, t_env *node, int i)
{
	while (env[i])
	{
		mh->utils->line = ft_strdup(env[i]);
		mh->utils->tmp = mh->utils->line;
		if (ft_strchr(mh->utils->line, '='))
		{
			mh->utils->tmp = ft_strchr(mh->utils->line, '=');
			mh->utils->tmp[0] = '\0';
			mh->utils->name = ft_strdup(mh->utils->line);
			mh->utils->tmp[0] = '0';
			mh->utils->tmp++;
			mh->utils->data = ft_strdup(mh->utils->tmp);
		}
		node = create_env_node(mh->utils->name, mh->utils->data);
		if (node != NULL)
			insert_env_node(&mh->env, node);
		free(mh->utils->line);
		free(mh->utils->name);
		free(mh->utils->data);
		i++;
	}
	check_oldpwd(mh);
}
