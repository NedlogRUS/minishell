/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apanikov.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:29:30 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/17 21:44:25 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APANIKOV_H
# define APANIKOV_H

# include "minishell.h"


void builtin_pwd(t_mhstruct *mh);
t_env* create_env_node(const char* name, const char* data);
void insert_env_node(t_env** head, t_env* node);
void builtin_env(t_mhstruct *mh);
void builtin_export(t_mhstruct *mh);
void add_oldpwd_node(t_mhstruct *mh);
void check_oldpwd(t_mhstruct *mh);
void initializer_mh(char **env, t_mhstruct *mh);

#endif