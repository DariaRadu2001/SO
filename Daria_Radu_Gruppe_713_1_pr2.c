#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	//ich lose die Aufgabe, indem ich unbennantes Pipe verwende
	int pid, p[2], n, preis, menge, lange;
	char obst[256];
	int retstatus;
	retstatus = pipe(p);
	//ich untersuche ob das Pipe erstellt ist
	if(retstatus == -1)
	{
		printf("Pipe konnte nicht erstellt werden!\n");
		return 1;
	}
	//ich untersuche ob das Kindprozzes erstellt ist
	pid = fork();
	if(pid == -1)
	{
		printf("Das Kindprozess konnte nicht erstellt werden\n");
		return 1;
	}
	//ich bin in dem Kindprozzes
	if(pid == 0)
	{
		printf("---Kind---\n");
		/*ich lese von der Tastatur das Anzahl der
		Fruchte die gekauft werden und tue das n in dem Pipe*/
		printf("Wv Fruchte wollen Sie kaufen n=");
		scanf("%d", &n);
		int i;
		//ich schliesse dem Weg fur Lesen
		close(p[0]);
		write(p[1], &n, sizeof(int));
		/*mit einem For Schleife lese ich n Fruchte
		die auch in dem Pipe geschrieben werden.
		Ich schreibe in dem Pipe in dieser Reihenfolge
		Lange des Strings obst
		Das String obst
		Das Integer preis
		Das Integer menge*/
		for(i = 0; i < n; i++)
		{
			printf("Frucht %d:", i+1);
			scanf("%s", obst);
			printf("Preis pro Kilo:");
                        scanf("%d", &preis);
			printf("Menge:");
                        scanf("%d", &menge);
			printf("\t %s %d %d \n", obst, preis, menge);
			lange = strlen(obst);
			write(p[1], &lange, sizeof(int));
			write(p[1], obst, strlen(obst));
			write(p[1], &preis, sizeof(int));
			write(p[1], &menge, sizeof(int));
		}
		//ich schiesse dem Weg fur Schreiben
		close(p[1]);
		printf("Diese sind meine Fruchte!\n");
		exit(0);
	}
	//ich bin im Eltern und warte bis das Kind ferig ist
	wait(0);
	printf("---Eltern---\n");
	//ich schiesse dem Weg fur Schreiben
	close(p[1]);
	//ich lese vom Pipe das Anzahl von Fruchte
	read(p[0], &n, sizeof(int));
	//n = 0 --> keine Fruchte in der Liste
	if(n == 0)
	{
		printf("Sie haben keine Fruchte in der Liste :( \n");
		return 0; 
	}

	int i;
	int kosten;
	int kosten_alles;
	kosten_alles = 0;
	/*Mit einer Schleife lese ich alle Fruchte von dem Pipe.
	Im kosten berechne ich die Kosten fur jedes Frucht un im kosten_alles
	berechne ich die gesamten Kosten*/
	for(i = 0; i < n; i++)
	{
		kosten = 1;
		read(p[0], &lange, sizeof(int));
		read(p[0], &obst, lange);
		read(p[0], &preis, sizeof(int));
		read(p[0], &menge, sizeof(int));
		//printf("%d %d\n", preis, menge);
		kosten = preis*menge;
		printf("%s kostet %d\n", obst, kosten);
		kosten_alles += kosten;

	}
	printf("Insgesamt sollen Sie %d Lei bezahlen\n", kosten_alles);
return 0;
}
