/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:53:01 by arnaud            #+#    #+#             */
/*   Updated: 2023/02/21 18:03:07 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ./pipex file1 cmd1 cmd2 file2
//
//
//			STRUCTURE
//
//	  au total : 3 process et un pipe
// 	 1 main process et deux child process pour les deux commandes 
// 
//  exemple : cat infile.txt | wc -l
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

	int fd[2];
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	pipex.argVec = NULL;
	pipex.envVec = NULL;
	

	if(pipe(fd) == -1) // création pipe
	{
		printf("Erreur lors de la création du pipe");
		return(1);
	}
	pipex.pid1 = fork();  // création du fork après la pipe comme ca les FD sont également assignés aux nouveaux process mais restent indépendant
	// si on ferme un FD dans un process, celui qui à été dupliqué ne se ferme pas
	if (pipex.pid1 < 0)
	{
		printf("Erreur lors du fork");
		return(2);
	}
	if (pipex.pid1 == 0) // enfant -> process pour notre première commande 
	{
		close(fd[0]); // on a pas besoin de lire dans ce process 
		int i;
		printf("Je dois transmettre à mon fils une information.. Quel âge as-tu ? : \n");
		scanf("%d", &i);
		write(fd[1], &i, sizeof(int));
		close(fd[1]);

	}
	else // père
	{
		close(fd[1]);
		int j;
		read(fd[0], &j, sizeof(int));
		close(fd[0]);
		printf("Mon père m'a indiqué ton âge, tu as bien %d ans c'est ca ?", j);
	}
	


	return(0);
	
}