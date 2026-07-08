#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

static void log_wrapper(FILE *log_file, const char *prefix, const char *filename)
{
	char buffer[264];

	strcpy(buffer, prefix);

	snprintf(
		buffer + strlen(buffer),
		254 - strlen(buffer),
		"%s",
		filename
	);

	buffer[strcspn(buffer, "\n")] = '\0';

	fprintf(log_file, "LOG: %s\n", buffer);
}

int main(int argc, char *argv[])
{
	FILE *log_file;
	FILE *src;
	int dst_fd;
	int c;
	char path[104];

	if (argc != 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return 1;
	}

	log_file = fopen("./backups/.log", "w");
	if (log_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(EXIT_FAILURE);
	}

	log_wrapper(log_file, "Starting back up: ", argv[1]);

	src = fopen(argv[1], "r");
	if (src == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	strcpy(path, "./backups/");
	strncat(path, argv[1], sizeof(path) - strlen(path) - 1);

	dst_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (dst_fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((c = fgetc(src)) != EOF)
	{
		write(dst_fd, &c, 1);
	}

	log_wrapper(log_file, "Finished back up ", argv[1]);

	fclose(src);
	fclose(log_file);
	close(dst_fd);

	return 0;
}
