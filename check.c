/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:54:20 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/22 13:47:49 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_all(int ac, const char *file1, const char *file2 )
{
	
	if (open(file1, O_RDWR) != -1 && open(file2, O_RDWR) != -1 && ac >= 5 && access(file1, (R_OK | W_OK)) == 0  && access(file2, (R_OK | W_OK)) == 0)
		{			
			return(0);
		}
	else	
			return(1);
}