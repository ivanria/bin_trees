#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "tree.h"

#define NUMBER_OF_NODES	10
#define MAX_VAL		10

int main(void)
{
	int *genTreeData(int n, int max_val)
	{
		extern int errno;
		int i, *values;
		if ((values = malloc(sizeof(int) * (n + 1))) == NULL) {
			fprintf(stderr, "function: %s(), line: %d, error: %s.\n", __func__, (__LINE__ - 1), strerror(errno));
			return NULL;
		}
		for (i = 0; i < n; i++) {
			values[i] = rand() % (max_val + 1);
		}
		values[i] = -1;
		return values;
	}

	int *tree_data;
#ifdef DEBUG
	extern int EF_ALIGNMENT, EF_PROTECT_FREE, EF_PROTECT_BELOW, EF_DISABLE_BANNER;
	EF_DISABLE_BANNER = 1;
	EF_PROTECT_FREE = 1;
	EF_ALIGNMENT = 0;
	if ((tree_data = genTreeData(NUMBER_OF_NODES, MAX_VAL)) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	EF_PROTECT_BELOW = 1;
	if ((tree_data = genTreeData(NUMBER_OF_NODES, MAX_VAL)) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	return 0;
#else
	if ((tree_data = genTreeData(NUMBER_OF_NODES, MAX_VAL)) == NULL) {
		exit(EXIT_FAILURE);
	}
	free(tree_data);
	return 0;
#endif
}
