#include <stdio.h>
#include <stdlib.h>

int main()
{
	int pass;
	printf("***********************************\n* 	     -Level00 -		  *\n***********************************\n");
	scanf("%d", &pass);
	if (pass != 5276)
		printf("Invalid password.\n");
	else
	{
		printf("Password accepted.\n");
		system("/bin/sh");
	}
	return 0;
}
