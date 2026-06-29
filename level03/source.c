#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define Congrat 1
#define Failed 2

int decrypt(char a)
{
	char s1[]="Q}|u`sfg~sf{}|a3";
	char s2[]="Congratulations!";

	size_t i = strlen(s1);
	for (int j=0;j<i-1;j++) {
		s1[i] ^= a;
	}
	if (strcmp(s1, s2) == 0) {
		return Congrat;
	}
	else {
		return Failed;
	}
}

void test(int a, int b)
{
	switch(a-b)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			decrypt(a - b);
			break;
		default:
			int i = rand();
			decrypt(i);
			break;
	}

}

int main(void)
{
	int j;
	int i = 322424845;
	scanf("%i", &j);
	test(i, j);
}
