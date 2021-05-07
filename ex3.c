#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	int nr1, nr2, nr3, nr4;
	printf("nr1=");
	scanf("%d", &nr1);

	printf("nr2=");
        scanf("%d", &nr2);

	printf("nr3=");
        scanf("%d", &nr3);

	printf("nr4=");
        scanf("%d", &nr4);

	int a[4] = {nr1, nr2, nr3, nr4};
	int pid, p[2];
	pipe(p);
	pid = fork();

	if(pid == 0)
	{
	close(p[0]);
	a[2] -= a[3];
	write(p[1], &a[2], sizeof(int));
	exit(0);
	}
	close(p[1]);
	a[0] += a[1];
	read(p[0], &a[2], sizeof(int));
	close(p[0]);
	wait(0);
	a[0] = a[0]*a[2];
	printf("%d\n", a[0]);
	return 0;
}

