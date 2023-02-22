/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:47:59 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/22 14:49:23 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_child(t_pipex pipex)
{
	char *str;

	str = ft_strjoin("/bin/", pipex.argOptions1[0]);
	
	execve(str, pipex.argOptions1, pipex.envVec);
}

void second_child(t_pipex pipex)
{

	char *str;

	str = ft_strjoin("/bin/", pipex.argOptions2[0]);
	
	execve(str, pipex.argOptions2, pipex.envVec);

}