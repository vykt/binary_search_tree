#ifndef BTREE_H
#define BTREE_H

#define FIND_SUCCESS 0
#define FIND_FAIL 1
#define FIND_NOT_INIT 2

#define ADD_SUCCESS 0
#define ADD_EXISTS 1

#define INP_ERR -1
#define INP_SHOW_TREE -2
#define INP_ADD -3
#define INP_CHECK -4

typedef struct binary_tree btree_t;

struct binary_tree {

	long data;
	btree_t * prev_node;
	btree_t * smaller_node;
	btree_t * bigger_node;

};

#endif
