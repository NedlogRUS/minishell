/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:09:54 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/18 18:27:20 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void builtin_export(t_mhstruct *mh) //only print
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

