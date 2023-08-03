/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:09:54 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/03 20:18:44 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_for_export(t_mhstruct *mh, char *tdata)
{
	char *arg = tdata;
	int i = 1;
	
	if(!ft_isalpha(arg[0]))// not 1 ! mean 0
		return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)), 1);
	while(arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if(!ft_isalnum(arg[i]) && arg[i] != '_')
			return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)), 1);
		i++;
	}
	return 0;
}

int check_env_name(t_env** head,char *name)
{
	t_env	*curr = *head;
	
	// while (curr->next != NULL) 
	while (curr != NULL) 
	{
		if(!ft_strcmp(curr->name, name))
			return 1;
        curr = curr->next;
    }
	return 0;
}

void	change_env_data(t_env** head,char *name, char *data)
{
	t_env* curr = *head;
	
	// while (curr->next != NULL) 
	while (curr != NULL)
	{
		if(!ft_strcmp(curr->name, name))
		{
			if(curr->data != NULL)
				free(curr->data);
			if(!data)
				curr->data = ft_strdup("\0");
			else
				curr->data = ft_strdup(data);
			return ;
		}
        curr = curr->next;
    }
	return ;
}

void	join_env_data(t_env** head,char *name, char *data)
{
	t_env* curr = *head;
	
	// while (curr->next != NULL)
	while (curr != NULL) 
	{
		if(!ft_strcmp(curr->name, name))
		{
			if(curr->data != 0)
				curr->data = ft_mhjoin(curr->data, data);
			else
				curr->data = ft_strdup(data);
			return ;
		}
        curr = curr->next;
    }
	return ;
}

void	join_export(t_mhstruct *mh, char *tdata)
{
	t_env	*node = NULL;
	char	*line;
    char	*name;
    char	*data;
	char	*tmp;
	
    line = ft_strdup(tdata);
	tmp = ft_strchr(line, '+');
	*tmp = '\0';
	name = ft_strdup(line);
	*tmp = '0';
	tmp++;
	tmp++;
	data = ft_strdup(tmp);
	if(!check_env_name(&mh->env, name))
	{
    	node = create_env_node(name, data);
    	if (node != NULL) 
        	insert_env_node(&mh->env, node);
	}
	else
		join_env_data(&mh->env, name, data);
    free(line);
	free(name);
	if(data != NULL)
		free(data);
	return ;
}

// make this function /\ like this \/ 

void	add_export(t_mhstruct *mh, char *tdata)
{
	t_env	*node;

	node = NULL;
	// put this shit to another function
	mh->utils->data = NULL;
	mh->utils->line = ft_strdup(tdata);
	mh->utils->tmp = ft_strchr(mh->utils->line, '=');
	mh->utils->tmp[0] = '\0';
	mh->utils->name = ft_strdup(mh->utils->line);
	mh->utils->tmp[0] = '0';
	mh->utils->tmp++;
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
	return ;
}

int	export(t_mhstruct *mh, char *tdata)
{
	int	i;

	i = 0;
	while (tdata[i])
	{
		if (tdata[i] == '+')
		{
			if (tdata[i + 1] != '=')
				return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10] \
				, tdata)), 1);
			else if (tdata[i + 1] == '=')
			{
				join_export(mh, tdata);
				return (1);
			}
		}
		else if (tdata[i] == '=')
		{
			add_export(mh, tdata);
			return (1);
		}
		i++;
	}
	return (1);
}

void	add_key(t_mhstruct *mh, char *tdata)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	while (tdata[i])
	{
		if (tdata[i] == '+')
			return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)));
		i++;
	}
	if (!check_env_name(&mh->env, tdata))
	{
		node = create_env_node(tdata, NULL);
		if (node != NULL)
			insert_env_node(&mh->env, node);
	}
	else
		return ;
}

void	export_print(t_mhstruct *mh) //only print
{
	t_env	*curr;

	curr = mh->env;
	while (curr != NULL)
	{
		printf("declare -x %s", curr->name);
		if (curr->data != NULL)
			printf("=\"%s\"\n", curr->data);
		else
			printf("\n");
		curr = curr->next;
	}
}

void	builtin_export(t_mhstruct *mh)
{
	t_token	*token;

	token = mh->token->next;
	if (token == NULL )
		return (export_print(mh));
	while (token != NULL)
	{
		while (1)
		{
			if (handle_for_export(mh, token->data) == 1)
				break ;
			if (ft_strchr(token->data, '='))
			{
				if (export(mh, token->data) == 1)
					break ;
			}
			else
			{
				add_key(mh, token->data);
				break ;
			}
		}
		token = token->next;
	}
	return ;
}
