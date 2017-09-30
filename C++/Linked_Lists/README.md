# /independent/C++/Linked_Lists/

A library that contains the definition and many functions for the use of linked lists in C++.

# HOW TO USE:
 . The type List creates a linked list header type of structure. This structure can then be assigned elements. Each element is kept within a monad-like structure called a Node, which has a hold and a link mebers. In general, one does not need to use the nodes during the coding with linked lists.
 . If using a function that returns a linked list, use the Base class of List, RList. They are identical, with the exception that RList does not delete itself after the end of scope, while List does, in order to avoid memory leaks.
