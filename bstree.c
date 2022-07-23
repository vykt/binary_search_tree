#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bstree.h"

#define MAX_TREE 128


void display_tree_layer(btree_t * tree_entry, uint8_t depth, char sign) {

	for (int i = 0; i < depth; i++) {
		putchar(' ');
		putchar(' ');
	}

	printf("%c%ld\n", sign, tree_entry->data);

	//Now check sublevels
	//If smaller entry exists
	if (tree_entry->smaller_node != NULL) {
		display_tree_layer(tree_entry->smaller_node, depth + 1, '-');
	}
	//If bigger entry exists
	if (tree_entry->bigger_node != NULL) {
		display_tree_layer(tree_entry->bigger_node, depth + 1, '+');
	}
}


void display_tree(btree_t * tree_root) {

	//First, check if tree exists
	if (tree_root == 0) {
		printf("Tree not yet initialised.\n");
	//Else it is initialised
	} else {
		printf("Binary tree:\n");
		//Recursively print binary tree
		display_tree_layer(tree_root, 0, NULL);

	} //End else
}


void display_menu() {

	puts("          --- MENU ---\nNumbers must be > 0. Decimal points are ignored. Enter one of the following options:\n\n> add <n>\n> check <n>\n> show tree\n\n");
}


//Initialise new tree entry by allocating memory for it & setting some default values.
void init_entry(btree_t ** tree_entry, btree_t * prev_tree_entry, long num) {

	*tree_entry = malloc(sizeof(btree_t));
	if (*tree_entry == NULL) {
		printf("Failed to initialise tree entry for num %ld.\n", num);
		exit(1);
	}

	(* tree_entry)->data = num;
	(* tree_entry)->prev_node = prev_tree_entry;
	(* tree_entry)->smaller_node = NULL;
	(* tree_entry)->bigger_node = NULL;
	
}


/*
 *	find_entry() and add_entry() are very similar and could be combined into a
 *	single function. However for the sake of giving each function only a single
 *	purpose, they have been separated.
 *
 */

int find_entry(btree_t * tree_root, long num) {

	//First, check if tree exists
	if (tree_root == 0) {
		return FIND_NOT_INIT;
	}

	//Otherwise
	btree_t * entry = tree_root;
	while (1) {
	
		//If its a match
		if (num == entry->data) return FIND_SUCCESS;
		
		//If num is smaller
		if (num < entry->data) {
			
			//If doesn't exist
			if (entry->smaller_node == NULL) {
				return FIND_FAIL;
			//Else if it does exist
			} else {
				entry = entry->smaller_node;
			}
		} //End if smaller

		//If num is bigger
		if (num > entry->data) {
			
			//If doesn't exist
			if (entry->bigger_node == NULL) {
				return FIND_FAIL;
			//Else if it does exist
			} else {
				entry = entry->bigger_node;
			}
		} //End if bigger

	} //End while
}


int add_entry(btree_t ** tree_root, long num) {

	//First check if any entry exists
	if (*tree_root == 0) {
		init_entry(tree_root, NULL, num);
		return ADD_SUCCESS;
	}

	//Otherwise
	btree_t * entry = *tree_root;
	while (1) {

		//If its a match
		if (num == entry->data) {
			return ADD_EXISTS;
		}
		
		//If num is smaller
		if (num < entry->data) {
			
			//If doesn't exist
			if (entry->smaller_node == NULL) {
				init_entry(&entry->smaller_node, entry, num);
				return ADD_SUCCESS;
			//Else if it does exist
			} else {
				entry = entry->smaller_node;
			}
		} //End if smaller

		//If num is bigger
		if (num > entry->data) {
			
			//If doesn't exist
			if (entry->bigger_node == NULL) {
				init_entry(&entry->bigger_node, entry, num);
				return ADD_SUCCESS;
			//Else if it does exist
			} else {
				entry = entry->bigger_node;
			}
		} //End if bigger

	} //End while

}


int get_inp(long * inp_cast) {

	char command[16];
	char num[16];

	fflush(stdin);

	//Get input
	printf("command: ");
	int scanf_ret1 = scanf("%15s %15s", command, num);

	//Check if user is asking to display table
	if (!strcmp(command, "show") && !strcmp(num, "tree")) return INP_SHOW_TREE;

	//Convert number part to long int
	*inp_cast = strtol(num, NULL, 10);
	if (*inp_cast < 1) return INP_ERR;

	if (!strcmp(command, "add")) return INP_ADD;
	if (!strcmp(command, "check")) return INP_CHECK;
	return INP_ERR;
}


int main(int argc, char ** argv) {

	//Define tree
	btree_t * tree_root = 0;
	printf("Press Ctrl+C to terminate.\n\n");	
	display_menu();

	int ret_inp;
	int ret_func;
	long num;

	while (1) {

		ret_inp = get_inp(&num);
		printf("ret_inp: %d\n", ret_inp);

		if (ret_inp == -1) puts("Invalid input.");
		if (ret_inp == -2) display_tree(tree_root);
		if (ret_inp == -3) {
			ret_func = add_entry(&tree_root, num);
			switch(ret_func) {
				case ADD_SUCCESS:
					puts("Number added.");
					break;
				case ADD_EXISTS:
					puts("Number already exists.");
			}
		} else if (ret_inp == -4) {
			ret_func = find_entry(tree_root, num);
			switch(ret_func) {
				case FIND_SUCCESS:
					puts("Found in tree.");
					break;
				case FIND_FAIL:
					puts("Not found in tree.");
					break;
				case FIND_NOT_INIT:
					puts("Add numbers to the tree first.");
					break;
				default:
					puts("This should never happen...");
					break;
			}
		}

	}
	return 0;
}
