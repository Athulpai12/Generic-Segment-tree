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
	return 	a-b;
	};
	std::function<double(double,double)> multiplier = [](double a, double b)->double
	{
	return 	a*b;
	};
  /***** test for primitive type 
         like int 

         ****/

	/**********
	double type and multiplier function 
	*********/

	segtree_recur<double> st_recur(1000000,1.000002,multiplier); // passing size ,value and function to constructor
	segtree_iter<double>  st_iter(1000000,1.000002,multiplier);
	segtree_node<double>  st_node(1000000,1.000002,multiplier);
	std::cout<<"time-recursive-- "<<st_recur.time_taken()<<"\n";  // prints the time taken to build the tree
	std::cout<<"time-iterative-- "<<st_iter.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node.time_taken()<<"\n";

	std::cout<<"\n";

	st_iter.update_iter(2,3,2); // updating the values in a range
	st_recur.update_recur(2,3,2);
	st_node.update_node(2,3,2);
	std::cout<<"top ele recur"<<st_recur.top()<<"\n"; // gets the top node
	std::cout<<"top ele iter"<<st_iter.top()<<"\n";
	std::cout<<"top ele node"<<st_node.top()<<"\n";

 	std::cout<<"\n\n";
	//st_iter.log_terminal();
	//st_recur.log_terminal();
	//st_node.log_terminal();


 	/**********
	int type and
	adder function 
	********/

	segtree_recur<int> st_recur_1(1000000,1,adder);
	segtree_iter<int>  st_iter_1(1000000,1,adder);
	segtree_node<int>  st_node_1(1000000,1,adder);
	std::cout<<"time-recursive-- "<<st_recur_1.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter_1.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node_1.time_taken()<<"\n";

	std::cout<<"\n";

	st_iter_1.update_iter(2,3,2);
	st_recur_1.update_recur(2,3,2);
	st_node_1.update_node(2,3,2);
	std::cout<<"top ele recur"<<st_recur_1.top()<<"\n";
	std::cout<<"top ele iter"<<st_iter_1.top()<<"\n";
	std::cout<<"top ele node"<<st_node_1.top()<<"\n";

	std::cout<<"\n\n";
     
     // A container being passed

	std::vector<int> v={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

	segtree_recur<int> st_recur_2(v.begin(),v.end(),adder); // passing iterator and function to constructor
	segtree_iter<int>  st_iter_2(v.begin(),v.end(),adder);
	segtree_node<int>  st_node_2(v.begin(),v.end(),adder);
	std::cout<<"time-recursive-- "<<st_recur_2.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter_2.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node_2.time_taken()<<"\n";

	std::cout<<"\n";
	//st_iter_2.update_iter(2,3,2);
	//st_recur_2.update_recur(2,3,2);
	//st_node_2.update_node(2,3,2);
	std::cout<<"top ele recur"<<st_recur_2.top()<<"\n";
	std::cout<<"top ele iter"<<st_iter_2.top()<<"\n";
	std::cout<<"top ele node"<<st_node_2.top()<<"\n";
 	
	std::cout<<"\n\n";

	segtree_recur<int> st_recur_3(v.begin(),v.end()); // just passing the iterator to constructor the default function values will be used in this case
	segtree_iter<int>  st_iter_3(v.begin(),v.end());
	segtree_node<int>  st_node_3(v.begin(),v.end());
	std::cout<<"time-recursive-- "<<st_recur_3.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter_3.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node_3.time_taken()<<"\n";

	std::cout<<"\n";
	//st_iter_2.update_iter(2,3,2);
	//st_recur_2.update_recur(2,3,2);
	//st_node_2.update_node(2,3,2);
	std::cout<<"top ele recur"<<st_recur_3.top()<<"\n";
	std::cout<<"top ele iter"<<st_iter_3.top()<<"\n";
	std::cout<<"top ele node"<<st_node_3.top()<<"\n";
 	
	std::cout<<"\n\n";

	st_iter_3.log_terminal(); // a log of the elements in the tree ... here default values for option and functions are used
	st_recur_3.log_terminal(0,[](int a){std::cout<<a;}); // a log of the elements in the tree ...both option and function passed by user
	st_node_3.log_terminal(1); // a log of the elements in the tree ... only option passed by user


	// A string type being passed

	std::vector<std::string> elements = {"a","b","c","d","e","f","g","h","i"};

	// A container is passed to the container
	segtree_recur<std::string> st_recur_4(elements,[](std::string s,std::string s1)->std::string{return s+s1;}); // lambda function being used to calculate the inner node
	segtree_iter<std::string>  st_iter_4(elements,[](std::string s,std::string s1)->std::string{return s+s1;});
	segtree_node<std::string>  st_node_4(elements,[](std::string s,std::string s1)->std::string{return s+s1;});
	std::cout<<"\ntime-recursive-- "<<st_recur_4.time_taken()<<"\n";
	std::cout<<"time-iterative-- "<<st_iter_4.time_taken()<<"\n";
	std::cout<<"time-node -- "<<st_node_4.time_taken()<<"\n";

	std::cout<<"\n";

	// query on the tree being done
	std::cout<<"query - iterative "<<st_iter_4.query_iter(0,2)<<std::endl;
	std::cout<<"query - recursive "<<st_recur_4.query_recur(0,2)<<std::endl;
	std::cout<<"query - node "<<st_node_4.query_node(0,2)<<std::endl;
	
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
