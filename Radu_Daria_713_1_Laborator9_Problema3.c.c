#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>


int main()
{
//pid und pid2 fur die Prozesse und p[2] fur dem Pipe
 int pid, p[2], pid2;
 char text[100];
 int retstatus = pipe(p);
//ich untersuche ob das Pipe erfolgreich erstellt wurde
 if(retstatus == -1)
 {
	printf("Pipe kann nicht erstellt weredn!\n");
	return 1;
 }
//Prozess 1 wo ich vom Tastatur ein Text lese
 if((pid=fork()) == 0)
 {
	printf("Geben sie ein Text bitte:");
        scanf("%[^\n]", text);
	close(p[0]);

	printf("Proces 1 printare %s \n", text);
	write(p[1], &text, 100);

	close(p[1]);
        exit(0);
}
 wait(0);
//ich warte bis das erstes Prozess zu Ende ist
//das 2. Prozess wo ich 'aeiou' mit '12345' verschiebe
if((pid2=fork()) == 0)
 {
        read(p[0], &text, 100);
	int s = strlen(text);
	/* s->Lange des Textes das ich in dem ersten Prozess gelesen habe
	Ein for bis am Ende des Textes und ich verschiebe die Vokalen
	mit die gegenenen Ziffern*/
	for(int i = 0; i < s; i++)
	{
		if(text[i] == 'a')
			text[i] = '1';

		if(text[i] == 'e')
                        text[i] = '2';

		if(text[i] == 'i')
                        text[i] = '3';

		if(text[i] == 'o')
                        text[i] = '4';

		if(text[i] == 'u')
                        text[i] = '5';

	}
	//ich schliesse das Weg fur Lesen
	close(p[0]);
	printf("proces 2 printare %s \n", text);
	//ich schreibe in dem Pipe das Text
	write(p[1], &text, 100);
        //ich schliesse das Weg fur Schreiben
	close(p[1]);
	exit(0);
 }
 //ich warte bis das 2 Prozess zum Ende kommt
 wait(0);
 //ich schliesse das Weg fur Schreiben
 close(p[1]);
 //ich lese aus dem Pipe das Text
 read(p[0], &text, 100);
 int s = strlen(text);
 bool ok = true;
 /*hier untersuche ich ob das text alphanummerisch ist, ob ja ich schreibe 
  das Text in dem Terminal*/
 for(int i = 0; i < s && ok == true; i++)
 {
	if(!isalpha(text[i]) && !isdigit(text[i]) && text[i] != ' ')
		ok = false;
 }

 if(ok)
   printf("proces 3 printare %s \n", text);
return 0;
}
