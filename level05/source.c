#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buff[100];

	fgets(buff, 100, stdin);

	for (int i = 0; i < 100; i++)
	{
		if (buff[i] > 64 && buff[i] <= 90)
			buff[i] += 32;
	}
	printf(&buff);
	exit(0);
}
