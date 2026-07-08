
int read_number(int t[100])
	int unum;

	printf("index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, *(_DWORD *)(a1 + 4 * unum));
	return 0;
	}


int main(void) {
	int t[100];
	char s[20];

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
		fgets(s, 20, stdin);
		s[strlen(s) - 1] = 0;
		number = 1;
		if (strcmp("store", s) == 0) {
			number = store_number(t);
		}
		else if (strcmp("read", s) == 0) {
			number = read_number(t);
		}
		else if (strcmp("quit", s) == 0)
			return (0);
		else if (number) {
			printf(" Failed to do %s command\n", s);
		}
		else {
			printf(" Completed %s command successfully\n", s);
		}
	}
}
