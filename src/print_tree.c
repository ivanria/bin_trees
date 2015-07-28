#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "tree.h"

RC_t PrinTree(void)
{
	struct winsize ws;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0) {
		perror("ioctl winsize");
		return ERROR;
	}
	fprintf(stderr, "column: %d\n", ws.ws_col);
	return SUCCESS;
}
