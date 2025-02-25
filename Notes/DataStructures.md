** Different Data structures and when to use them:

1. Arrays
Description: Fixed-size collection of elements of the same type.
When the size of the data is known at compile-time.
Accessing elements by index is frequent (O(1)).
Example: Storing monthly temperatures.

2. Vectors (std::vector)
Description: Dynamic array that resizes automatically.

When the size of data can change dynamically.
Random access and iterative traversal are required.
Example: Managing a dynamic list of users in an application.

3. Linked Lists
Description: Linear data structure where elements are linked using pointers.
Variants: Singly, Doubly, and Circular linked lists.
When frequent insertions/deletions are required.
Sequential access is sufficient.
Example: Implementing queues or stacks.

4. Stacks (std::stack)
Description: LIFO (Last In, First Out) data structure.
Managing function calls (call stack).
Undo operations in editors.
Depth-First Search (DFS) in graph algorithms.

5. Queues (std::queue)
Description: FIFO (First In, First Out) data structure.
Managing tasks in order of arrival.
Breadth-First Search (BFS) in graph algorithms.
Example: Task scheduling in operating systems.

6. Priority Queues (std::priority_queue)
Description: Elements are ordered by priority.
When elements need to be accessed based on priority.
Example: Dijkstra's algorithm for shortest paths.

7. Sets (std::set, std::unordered_set)
Description: Collection of unique elements.
Checking the existence of elements efficiently.
Storing distinct values.
Example: Removing duplicates from an array.


8. Maps (std::map, std::unordered_map)
Description: Key-value pairs, where keys are unique.
Associative lookups (e.g., dictionaries).
Example: Counting word frequencies in a text.

9. Graphs
Description: Collection of nodes (vertices) and edges.
Modeling networks like social media, maps, or communication systems.
Example: Shortest path algorithms or network flows.

10. Heaps
Description: Specialized tree-based structure for priority queues.
Finding the minimum or maximum efficiently.
Example: Implementing a scheduler or a median finder.

11. Tries
Description: Specialized tree for storing strings.
Efficient searching of prefixes.
Example: Implementing autocomplete or dictionary applications.

12. Bitsets (std::bitset)
Description: Space-efficient array of bits.
Managing flags or performing bit manipulation.
Example: Solving problems involving bitmasks.

** C style array Vs std::vector Vs std::list
			C-Style Array					std::array		std::vector
Size			Fixed/Static					Fixed/Static		Dynamic
Memory efficiency	More efficient					More Efficient		Less efficient(May double its size on new allocation.)
Copying			Iterate over elements or use std::copy()	Direct copy: a2 = a1;	Direct copy: v2 = v1;
Passing to function	Passed by pointer				Passed by value		Passed by value	(size not available in function)
									or as std::span														
Size			sizeof a1 / sizeof *a1				a1.size()		v1.size()
			or std::size(a1) 				or std::size(a1)	or std::size(v1)

Use case		For quick access and when		    	Same as classic array 	When frequent additions/
			insertions/deletions not 		i	but safer and easier 	deletions might be needed
			frequently needed.				to pass and copy

** std::map and std::unordered_map
                   map              unordered_map
Ordering         increasing order    no ordering
                 of keys(by default) 

Implementation   Self balancing BST   Hash Table
                 like Red-Black Tree   

search time      log(n)               O(1) -> Average 
                                      O(n) -> Worst Case

Insertion time   log(n) + Rebalance   Same as search
                      
Deletion time    log(n) + Rebalance   Same as search
