#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct rb_s rb_t;
struct rb_s {
	rb_t *l, *r;
	int key, value, color;
};

#define RB_RED 1
#define RB_BLACK 0
#define RB_MAKE_ME_BLACK 2
#define BT_UPDATED 3
#define BT_INSERTED 4
#define COLOR(node) ((node == 0)? RB_BLACK : node->color)

int rb_insert(rb_t ** proot, const rb_t * x);
int rb_insert0(rb_t ** proot, const rb_t * x);
void rb_right_rotate(rb_t ** p);
void rb_left_rotate(rb_t ** p);
void rb_check_left(rb_t ** p);
void rb_check_right(rb_t ** p);

int _print_t(rb_t *tree, int is_left, int offset, int depth, char s[20][255])
{
char b[20];
int width = 5;

if (!tree) return 0;

sprintf(b, "(%02d)%c", tree->key, tree->color == RB_BLACK ? 'B' : 'R');

int left  = _print_t(tree->l,  1, offset,                depth + 1, s);
int right = _print_t(tree->r, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
for (int i = 0; i < width; i++)
s[depth][offset + left + i] = b[i];

if (depth && is_left) {

for (int i = 0; i < width + right; i++)
s[depth - 1][offset + left + width/2 + i] = '-';

s[depth - 1][offset + left + width/2] = '.';

} else if (depth && !is_left) {

for (int i = 0; i < left + width; i++)
s[depth - 1][offset - width/2 + i] = '-';

s[depth - 1][offset + left + width/2] = '.';
}
#else
int i;
for (i = 0; i < width; i++)
s[2 * depth][offset + left + i] = b[i];

if (depth && is_left) {

for (i = 0; i < width + right; i++)
s[2 * depth - 1][offset + left + width/2 + i] = '-';

s[2 * depth - 1][offset + left + width/2] = '+';
s[2 * depth - 1][offset + left + width + right + width/2] = '+';

} else if (depth && !is_left) {

for (i = 0; i < left + width; i++)
s[2 * depth - 1][offset - width/2 + i] = '-';

s[2 * depth - 1][offset + left + width/2] = '+';
s[2 * depth - 1][offset - width/2 - 1] = '+';
}
#endif

return left + width + right;
}

void print_t(rb_t *tree)
{
int i;
char s[20][255];
for (i = 0; i < 20; i++)
sprintf(s[i], "%80s", " ");

_print_t(tree, 0, 0, 0, s);

for (i = 0; i < 20; i++)
printf("%s\n", s[i]);
}

int rb_insert(rb_t ** proot, const rb_t * x)
{
	int ret = rb_insert0(proot, x);
	if ((*proot)->color != RB_BLACK)
		(*proot)->color = RB_BLACK;
	return ret;
}

int rb_insert0(rb_t ** proot, const rb_t * x)
{
	rb_t *root;
	root = *proot;
	if (root) {
		int ret;
		if (root->key > x->key) {
			ret = rb_insert0(&(root->l), x);
			if (ret == BT_INSERTED) {
				rb_check_right(proot);
			}
		} else if (root->key < x->key) {
			ret = rb_insert0(&(root->r), x);
			if (ret == BT_INSERTED) {
				rb_check_left(proot);
			}
		} else {	// root->key == key
			root->value = x->value;
			return BT_UPDATED;
		}
		return ret;
	} else {		// root == NULL, то есть (под)дерево пусто.
// создаём новый узел, если добавление
		*proot = (rb_t *) malloc(sizeof(rb_t));
		(*proot)->key = x->key;
		(*proot)->value = x->value;
		(*proot)->l = (*proot)->r = 0;
		(*proot)->color = RB_RED;
		return BT_INSERTED;
	}
}

void rb_left_rotate(rb_t ** p)
{
	rb_t *x = *p;
	(*p) = (*p)->r;
	x->r = (*p)->l;
	(*p)->l = x;
}
void rb_right_rotate(rb_t ** p)
{
	rb_t *x = *p;
	(*p) = (*p)->l;
	x->l = (*p)->r;
	(*p)->r = x;
}


void rb_check_right(rb_t ** p)
{
	rb_t *l = (*p)->l;//
	if ((*p)->color == RB_BLACK) {
		if (l->color == RB_MAKE_ME_BLACK) {
			(*p)->color = RB_RED;
			if (COLOR((*p)->r) == RB_RED) {
				l->color = (*p)->r->color = RB_BLACK;
			} else {
				l->color = RB_RED;
				if (COLOR(l->r) == RB_RED)
					rb_right_rotate(&((*p)->l));
				rb_left_rotate(p);
				(*p)->color = RB_BLACK;
			}
		}
	} else if (l->color == RB_RED) {
		(*p)->color = RB_MAKE_ME_BLACK;
	}
}

void rb_check_left(rb_t ** p)
{
	rb_t *r = (*p)->r;
	if ((*p)->color == RB_BLACK) {
		if (r->color == RB_MAKE_ME_BLACK) {
			(*p)->color = RB_RED;
			if (COLOR((*p)->l) == RB_RED) {
				r->color = (*p)->l->color = RB_BLACK;
			} else {
				r->color = RB_RED;
				if (COLOR(r->l) == RB_RED)
					rb_right_rotate(&((*p)->r));
				rb_left_rotate(p);
				(*p)->color = RB_BLACK;
			}
		}
	} else if (r->color == RB_RED) {
		(*p)->color = RB_MAKE_ME_BLACK;
	}
}

int main(void)
{
	rb_t *root = NULL, node;
	bzero(&node, sizeof(rb_t));
	int data[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}, i;
	printf("insert\n");
	node.key = data[0];
	rb_insert(&root, &node);
	for (i = 1; i < (int)(sizeof(data) / sizeof(data[0])); i++) {
		node.key = i;
		rb_insert(&root, &node);
	}
	printf("print tree\n");
	print_t(root);
	return 0;
}
