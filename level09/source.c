#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int secret_backdoor()
{
	char s[128];

	fgets(s, 128, stdin);
	return system(s);
}

void set_username(char *msg)
{
	char username[128];
	int i;

	memset(username, 0, sizeof(username));

	puts(">: Enter your username");
	printf(">>: ");
	fgets(username, sizeof(username), stdin);

	for (i = 0; i <= 40; i++)
	{
		if (username[i] == '\0')
			break;

		msg[140 + i] = username[i];
	}

	printf(">: Welcome, %s", msg + 140);
}

void set_msg(char *msg)
{
	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(buffer, sizeof(buffer), stdin);
	strncpy(msg, buffer, *(unsigned char *)(msg + 180));
}

void handle_msg(void)
{
	struct
	{
		char message[140];
		char username[40];
		unsigned int msg_len;
	} data;

	memset(&data, 0, sizeof(data));

	data.msg_len = 140;

	set_username((char *)&data);
	set_msg((char *)&data);

	puts(">: Msg sent!");
}

int	main(void)

{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
	handle_msg();
	return 0;
}
