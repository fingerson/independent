# /independent/C++/Linked_Lists/

A library that contains the definition and many functions for the use of linked lists in C++.

## TL;DR
 * The type List creates a linked list header type of structure. This structure can then be assigned elements. Each element is kept within a monad-like structure called a Node, which has a hold and a link mebers. In general, one does not need to use the nodes during the coding with linked lists.
 * If using a function that returns a linked list, use the Base class of List, RList. They are identical, with the exception that RList does not delete itself after the end of scope, while List does, in order to avoid memory leaks.
 * Tuples are a pairing of stuff. Not more complicated than that.

## REFERENCE MANUAL
* [RList](https://github.com/Beoww/independent/blob/master/C%2B%2B/Linked_Lists/README.md#rlist)
	* [Supported Operators](#supported-operators)
		* [ostream <<](#ostream-)
		* [[ ]](#-)
		* [==](#-1)    
		* [!=](#-2)
		* [>](#-3)
		* [>=](#-4)
		* [<](#-5)
		* [<=](#-6)
		* [=](#-7)
		* [+=](#-8)
		* [+](#-9)
	* [Functions](#functions)
		* [Constructor](#constructor)
		* [append](#append)
		* [append_at](#append_at)
		* [append_list](#append_list)
		* [append_list_at](#append_list_at)
		* [assign_at](#assign_at)
		* [assign_from_array](#assign_from_array)
		* [contains](#contains)
		* [copy_list](#copy_list)
		* [delete_all](#delete_all)
		* [delete_at](#delete_at)
		* [has_elements](#has_elements)
		* [length](#length)
		* [peek](#peek)
		* [pop](#pop)
		* [prune_at](#prune_at)
		* [prune_from_to](#prune_from_to)
		* [push](#push)
		* [switch_holds](#switch_holds)
* [List](#list)
* [Tuple](#tuple)
	* [Supported Operators](#supported-operators-1)
		* [ostream <<](#ostream--1)
		* [==](#-11)
		* [!=](#-12)
		* [=](#-13)
	* [Functions](#functions-1)
		* [Constructor](#constructor-1)
		* [left](#left)
		* [right](#right)
* [Other Functions](#other-functions)
	* [foldl](#foldl)
	* [foldr](#foldr)
	* [head](#head)
	* [filter](#filter)
	* [init](#init)
	* [map_on](#map_on)
	* [reverse_list](#reverse_list)
	* [tail](#tail)
	* [zip](#zip)
* [Errors](#errors)
	* [std::domain_error](#stddomain_error)
		* [Peek is not defined for empty lists](#peek-is-not-defined-for-empty-lists)
		* [Cannot pop an empty list](#cannot-pop-an-empty-list)
		* [Head not defined for empty lists](#head-not-defined-for-empty-lists)
		* [Tail is not defined for empty lists](#tail-is-not-defined-for-empty-lists)
	* [std::out_of_range](#stdout_of_range)
		* [Access request to out of range node](#access-request-to-out-of-range-node)
		* [Append request at out of range position](#append-request-at-out-of-range-position)
		* [Assign request at out of range node](#assign-request-at-out-of-range-node)
		* [Deletion request at out of range node](#deletion-request-at-out-of-range-node)
		* [Switch request to at least one out of range node](#switch-request-to-at-least-one-out-of-range-node)

# RList
A class type that acts as a base for the List type. It works with dynamic memory allocation and can support multidimensional lists.

## Supported Operators
For the demonstration of the effects of each one of the operators, a simple list which contains the numbers 4 through 0 in regressive order will be used. Such a list can be obtained with a syntax similar to the one bellow (other syntaxes are also possible).
```c++
RList<int> my_list;
for(int i = 0; i <= 4; i++)
{
	my_list[i] = 4 - i;
}
```
We will also define other lists in similar ways for other operator examples:
```c++
// equal_list
RList<int> equal_list;
for(int i = 0; i <= 4; i++)
{
	equal_list[i] = 4 - i;
}

// shorter_list
RList<int> shorter_list;
for(int i = 0; i <= 3; i++)
{
	shorter_list[i] = 3 - i;
}
```
---

## ostream <<  
If used with std::cout, the syntax:
``` c++
std::cout << my_list << std::endl;
```
Will produce:

> [4,3,2,1,0]

It is important to notice that << has a special behavior when applied to lists of chars. For instance, the syntax
```
List<char> char_list;
char_list.assign_from_array("Test");
std::cout << char_list << std::endl;
```

Will produce:
> Test

This is so that it can be used as a string. If one does not want this type of behavior, a class that is analog to char and outputs the char when used with the operator << can be created and used.

---

## [ ]
If used with std::cout, the syntax:
``` c++
std::cout << my_list[3] << std::endl;
```
Will produce:
>  1

May throw the erros(s):  
[std::out_of_range("ERROR: Access request to out of range node.")](#access-request-to-out-of-range-node)

---

## ==
If used with std::cout, the syntax:
``` c++
std::cout << (my_list == equal_list ? "True" : "False") << std::endl;
std::cout << (my_list == shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> True  
> False

This operator compares each one of the elements in order to see if both lists are equal.

---

## !=
If used with std::cout, the syntax:
``` c++
std::cout << (my_list != equal_list ? "True" : "False") << std::endl;
std::cout << (my_list != shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> False  
> True

This operator compares each one of the elements in order to see if both lists are different.

---
## >
If used with std::cout, the syntax:
``` c++
std::cout << (my_list > equal_list ? "True" : "False") << std::endl;
std::cout << (my_list > shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> False  
> True

Since this operator compares the length of the lists.

---
## >=
If used with std::cout, the syntax:
``` c++
std::cout << (my_list > equal_list ? "True" : "False") << std::endl;
std::cout << (my_list > shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> False  
> True

Since this operator compares the length of the lists.

---

## <
If used with std::cout, the syntax:
``` c++
std::cout << (my_list < equal_list ? "True" : "False") << std::endl;
std::cout << (my_list < shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> False  
> False

Since this operator compares the length of the lists.

---

## <=
If used with std::cout, the syntax:
```c++
std::cout << (my_list <= equal_list ? "True" : "False") << std::endl;
std::cout << (my_list <= shorter_list ? "True" : "False") << std::endl;
```
Will produce:
> True  
> False

Since this operator compares the length of the lists.

---

## =
If used with std::cout, the syntax:
``` c++
List<int> another_list;
another_list = shorter_list;
std::cout << another_list << std::endl;
```
Will produce:
> [3, 2, 1, 0]  

This operator deletes all elements of the receiver list and attributes to it all of the elements that belong to the list on the right-hand side.

---

## +=
If used with std::cout, the syntax:
``` c++
List<int> yet_another_list;
yet_another_list = my_list;
yet_another_list += shorter_list;
std::cout << yet_another_list << std::endl;
```
Will produce:
> [4,3,2,1,0,3,2,1,0]  

Since this operator appends the list on the right-hand side to the end of the list on the left-hand side.

This operator also works with single values, for example, the syntax:
```c++
List<int> yet_another_list;
yet_another_list = my_list;
yet_another_list += 5;
std::cout << yet_another_list << std::endl;
```
Will produce:
> [4,3,2,1,0,5]  

In this case, the operator appends the element on the right-hand side to the end of the list on the left-hand side.

---

## +
If used with std::cout, the syntax:
``` c++
List<int> yet_another_list;
yet_another_list = my_list + shorter_list;
std::cout << yet_another_list << std::endl;
```
Will produce:
> [4,3,2,1,0,3,2,1,0]  

Since the + operator returns a RList equivalent to the two lists on each side concatenated.

This operator also works with single values, for example, the syntax:
```c++
List<int> yet_another_list;
yet_another_list = my_list + 5;
std::cout << yet_another_list << std::endl;
```
will produce the following result:
> [4,3,2,1,0,5]  

In this case, the operator returns a RList equivalent to the list on its left concatenated with the single element on its right.

---

## Functions

## Constructor
When initialized, the RList is an empty list.

## append
```c++
void append(T element);
```
element: An element of the type T that to be embedded in the list.

For example, syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.append(5);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0,5]  

---
## append_at
```c++
void append_at(int position, T element);
```
position: The position within the array the element will occupy after appending.
element: An element of the type T that to be embedded in the list.

For example, syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.append_at(2, 5);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,5,2,1,0]  

May throw the error(s):  
[std::out_of_range("ERROR: Append request at out of range position.")](#append-request-at-out-of-range-position)

---

## append_list
```c++
void append_list(const RList<T> &list_to_be_appended);
```
list_to_be_appended: The list that is concatenated after the first list.

For example, syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.append_list(shorter_list);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0,3,2,1,0]  

---


## append_list_at
```c++
void append_list_at(int position, const RList<T> &list_to_be_appended);
```
position: The position which the first element of the appended list will occupy after the appending.
list_to_be_appended: The list that is concatenated after the first list.

For example, syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.append_list(2, shorter_list);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,3,2,1,0,2,1,0]  

May throw the error(s):  
[std::out_of_range("ERROR: Append request at out of range position.")](#append-request-at-out-of-range-position)

---

## assign_at
```c++
void assign_at(int position, T element);
```
position: The position at which the assigned element will be held;
element: The element to be held in the list.

For example, syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.assign_at(3,7);
```
Will produce:
> [4,3,2,7,0]  

May throw the error(s):  
[std::out_of_range("ERROR: Assign request at out of range node.")](#assign-request-at-out-of-range-node)

---

## assign_from_array
```c++
void assign_from_array(T assigner_array[], int array_size)
```
assigner_array: The name of the array from which the elements are to be assigned to the list.
array_size: The size of the assigner_array, or, at least, the number of elements from the assigner_array that shall be assigned to the list.

For example, the syntax:
```c++
List<int> array_list;
int my_array[4] = {2,7,1,8};
array_list.assign_from_array(my_array, 4);
std::cout << array_list << std::endl;
```
Will produce:
> [2,7,1,8]  

<!---
This function also has the overloaded exception for char lists, which only takes an array:
```c++
void assign_from_array(char assigner_array[])
```

In this case, the syntax:
```c++
List<char> char_list;
char_list.assign_from_array("Test");
std::cout << char_list << std::endl;
```
Will produce:
>Test

The difference in the format of the cout output is explained in the section about the << operator for RLists.
--->

## contains
```c++
bool contains(const RList<T> &contained_list);
```
contained_list: The list which the function shall test to see if it is a subset of the list object which called the function.

The syntax:
```c++
std::cout << my_list << std::endl;
std::cout << shorter_list << std::endl;

std::cout << (my_list.contains(shorter_list)? "True" : "False") << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> [3,2,1,0]  
> True  

---

## copy_list
```c++
void copy_list(const RList<T> &list_to_be_copied);
```
list_to_be_copied: The list whose elements shall be transplanted to the caller object in the same order.

The syntax:
```c++
List<int> another_list;
another_list.copy_list(my_list);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0]  

Note that the behavior of the copy_list function is identical to the = operator.

---

## delete_all
```c++
void delete_all()
```
The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
another_list.delete_all();
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> []  

Since the delete_all function deletes all of the elements inside the list, turning it into an empty list.

---

## delete_at
```c++
void delete_at(int position);
```
position: The position of the element to be deleted.

The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
another_list.delete_at(3);
std::cout << another_list << std::endl;
```

Will produce:
> [4,3,2,1,0]  
> [4,3,2,0]  

May throw the error(s):  
[std::out_of_range("ERROR: Deletion request at out of range node.")](#deletion-request-at-out-of-range-node)

---

## has_elements
```c++
bool has_elements()
```

The syntax:
```c++
List<T> another_list;
std::cout << (another_list.has_elements() ? "True" : "False") << std::endl;
```
Will produce:
> False  

Since by default, the initialized list is an empty list (see Constructor).

---

## length
```c++
int length()
```

The syntax:
```c++
std::cout << my_list.length() << std::endl;
```
Will produce:
> 5  

Since it returns the total number of elements within the list.

---
## peek
```c++
T peek()
```
The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
std::cout << another_list.peek() << std::endl;
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> 0  
> [4,3,2,1,0]  

Since it returns the last element WITHOUT DELETING IT.

May throw the error(s):  
[std::domain_error("ERROR: Peek is not defined for empty lists.")](#peek-is-not-defined-for-empty-lists)

## pop
```c++
T pop()
```

The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
std::cout << another_list.pop() << std::endl;
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> 0  
> [4,3,2,1]  

Since it returns the last element AND DELETES IT.

May throw the error(s):  
[std::domain_error("ERROR: Cannot pop an empty list.\n")](#cannot-pop-an-empty-list)

## prune_at
```c++
void prune_at(int position)
```
The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
another_list.prune_at(3);
std::cout << another_list << std::endl;
```
Will produce:
>[4,3,2,1,0]  
>[4,3,2]  

Since it deletes the elements from (and including) the position to the end.

May throw the error(s):  
[std::out_of_range("ERROR: Deletion request at out of range node.")](#deletion-request-at-out-of-range-node)

---

## prune_from_to
```c++
void prune_from_to(int prune_start, int prune_end);
```

prune_start: The position of the first element to be deleted.
prune_end: The position of the last element to be deleted.

The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
another_list.prune_from_to(1,3);
std::cout << another_list << std::endl;
```

Will produce:
> [4,3,2,1,0]  
> [4,0]  

Since it deletes all elements from (and including) prune_start to (and including) prune_end.

May throw the error(s):  
[std::out_of_range("ERROR: Deletion request at out of range node.")](#deletion-request-at-out-of-range-node)

---

## push
```c++
void push(T element)
```
element: The element to be appended at the end of the list.

The syntax:
```c++
List<int> another_list;
another_list = my_list;
another_list.push(5);
std::cout << another_list << std::endl;
```
Will produce as output
> [4,3,2,1,0,5]  

Note that the push() and the append() functions are identical. The reason for such a redundancy is to include the terminology used when working with stacks.

---

## switch_holds
```c++
void switch_holds(int pos1, int pos2)
```
pos1: The position of the element to be put in position pos2.
pos2: The position of the element to be put in position pos1.

The syntax:
```c++
List<int> another_list;
another_list = my_list;
std::cout << another_list << std::endl;
another_list.switch_holds(1,4);
std::cout << another_list << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> [4,0,2,1,3]  

Since it switches two of the elements within a list.

May throw the error(s):  
[std::out_of_range("ERROR: Switch request to at least one out of range node.")](#switch-request-to-at-least-one-out-of-range-node)

---

## value_at
```c++
T value_at(int position)
```
position: The position of the value to be returned.

The syntax:
```c++
std::cout << my_list << std::endl;
std::cout << my_list.value_at(3) << std::endl;
```
Will produce:
> [4,3,2,1,0]  
> 1  

Since it returns the value of the element in position 3.

May throw the errors(s):  
[std::out_of_range("ERROR: Access request to out of range node.")](#access-request-to-out-of-range-node)

--- 

# List
The List class is for almost all regards, identical to its base, the RList class. The difference between the two are suddle. One of them lies within the Destructor: While the List DELETES ALL OF ITS ELEMENTS when an instance goes out of scope, the RList does not. This means that, in general, the List class should be used, since it supports all of the functions and operations of the RList class (including assignment between them), and its destructor prevents issues with memory leak, since the linked lists use dynamic memory allocation.

The second difference appears when attributing a RList to a List. Instead of copying each one of the elements and, in essence, rewriting all of the list to the receiving variable. The RList will instead give its first_node address to the List, who will act as a second header to the SAME LIST. This means that deleting one can yeld problems with the other. This is functionality serves the purposes explained bellow.

There are, however, cases which cannot be properly done with Lists, like the return of functions, in those cases, one should use the RList type (The R comes from this situation and stands for Return).

---
# Tuple

Tuple is a type of structure that contains two elements in a pairing, and they can be of different types.

## Supported Operators
For the purpose of demonstration, the following tuples will be defined:
```c++
Tuple<int,float> my_tuple(4, 2.718);
Tuple<int,float> different_tuple(2, 6.2831);
```

## ostream <<
Using std::cout, the syntax:
```c++
std::cout << my_tuple << std::endl;
```
Will produce:
> (4,2.718)  

---
## ==
Using std::cout, the syntax:
```c++
std::cout << (my_tuple == different_tuple ? "True" : "False") << std::endl;
```
Will produce:
> False  

Since the  == operator compares both elements in both tuples in order to see if they are equal.

## !=
Using std::cout, the syntax:
```c++
std::cout << (my_tuple != different_tuple ? "True" : "False") << std::endl;
```
Will produce:
> True  

Since the  != operator compares both elements in both tuples in order to see if they are different.

## =
```c++
Tuple<int, float> new_tuple;
new_tuple = my_tuple;
std::cout << new_tuple << std::endl;
```
Will produce:
> (4,2.718)  

The operator = assigns the right-hand side tuple to the left-hand side one.

---

## Functions

## Constructor
The Tuple class has two different constructors. The first:
```c++
Tuple()
```
Takes no arguments and initializes its parameters with their basic constructors, and
```c++
Tuple(T left, S right)
```
assigns the element left to its member element left_elem and right to its member element right_elem.

## left
```c++
T& left()
```
The syntax
```c++
std::cout << my_tupple.left() << std::endl;
```
Will produce:
> 4  

Since it returns the caller object's left_elem.

Note that the const version of the left() function returns has a return type T, and not T&, since by definition, the parameters should not be changed.

---

## right
```c++
S& right()
```
The syntax
```c++
std::cout << my_tupple.right() << std::endl;
```
Will produce:
> 2.718  

Since it returns the caller object's right_elem.

Note that the const version of the right() function returns has a return type S, and not S&, since by definition, the parameters should not be changed.

---

# Other functions
For demonstration purposes, the following variables will be defined:
```c++
List<int> list_1;
for(int i = 0; i <= 9; i++)
{
	list_1[i] = 9 - i;
}

List<int> list_2
for(int i = 0; i <= 4; i++)
{
	list_2[i] = i;
}
```

And the syntax
```c++
std::cout << list_1 << std::endl;
std::cout << list_2 << std::endl;
```
Would produce
> [9,8,7,6,5,4,3,2,1,0]  
> [0,1,2,3,4]

We will also define three different functions
```c++
int sub_stuff(int a, int b){
	return a-b;
}

bool is_pair(int a){
	return (a%2? false : true);
}

int two_times(int a){
	return 2*a;
}
```

## foldl
```c++
T foldl(T (*f)(T, T), T x, const RList<T> &list_to_be_folded)
```
f: A function pointer to a function that receives two variables of type T and returns a type T value.
x: A folding value.
list_to_be_folded: A list on which the operation of folding will be done.

The syntax:
```c++
int answer = foldl(sub_stuff, 3, list_1);
std::cout << answer << std::endl;
```
Will produce:
> -42  

Since:
```math
(((((((((3 - 9) - 8) - 7) - 6) - 5) - 4) -3) -2) -1) - 0 = -42
```

---

## foldr
```c++
T foldr(T (*f)(T, T), T x, const RList<T> &list_to_be_folded)
```
f: A function pointer to a function that receives two variables of type T and returns a type T value.
x: A folding value.
list_to_be_folded: A list on which the operation of folding will be done.

The syntax:
```c++
int answer = foldr(sub_stuff, 3, list_1);
std::cout << answer << std::endl;
```
Will produce:
> 8  

Since:
```math
9 -(8 -(7 -(6 - (5 - (4 - (3 -(2 - (1 - 0)))))))) = 8
```

---

## head
```c++
T head(const RList<T> &list_to_be_headed)
```
list_to_be_headed: List whose first element will be returned.

The syntax:
```c++
int head_of_list = head(list_1);
std::cout << head_of_list << std::endl;
```
Will produce:
> 9  

Since head returns a non-empty list's first element.

May throw the error(s):  
[std::domain_error("ERROR: Head not defined for empty lists.\n")](#head-not-defined-for-empty-lists)

---

## filter
```c++
RList<T> filter(bool (*f)(T), const RList<T> &list_to_be_filtered)
```
f: A boolean filter function pointer.
list_to_be_filtered: A list that will provide the test elements for f.

The syntax:
```c++
List<int> filtered_list;
filtered_list = filter(is_pair, list_1);
std::cout << filtered_list << std::endl;
```

Will produce:
>[8,6,4,2,0]  

Since filter keeps all elements of the parameter list that return true when applied to the boolean filter function.

---

## init
```c++
RList<T> init(const RList<T> &list_to_be_inited)
```
list_to_be_inited: The list whose first elements will be returned.

The syntax:
```c++
List<int> inited_list;
inited_list = init(list_1);
std::cout << inited_list << std::endl;
```
Will produce:
> [9,8,7,6,5,4,3,2,1]  

Since init returns all elements but the last one.

---

## map_on
```c++
RList<T> map_on(T (*f)(T), const RList<T> &list_to_be_mapped)
```

f:  Function pointer of the function that will be mapped onto each element of the list.
list_to_be_mapped: List whose elements will be mapped into the return list through f.

The syntax:
```c++
List<int> mapped_list;
mapped_list = map_on(two_times, list_1)
std::cout << mapped_list << std::endl;
```
Will produce:
> [18,16,14,12,10,8,6,4,2,0]  

Since the function two_times doubles an int and each int within list_1 is doubled and appended to mapped_list.

---

## reverse_list
```c++
RList<T> reverse_list(const RList<T> list_to_be_reversed)
```
list_to_be_reversed: The list whose elements will be appended in reverse order to the return list.

The syntax:
```c++
List<int> reversed_list;
reversed_list = reverse_list(list_1);
std::cout << reversed_list << std::endl;
```
Will produce:
> [0,1,2,3,4,5,6,7,8,9]  

---

## tail
```c++
RList<T> tail(const RList<T> &list_to_be_tailed)
```
list_to_be_tailed: List who will provide its last elements to the return list.

The syntax:
```c++
List<int> tailed_list;
tailed_list = tail(list_1);
std::cout << tailed_list << std::endl;
```
Will produce:
>[8,7,6,5,4,3,2,1,0]  

Since tail leaves out the first element of the argument list.

May throw the error(s):  
[std::domain_error("ERROR: Tail is not defined for empty lists.")](#tail-is-not-defined-for-empty-lists)

---

## zip
```
RList< Tuple<T,S> > zip(const RList<T> &list_1, const RList<S> &list_2)
```

list_1: The list that will provide its first elements to the left elements of each tuple in the return tuple list.
list_2: The list that will provide its first elements to the right elements of each tuple in the return tuple list.

The syntax:
```c++
List< Tuple<int,int> > tuple_list;
std::cout << list_1 << std::endl;
std::cout << list_2 << std::endl;
tuple_list = zip(list1, lis2);
std::cout << tuple_list << std::endl;
```
Will produce:
> [9,8,7,6,5,4,3,2,1,0]  
> [0,1,2,3,4]  
> [(9,0),(8,1),(7,2),(6,3)(5,4)]  

Since zip returns a list with the length of the smaller of the argument lists.

---
# Errors
When the user tries to do some kind of forbidden action, some errors may be thrown.

## std::domain_error
Errors of this type are thrown when using a function on some kind of element not supported by the function itself. Similar to trying to calculate the square root of a negative number within the real set.

---

## Peek is not defined for empty lists
Since peek returns the last element of a list, it cannot be applied on an empty list, since it has no elements to remove.

May be thrown by [Rlist::peek](#peek).

---

## Cannot pop an empty list
Since pop returns and removes the last element of a list, it cannot be applied on an empty list, since it has no elements to remove nor return.

May be thrown by [Rlist::pop](#pop).

---

## Head not defined for empty lists
Since head returns the first element of the list, it cannot be applied to an empty list, since it has no elements to return.

May be thrown by [head](#head).

---

## Tail is not defined for empty lists
Since tail returns the one list but the first element, it cannot be applied to an empty list, since there is no first element to be removed.

May be thrown by [tail](#tail).

---

## std::out_of_range
Errors of this type are thrown when trying to access or change some element at an inexistent position in the list.

## Access request to out of range node.
Error thrown when trying to read or change some element at a position that does not exist in the list. As example, when a list is 8 elements long and the user tries to access the element at position 10. For the operator [] within RLists, the error is only thrown if one tries to assign a negative position.

May be thrown when using the [operator [] of RList](#-), [RList::value_at](#value_at).

---

## Append request at out of range position
Error thrown when trying to append at some position that does not exist in the list. As example, when the user tries to append something at position 10 of a list that contains only 8 elements.

May be thrown by [RList::append_at](#append_at), [RList::append_list_at](#append_list_at).

## Assign request at out of range node
Error thrown when trying to assing a value to a position that does not exist within the list. As example, when the user tries to assign a value to the position 10 of a list that is 8 elements long.

May be thrown by [RList::assign_at](#assign_at).

---

## Deletion request at out of range node
Error thrown when trying to delete an element at a position that does not belong to the list. As an example, this error will be thrown it one tries to delete the element at position 10 of a list that is 8 elements long.

May be thrown by [RList::delete_at](#delete_at), [RList::prune_at](#prune_at), [RList::prune_from_to](#prune_from_to).

## Switch request to at least one out of range node
Error thrown when at least one position to be switched does not exist within the list. As an example, if one tries to switch the sixth and the tenth element of a list that is 8 elements long, this error will be thrown.

May be thrown by [RList::switch_holds](#switch_holds).
