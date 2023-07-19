#include "../includes/minishell.h"

void builtin_pwd(t_mhstruct *mh) 
{
    char cwd[PATH_MAX];
	(void) mh;
	
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
    	    printf("%s\n", cwd); 
    return ;
}

t_env* create_env_node(const char* name, const char* data)
{
    t_env* node = (t_env*)malloc(sizeof(t_env));
    if (node != NULL) 
	{
        node->name = strdup(name);
		if(!data)
			node->data = NULL;
		else
        	node->data = strdup(data);
        node->next = NULL;
    }
    return node;
}

void insert_env_node(t_env** head, t_env* node) 
{
    if (*head == NULL) 
	{
        *head = node;
    }
	else 
	{
        t_env* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }
}

// void free_env_list(t_env** head) 
// {
//     t_env* curr = *head;
//     while (curr != NULL) {
//         t_env* temp = curr;
//         curr = curr->next;
//         free(temp->name);
//         free(temp->data);
//         free(temp);
//     }
//     *head = NULL;
// }

void builtin_env(t_mhstruct *mh)
 {
    t_env* curr = mh->env;
    while (curr != NULL) 
	{
		if(curr->data != NULL)
		{
        printf("%s=", curr->name);
        printf("%s\n", curr->data);
		}
        curr = curr->next;
    }
}

void add_oldpwd_node(t_mhstruct *mh)
{
    t_env	*node = (t_env*)malloc(sizeof(t_env));
	t_env	*curr;
    if (node != NULL) 
	{
        node->name = ft_strdup("OLDPWD");
        node->data = NULL; 
        node->next = NULL;
		if(mh->env == NULL)
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

void check_oldpwd(t_mhstruct *mh)
{
	t_env *temp = mh->env;
	int i = 0;
    while (temp != NULL) 
	{
        if(!ft_strcmp(temp->name, "OLDPWD"))
		{
			free(temp->data);
			temp->data = NULL;
			i++;
		}
        temp = temp->next;
    }
	if(i == 0)
	add_oldpwd_node(mh);
	
}

char *ft_mhjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *new;
	if(!s2)
		return(s1);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(!new)
		return 0;
	while(s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		new[i+j] = s2[j];
		j++;
	}
	new[i+j] = '\0';
	free(s1);
	return new;
}

char	**get_env_array(t_mhstruct *mh)
{
	char **out = NULL;
	int i = 0;
    t_env* currentEnv = mh->env;
    while (currentEnv != NULL)
    {
        i++;
        currentEnv = currentEnv->next;
    }
    out = (char **)malloc((i + 1) * sizeof(char *));
    if (!out)
        return NULL;
    i = 0;
    currentEnv = mh->env;
    while (currentEnv != NULL)
	{
        out[i] = ft_strdup(currentEnv->name);
		out[i] = ft_mhjoin(out[i], "=");
		out[i] = ft_mhjoin(out[i], currentEnv->data);
        currentEnv = currentEnv->next;
        i++;
    }
    out[i] = NULL;
	return (out);
}

void initializer_mh(char **env, t_mhstruct *mh)
{
	mh->env = NULL;
	t_env	*node;
	char	*line;
    char	*name;
    char	*data;
	char	*tmp;
	int i = 0;
	while(env[i])
	{
        line = ft_strdup(env[i]);
		tmp = line;
		if((tmp = ft_strchr(line, '=')))
		{
			*tmp = '\0';
			name = ft_strdup(line);
			*tmp = '0';
			tmp++;
			data = ft_strdup(tmp);
		}
        node = create_env_node(name, data);
        if (node != NULL) 
            insert_env_node(&mh->env, node);
        free(line);
		i++;
    }
	check_oldpwd(mh);
}
