#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int get_unum(void) {
	unsigned int unum;
	scanf("%u", &unum);
	return unum;
}

int read_number(int t[100]) {
	int unum;

	printf("index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, t[unum]);
	return 0;
}

int store_number(int t[100]) {
	int unum;
	int value;

	printf(" Number: ");
	value = get_unum();
	printf(" Index: ");
	unum = get_unum();
	if (unum % 3 == 0 || (value >> 24) == 0xb7) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}
	t[unum] = value;
	return 0;
}

int main(void) {
	int t[100];
	char s[20];
	int number;

	puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");

	while(true) {
		printf("Input command: ");
		number = 1;
		fgets(s, 20, stdin);
		s[strlen(s) - 1] = 0;
		if (memcmp("store", s, 5) == 0) {
			number = store_number(t);
		}
		else if (memcmp("read", s, 4) == 0) {
			number = read_number(t);
		}
		else if (memcmp("quit", s, 4) == 0)
			return (0);

		if (number) {
			printf(" Failed to do %s command\n", s);
		}
		else {
			printf(" Completed %s command successfully\n", s);
		}
		memset(s, 0, 5);
	}
}
