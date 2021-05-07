#include <stdio.h>
//mit diese Funktion 
void merge(FILE *fp, FILE *fp2)
{
	//ich speichere in eine Variable die Lange fur eine Reihe
	int lungime = 256;
	//line1 ist eine Variable fur jede Reihe aus der ersten Datei
	//line2 ist die selbe aber fur die zweite Datei
	char line1[lungime];
	char line2[lungime];
	//ich lese die ersten Reihen aus jeder Datei
	fgets(line1, lungime, fp);
	fgets(line2, lungime, fp2);
	//ein unendliches loop, indem ich break Operators habe
	while(1)
	{
	//wir nehmen jedes Charakter aus der 2 Zeilen und vergleichen sie
	//i ist die Position wo die 2 Charakter verschieden sind
	int i= 0;
	while(line1[i] == line2[i])
		i++;

	//ob das Zeichen aus der erste Datei kleiner ist,
	// dann zeigen wir die Zeile aus fp 
	if(line1[i] < line2[i])
	{
		printf("%s", line1);
		//wenn wir am Ende der erste Datei sind zeigen wir
		//die Zeile von fp2 und break
		if(fgets(line1, lungime, fp) == NULL)
		{
			printf("%s", line2);
			break;
		}
	}
	else
	{	//das Zeichen von fp2 ist kleiner
		printf("%s", line2);
		//wir sind am Ende der zweite Datei, wenn fgets uns NULL gibt 
	      	if(fgets(line2, lungime, fp2) == NULL)
		 {
     			   printf("%s", line1);
 			   break;
		}
	}

	}

//ich nehme weiter jede Datei bis sie zum Ende ist
while(fgets(line1, lungime, fp) != NULL)
	printf("%s", line1);

while(fgets(line2, lungime, fp2) != NULL)
        printf("%s", line2);


}


//hier habe ich dem main, wo ich nur die Dataien, die ich als Argumente offne
int main( int argc, char *argv[])
{
	FILE *fp;
	FILE *fp2;
	//ich offne beide Dateien fur lesen
	fp = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	//ich aufrufe die Funktion
	merge(fp, fp2);
	//ich schliesse beide Dateien
	fclose(fp);
	fclose(fp2);
	return 0;
}
