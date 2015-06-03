#include <stdio.h>

int main(void)
{
#ifdef DEBUG
	extern int EF_ALIGNMENT;
	EF_ALIGNMENT = 0;
#endif
	return 0;
}
