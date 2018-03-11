#include<iostream>
#include <set>
#include "segment_tree.hpp"
int main()
{
	std::function<int(int,int)> adder = [](int a, int b)->int
	{
	return 	a+b;
	};
	std::function<int(int,int)> sub = [](int a, int b)->int
	{
	return 	a+b;
	};
	std::function<int(int,int)> multiplier = [](int a, int b)->int
	{
	return 	a*b;
	};
  /***** test for primitive type 
         like int 

         ****/
	std::vector<int> v={1,2,3,4,5,6,7,8,9,10};
	segtree_recur<int> st_recur(100000,1,multiplier);
	segtree_iter<int>  st_iter(100000,1,multiplier);
	segtree_node<int>  st_node(100000,1,multiplier);
	std::cout<<"time-recursive-- "<<st_recur.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node.time_taken()<<"\n";

	st_iter.update_iter(2,10,2);
	st_recur.update_recur(2,10,2);
	st_node.update_node(2,10,2);
	std::cout<<"top ele recur"<<st_recur.top()<<"\n";
	std::cout<<"top ele iter"<<st_iter.top()<<"\n";
	std::cout<<"top ele node"<<st_node.top()<<"\n";
 

 /**** test on complex data types like set data structure 


  **************/

	std::function< std::set<int> (std::set<int>,std::set<int>)> set_oper =[](std::set<int> a,std::set<int> b) ->std::set<int>{
		std::set<int> s;
	for(auto i:b)
		s.insert(i);
	for(auto i:a)
		s.insert(i);
	return s;
	};
	std::vector< std::set<int> > vec_set = {{1,2,3,4},{4,6},{7,8},{0,789}};
	segtree_recur<std::set<int> > st_recur1(vec_set.begin(),vec_set.end(),set_oper);
	segtree_iter<std::set<int> >  st_iter1(vec_set.begin(),vec_set.end(),set_oper);
	segtree_node<std::set<int> >  st_node1(vec_set.begin(),vec_set.end(),set_oper);
	std::cout<<"time-recursive-- "<<st_recur1.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter1.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node1.time_taken()<<"\n";

	std::function<void(std::set<int>)> print_set_top = [](std::set<int> ret)
	{
		for(auto j: ret)
			std::cout<<j<<"  ";
		std::cout<<"\n";
	};
	print_set_top(st_recur1.top());
	print_set_top(st_iter1.top());
	print_set_top(st_node1.top());
}
