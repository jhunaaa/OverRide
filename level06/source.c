#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <stdlib.h>

int auth(char *login, unsigned int serial)
{
	unsigned int hash;
	size_t len;

	/* Remove the trailing newline added by fgets() */
	login[strcspn(login, "\n")] = '\0';

	len = strnlen(login, 32);

	if (len <= 5)
		return 1;

	/* Anti-debug check */
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
	{
		puts("******************");
		puts("* TAMPERING DETECTED *");
		puts("******************");
		return 1;
	}

	/* Initialize the hash using the 4th character of the login */
	hash = (login[3] ^ 4919) + 6221293;

	for (size_t i = 0; i < len; i++)
	{
		unsigned int value;

		if (login[i] <= 31)
			return 1;

		value = login[i] ^ hash;

		hash += value -
			((((value - ((unsigned long long)value * 2284010283ULL >> 32)) >> 1)
			+ (((unsigned long long)value * 2284010283ULL) >> 32))
			>> 10) * 1337;
	}

	return (serial == hash) ? 0 : 1;
}

int main(void)
{
	char login[32];
	unsigned int serial;

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(login, sizeof(login), stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");
	scanf("%u", &serial);

	if (auth(login, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return 0;
	}

	return 1;
}
