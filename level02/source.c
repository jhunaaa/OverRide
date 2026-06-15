#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char buf_1[49];
	char buf_2[100];
	char buf_3[112];
	FILE *fp = fopen("/home/users/level03/.pass", "r");
	if (!fp)
	{
		fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
		exit(1);
	}
	int var9 = fread(&buf_1, 1, 49, fp);
	if (var9 <= 0)
	{
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		exit(1);
	}
	fclose(fp);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(buf_2 ,100,stdin);
	printf("--[ Password: ");
	fgets(buf_3 ,100 ,stdin);
	if (!strcmp(buf_1, buf_3) == 0)
	{
		printf(&buf_2);
		puts(" does not have access!");
		exit(1);
	}
	printf("Greetings, %s!\n", buf_2);
	system("/bin/sh");
	return 0;
}
