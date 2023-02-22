/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:56:33 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/22 15:01:25 by abeaudui         ###   ########.fr       */
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

	int fd[2];
	
	pipex.path_pos = path_pos(env);
	pipex.envVec = ft_split(pipex.path_pos, ':');


	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	
	pipex.argOptions1 = ft_split(pipex.cmd1, ' ');
	pipex.argOptions2 = ft_split(pipex.cmd2, ' ');


	if(check_all(ac, av[1], av[4]) == 0)
	{
		
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
		
		if (pipex.pid1 == 0) // enfant 1 -> process pour notre première commande 
		{
			first_child(pipex);
		
		}
		
		pipex.pid2 = fork();
		
		if(pipex.pid2 < 0)
		{
			
		}
		if (pipex.pid2 == 0) // enfant 2 -> process de notre deuxieme commande
		{
			second_child(pipex);
		}

		else // père
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pipex.pid1, NULL, 0);
			waitpid(pipex.pid2, NULL, 0);
		}
	}
	return(0);
	
}