/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:56:33 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/26 13:59:16 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// ./pipex file1 cmd1 cmd2 file2
//
//
//			STRUCTURE
//
//	  au total : 3 process et un pipe
// 	 1 main process et deux child process pour les deux commandes 
// 
//  exemple : infile.txt cat | wc -l outfile.txt
//  la commande cat va écrire le résutlat dans la pipe et non sur le terminal (on ferme donc l'écriture sur le terminal)
//  la commande wc -l va lire dans la pipe et non dans le terminal (on ferme donc la lecture sur le terminal)
//    
// 	  
//
//	input (keyboard input in terminal)= 0
//	output (when a command print text) = 1
//	fd1 write data
// 	fd0 read from 	



// utilité de créer des sous-processus : si pas de fork alors le processuc engendré remplacerait totalement le premier
// le fils sera en mesure de lire depuis pipefd[0] les informations fournies par son père dans pipefd[1] et inversement

#include "pipex.h"

int main(int ac, char **av, char **env)
{
	t_pipex pipex;
	
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	pipex.path_pos = path_pos(env);
	pipex.envVec = ft_split(pipex.path_pos, ':');
	pipex.argOptions1 = ft_split(pipex.cmd1, ' ');
	pipex.argOptions2 = ft_split(pipex.cmd2, ' ');
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac -1], O_RDWR, O_CREAT);
	if (pipex.infile != -1 && pipex.outfile != -1 && ac != 5)
		return(3);
	if (pipe(pipex.fd) == -1) // création pipe
			return(1);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return(2);
	if (pipex.pid1 == 0) // enfant 1 -> process pour notre première commande 
		second_child(pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0) // enfant 2 -> process de notre deuxieme commande
		first_child(pipex);
	else // père
			daddy(pipex);
	ft_free(pipex);
	return(0);
}

void daddy(t_pipex pipex)
{
			close(pipex.fd[0]);
			close(pipex.fd[1]);
			waitpid(pipex.pid1, NULL, 0);
			waitpid(
				pipex.pid2, NULL, 0);
}