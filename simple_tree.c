#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct tree_s tree_t;
struct tree_s {
	bool present;
	int data;
	tree_t *left;
	tree_t *right;
};

tree_t *create_node(void)
{
	tree_t *node = calloc(1, sizeof(tree_t));
	return node;
}


int _print_t(tree_t *tree, int is_left, int offset, int depth, char s[20][255])
{
char b[20];
int width = 5;

if (!tree) return 0;

sprintf(b, "(%03d)", tree->data);

int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

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

void print_t(tree_t *tree)
{
int i;
char s[20][255];
for (i = 0; i < 20; i++)
sprintf(s[i], "%80s", " ");

_print_t(tree, 0, 0, 0, s);

for (i = 0; i < 20; i++)
printf("%s\n", s[i]);
}

void insert(tree_t *root, int data)
{
	tree_t *node;
	node = root;
	if (root->present == false) {
		root->data = data;
		root->present = true;
		return;
	}

	for (;;) {
		if (node->data < data) {
			if (node->right != NULL) {
				printf("right\n");
				insert(node->right, data);
				return;
			} else {
				node->right = create_node();
				node->right->present = true;
				node->right->data = data;
				return;
			}
		} else if (node->data > data) {
			if (node->left != NULL) {
				printf("left\n");
				insert(node->left, data);
				return;
			} else {
				node->left = create_node();
				node->left->present = true;
				node->left->data = data;
				return;
			}
		}
	}
}

int main(void)
{
	tree_t *root;
	root = create_node();
	int data[] = {0,1,2,3,4,5,6,7,8,9}, i;
	if (root == NULL) {
		return 1;
	}
	printf("insert\n");
	for (i = 0; i < (int)(sizeof(data) / sizeof(data[0])); i++) {
		insert(root, data[i]);
	}
	printf("print tree\n");
	print_t(root);
	return 0;
}
