/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:09:54 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/19 21:02:54 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_for_export(t_mhstruct *mh)
{
	char *arg = mh->afex;
	int i = 1;
	
	if(!ft_isalpha(arg[1]))
	{
		printf("minihell: export: %s : not a valid identifier\n", mh->afex);
		mh->er_num = 1;
		return 1;
	}
	while(arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if(!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("minihell: export: %s : not a valid identifier\n", mh->afex);
			mh->er_num = 1;
			return 1;
		}
		i++;
	}
	return 0;
}

int check_env_name(t_env** head,char *name)
{
	t_env* curr = *head;
	
	while (curr->next != NULL) 
	{
		if(curr->name == name)
			return 1;
        curr = curr->next;
    }
	return 0;
}

void	change_env_data(t_env** head,char *name, char *data)
{
	t_env* curr = *head;
	
	while (curr->next != NULL) 
	{
		if(curr->name == name)
		{
			if(curr->data != 0)
				free(curr->data);
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
	
	while (curr->next != NULL) 
	{
		if(curr->name == name)
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

void	join_export(t_mhstruct *mh)
{
	t_env	*node = NULL;
	char	*line;
    char	*name;
    char	*data;
	char	*tmp;
	
    line = ft_strdup(mh->afex);
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
	return ;
}

void	add_export(t_mhstruct *mh)
{
	t_env	*node = NULL;
	char	*line;
    char	*name;
    char	*data = NULL;
	char	*tmp;
	
    line = ft_strdup(mh->afex);
	tmp = ft_strchr(line, '=');
	*tmp = '\0';
	name = ft_strdup(line);
	*tmp = '0';
	tmp++;
	if(*tmp != '\0')
		data = ft_strdup(tmp);
	if(!check_env_name(&mh->env, name))
	{
    	node = create_env_node(name, data);
    	if (node != NULL) 
        	insert_env_node(&mh->env, node);
	}
	else
		change_env_data(&mh->env, name, data);
    free(line);
	return ;
}

int export(t_mhstruct *mh)
{
	char *arg = mh->afex;
	int i = 0;
	
	while(arg[i])
	{
		if(arg[i] == '+')
		{
			if(arg[i + 1] != '=')
			{
			printf("minihell: export: %s : not a valid identifier\n", mh->afex);
			mh->er_num = 1;
			return 1;
			}
			else if (arg[i + 1] == '=')
			{
				join_export(mh); 
				return 1;
			}
		}
		else if(arg[i] == '=')
			add_export(mh); // add return
			return 1;
		i++;
	}
	return 1;
}

void	add_key(t_mhstruct *mh)
{
	char *arg = mh->afex;
	int i = 0;
	t_env	*node = NULL;
    char	*name;
	
	while(arg[i])
	{
		if(arg[i] == '+')
		{
			printf("minihell: export: %s : not a valid identifier\n", mh->afex);
			mh->er_num = 1;
			return ;
		}
		i++;
	}
	if(!check_env_name(&mh->env, mh->afex))
	{
		node = create_env_node(name, NULL);
    	if (node != NULL) 
        	insert_env_node(&mh->env, node);
	}
	else
		return ;
}

void export_print(t_mhstruct *mh) //only print
 {
    t_env* curr = mh->env;
	
    while (curr != NULL) 
	{
        printf("declare -x %s", curr->name);
		if(curr->data != NULL)
        	printf("=\"%s\"\n", curr->data); 
		else
			printf("\n");
        curr = curr->next;
    }
}

void builtin_export(t_mhstruct *mh)
 {
	if(!mh->afex)
		export_print(mh);
	else
	{
		if(handle_for_export(mh) == 1)
			return ;
		if(!ft_strcmp(mh->afex, "="))
		{
			if(export(mh) == 1)
				return ;
		}
		else
			add_key(mh); // dont forget chek for +
	}
	return ;
}
