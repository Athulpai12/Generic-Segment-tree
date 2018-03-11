# Generic-Segment-tree
The segment_tree.hpp contains the implementation of the generic segment tree. 
The test.cpp is used to test the implementation 


# Instructions to run
g++ -std=c++11 test.cpp
 


This repository is the implementation of a generic segment tree in three method

* segtree_iter class builds the tree in iterative fashion

* segtree_recur class build the tree in recursive fashion (here lambda function are used to implement recursion thus closures are 
   implemented through these.The capture is by reference .)

(both the above method use a container to store the tree ie it uses contiguous memory location)

* segtree_node builds the tree in brute force recusive fashion and uses a node class to store element is the array 
  and uses the heap memory to store the tree hence the tree is not stored contiguously thus is best to be used when 
  memory is to be stored on the heap .   (here lambda function are used to implement recursion thus closures are 
   implemented through these.The capture is by reference .)

* The classes uses SAFE_DELETE  thus avoids memory leak of any sort



This is a generic segment tree hence the each node can have 

*a set

*a multiset

*a vector

*a array 

*a linked list

*a primitive data type (int|float|double|char)

*any other type of data structure.

Only this that needs that need to be pass are the type stored in each node and the function to calculte the inner nodes from the 
leaf nodes

*******************************************************

