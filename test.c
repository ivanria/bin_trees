#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include "tree.h"

#define MAX_VAL		10
#define MIN_VAL		0
#define VAL_RANGE	(MAX_VAL - MIN_VAL)
#define NUMBER_OF_NODES	VAL_RANGE
#define CASSERT(EXPR)	switch (0) {case 0: case (EXPR):;}

struct winsize win_size;

int main(void)
{
	CASSERT(MAX_VAL > MIN_VAL);
	int *genTreeData(void)
	{
		extern int errno;
		int i, *values, tmp, j;
		if ((values = malloc(sizeof(int) * NUMBER_OF_NODES)) == NULL) {
			fprintf(stderr, "function: %s(), line: %d, error: %s.\n", __func__, (__LINE__ - 1), strerror(errno));
			return NULL;
		}
		memset(values, MIN_VAL - 1, NUMBER_OF_NODES);
		for (i = 0; i < NUMBER_OF_NODES; i++) {
REPEAT:
			tmp = rand() % (VAL_RANGE + 1) - (MIN_VAL > 0 ? 0 : abs(MIN_VAL));
			for (j = 0; j <= i; j++) {
				if (tmp == values[j])
					goto REPEAT;
			}
			values[i] = tmp;
		}
#ifdef DEBUG
		for (i = 0; i < NUMBER_OF_NODES; i++)
			printf("%d ", values[i]);
		printf("\n");
#endif
		return values;
	}

	int *tree_data;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);

#ifdef DEBUG
	extern int EF_ALIGNMENT, EF_PROTECT_FREE, EF_PROTECT_BELOW, EF_DISABLE_BANNER;
	EF_DISABLE_BANNER = 0;
	EF_PROTECT_FREE = 1;
	EF_ALIGNMENT = 0;
	if ((tree_data = genTreeData()) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	EF_PROTECT_BELOW = 1;
	if ((tree_data = genTreeData()) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	return 0;
#else
	if ((tree_data = genTreeData()) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	return 0;
#endif
}

