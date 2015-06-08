#ifndef _THREE_H
#define _THREE_H

typedef enum {
	SUCC = 0,
	ERR
} RC_t;

typedef struct tree_s tree_t;
struct tree_s {
	int value;
	tree_t *left, *right;
}; 
tree_t *treeInit(void);

#endif /*_TREE_H*/
