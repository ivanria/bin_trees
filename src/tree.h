#ifndef _THREE_H
#define _THREE_H

typedef enum {
	ERROR	= -1,
	SUCCESS	= 0,
} RC_t;

typedef struct tree_s Tree_t;
struct tree_s {
	int value;
	Tree_t *left, *right;
}; 

RC_t PrinTree(void);

#endif /*_TREE_H*/
