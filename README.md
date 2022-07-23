# binary_search_tree


### ABOUT:

This is an efficient implementation of binary search trees (BSTs) in C. Each node on the
tree is represented by a struct holding the addresses of the nodes under it. For
redundancy, the address of the previous node is included as well. The tree uses minimal
memory by only allocating space on the heap for each used node. This also means that
the table can grow indefinitely as long as space on the heap remains. The table is 
printed using a recursive function. Note however that this function only supports depth 
up to 256.



### INSTALLATION:

Build:
```
make
```

If gcc & make are unavailable, an ELF64 executable can be found inside ./bin.



### RUN:

Run the application:
```
./bstree
```



### INTERACT:

A menu is printed for the user upon launching the application. The following options
are available:
```
add <n>		- Add number to tree. First run initialises the tree. [E.g.: add 8]

check <n>	- Check if given number is present in initialised tree. [E.g.: check 8]

show tree	- Print tree to the screen. A '-' (minus) indicates that the node is
		  smaller (left), while '+' (plus) indicates that the node is bigger.
```

NOTE: Input for ```add``` and ```check``` functions uses ```scanf()```. ```scanf()``` is inherently
prone to buffer overflows. Getting input via ```getchar()``` or ```fgets()``` would take x3 times
as long and be somewhat irrelevant to the assignment, so I chose to stick with ```scanf()```.
Other forms of input validation are present.
