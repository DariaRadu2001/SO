#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#define FIFO "fifo_ub9"

int main(int argc, char* argv[])
{
	//ich verwende fifo und fifo2, um dem FIFO zu offnen
	int fifo,fifo2;
	int pid;
	//ich erledige dem FIFO
	if((mkfifo(FIFO, S_IRUSR | S_IWUSR)) == -1)
	{
		if(errno == EEXIST)
			perror("mkfifo()");
		else
		{
			perror("mkfifo()");
			exit(EXIT_FAILURE);
		}
	}
	//ich offne fur lesen-schreiben
	fifo2 = open(FIFO, O_RDWR);
	if(fifo2 < 0)
        {
                printf("vreau sa beau in tren\n");
                perror("open()");
                return(EXIT_FAILURE);

        }
	//ich bin in dem Kindprozess
	if((pid = fork()) == 0)
	{
		printf("---KIND---\n");
		DIR *d;
		struct dirent *dir;
		//ich offne dem Verzeichniss
		d = opendir(argv[1]);
		char filename[20][256];
		char mesaj_eroare[]="EROARE";
		int n = 0;
		/*wenn ich dem Verzeichnis nicht offnen kann, 
		  setzte ich in dem FIFO die Nachricht EROARE*/ 
		if(d == NULL)
		{
			printf("ERROARE la deschidere file\n");
			if((fifo = open(FIFO, O_RDWR)) < 0)
			{
				perror("open()");
				exit(EXIT_FAILURE);
			}
			write(fifo, &n, sizeof(int));
			write(fifo, &mesaj_eroare, strlen(mesaj_eroare));
                	close(fifo);
			exit(EXIT_FAILURE);

		}
		else
		{
			/*ich lese jede Datei aus der Verzeichnis und lege
			den Namen in dem filename*/
			while((dir = readdir(d)) != NULL)
			{
				strcpy(filename[n],dir->d_name);
				printf("File %d %s\n",n,filename[n]);
				n++;
			}
			//n ist der Anzahl von Dateien
			if((fifo = open(FIFO, O_RDWR)) == -1)
			{
                                perror("open()");
                                exit(EXIT_FAILURE);
                        }
			write(fifo, &n, sizeof(int));
			write(fifo, &filename, 20*256);
			close(fifo);

		}
		exit(0);
	}
	//ich bin in dem Elternprozess
	wait(0);
	printf("---Eltern---\n");
	int n;
	char filename[20][256];
	char mesaj_eroare[7];
	//ich lese aus FIFO der Anzahl von Dateien
	read(fifo2, &n, sizeof(int));
	/*ich habe keine Dateien, d.h. das Verzeichnis konnte
	 nicht geoffnet sein*/
	if(n == 0)
	{
		read(fifo2, &mesaj_eroare,7);
		mesaj_eroare[strlen(mesaj_eroare)]='\0';
		printf("%s\n",mesaj_eroare);
	}
	else
	{
		//ich lese alle alle Dateien aus dem PIPE
		read(fifo2, &filename, 20*256);
		int i;
		for(i = 0; i < n; i++)
			printf("File %d: %s\n", i, filename[i]);

	}
	close(fifo2);

printf("---ENDE---\n");
return 0;
}
