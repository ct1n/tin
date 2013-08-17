#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int f;
	off_t o;
	unsigned char buf[512];

	if (argc != 2) {
		fprintf(stderr, "Usage: mkboot file\n");
		return 1;
	}

	f = open(argv[1], O_WRONLY);
	if (f < 0) {
		perror("open");
		return 1;
	}

	o = lseek(f, 0, SEEK_END);
	if (o > 510) {
		fprintf(stderr, "%s too large: %d bytes\n", argv[1], o);
		return 1;
	}

	memset(buf, 0, 510);
	buf[510] = 0x55;
	buf[511] = 0xAA;
	write(f, buf + o, 512 - o);

	close(f);

	return 0;
}
