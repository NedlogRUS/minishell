/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:42:38 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/28 17:26:42 by vatche           ###   ########.fr       */
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

void	add_oldpwd_node(t_mhstruct *mh)
{
	t_env	*node;
	t_env	*curr;

	node = (t_env *)malloc(sizeof(t_env));
	if (node != NULL)
	{
		node->name = ft_strdup("OLDPWD");
		node->data = NULL;
		node->next = NULL;
		if (mh->env == NULL)
			mh->env = node;
		else
		{
			curr = mh->env;
			while (curr->next != NULL)
				curr = curr->next;
			curr->next = node;
		}
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

void    add_error_message(t_mhstruct *mh)
{
    mh->emsg = malloc(sizeof(char *) * 16);
    mh->emsg[0] = ft_strdup("cd: ");
    mh->emsg[1] = ft_strdup("export: ");
    mh->emsg[2] = ft_strdup("unset: ");
    mh->emsg[3] = ft_strdup("exit: ");
    mh->emsg[4] = ft_strdup("HOME not set\n");
    mh->emsg[5] = ft_strdup("OLDPWD not set\n");
    mh->emsg[6] = ft_strdup("too many arguments\n");
    mh->emsg[7] = ft_strdup(": Permission denied\n");
    mh->emsg[8] = ft_strdup(": Not a directory\n");
    mh->emsg[9] = ft_strdup(": No such file or directory\n");
    mh->emsg[10] = ft_strdup(": not a valid identifier\n");
    mh->emsg[11] = ft_strdup("command not found: ");
    mh->emsg[12] = ft_strdup("\n");
	mh->emsg[13] = ft_strdup("Minihell: ");
	mh->emsg[14] = ft_strdup("Resource temporarily unavailable\n");
	mh->emsg[15] = ft_strdup("syntax error near unexpected token\n");
}

void	initializer_mh(char **env, t_mhstruct *mh)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	mh->env = NULL;
	mh->in = dup(STDIN_FILENO);
	mh->screen = dup(STDOUT_FILENO);
	mh->utils = malloc(sizeof(t_utils));
	g_error = 0;
	mh->mh_pid = (int)getpid();
	mh->dolmark = 0;
	mh->t_size = 0;
	mh->th_i = 0;
	initializer_env(env, mh, node, i);
	add_error_message(mh);
	free(mh->utils);
	mh->utils = NULL;
}
