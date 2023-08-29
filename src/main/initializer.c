/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:42:38 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:55:29 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	add_error_message(t_mhstruct *mh)
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
	mh->mh_pid = 0;
	mh->dolmark = 0;
	mh->t_size = 0;
	mh->th_i = 0;
	initializer_env(env, mh, node, i);
	add_error_message(mh);
	free(mh->utils);
	mh->utils = NULL;
}
