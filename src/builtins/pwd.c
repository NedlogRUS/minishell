/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:25:25 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/03 17:56:51 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void builtin_pwd(t_mhstruct *mh) 
{
    char cwd[PATH_MAX];
	
	mh->er_num = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
    	    printf("%s\n", cwd); 
    return ;
}