#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

//mit diese Funktion wandle ich alle grosse Buchstaben in kleinen Buchstaben
void transform(char* text)
{
	//die Lange des Texts
	int s = strlen(text);
	int i;
	for(i = 0; i < s; i++)
	{
		//wenn die Buchstabe gross ist, wandle ich sie im kleiner Buchstabe um
		if('A' <= text[i] && text[i] <= 'Z')
			text[i] = tolower(text[i]);

	}

}

int main()
{

 int pi;
 //ich lese vom der Tastatur das Text
 printf("Geben Sie ein Text bitte: ");
 char text[256];
 scanf("%[^\n]", text);
 transform(text);
 char litere[27] = "abcdefghijklmnopqrstuvwxyz"; 
 int lungime = strlen(litere);

 for(int i = 0; i < lungime; i++)
 {

	//Lange des Textes
        int s = strlen(text);
        int j;
        int sum = 0;
	//ich erledige ein Kindprozzes
	if((pi=fork()) == 0)
 	{
		for(j = 0; j < s; j++)
		{
			if(text[j] == litere[i])
				sum++;
		}
	//ich zeige wv. Male jede Buchstabe aus dem Text vorkommt
	if(sum > 0)
		printf("Litera %c apare de %d ori \n",litere[i], sum);
	exit(0);
	}
 //ich warte bis das Kindprozess beschlossen ist
 wait(0);
 }
 wait(0);
 return 0;
}
