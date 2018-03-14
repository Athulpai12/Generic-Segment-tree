#ifndef SEGTREE_ALL
#define SEGTREE_ALL


#include <vector>
#include <utility>
#include <functional>
#include <math.h>
#include <ctime>
#include <assert.h>
#define SAFE_DELETE(p) if (p) delete p,p = nullptr;


/************************************************
Note - 

Below is implementation of a generic segment tree in three methods

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

Only this things that need to be  passed are the type stored in each node and the function to calculte the inner nodes from the 
leaf nodes

**************************************************/

/****************************************************************

*Below is the Implementation of a Segment tree Data Structure in Iterative  approach

*This is a generic Segment tree 

*A vector Container is used

*This approach takes the least time to create the tree

********************************************************************/


/***** 

EDIT NOTE  - Earlier The user passed data was stored in a separate container but it is now it is removed and changed to manipulating iterators that are passed 
By doing so run time was reduced and memory consumption was reduced.

*****/
template<typename Type , typename Container=std::vector<Type> >
class segtree_iter
{
private:
	Container tree_cont; // Container to store the segment tree by using the container passed by user
	std::function<Type(Type,Type)> segtree_build_function; // The function used to calculate the build function'
	int cont_size; // The size of the container passed by the user
	double build_time; // The time taken to build the tree.
	typedef typename Container::iterator iterate_through; // Iterator to list the element in the tree in top down fashion
	typedef typename Container::reverse_iterator reverse_iterate_through; // reverse iterator to list elements of the tree in bottom  up fashion
public:
	segtree_iter():
	build_time(0.0),
	cont_size(0)
	{

	}
	template<typename InputIterator> // if the user passes the iterator to the constructor 
	// function has a default value which can be overridden by the user
	segtree_iter(const InputIterator start,const InputIterator end,std::function<Type(Type, Type)> build_function = [](Type a,Type b)->Type{return a>b?a:b;} ):
	cont_size(end-start),
	segtree_build_function(build_function)
	{
		build_iter(start,end);
	} // if the user passes a value and size
	// function has a default value which can be overridden by the user
	segtree_iter(int size , Type value,std::function<Type(Type, Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	cont_size(size),
	segtree_build_function(build_function)
	{
		build_iter(value);
	}// if the user passes a container directly
	// function has a default value which can be overridden by the user
	segtree_iter(const Container &build_container,std::function<Type(Type, Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	cont_size((int)build_container.size()),
	segtree_build_function(build_function)
	{
		
		build_iter(build_container);
	}// iterative build method
	template<typename InputIterator> 
	//using the iterator to directly build the tree instead of using a container to store the elements (This helps in saving memory and time)
	void build_iter(const InputIterator start,const InputIterator end)
	{
		clock_t begin_time = clock();
		int tree_size = (cont_size)<<1;
		tree_cont.resize(tree_size);
		// the algorithm to build the function 
		for(int i=2*cont_size -1,j=-1;i>=cont_size;i--,j--)
			tree_cont[i] = *(end+j);
		for (int i = cont_size-1; i > 0; --i) tree_cont[i] = segtree_build_function( tree_cont[i<<1] ,tree_cont[i<<1|1] );
		clock_t end_time = clock();
		// here the time is calculated for building the tree
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	} // iterative query method
	void build_iter(Type value)
	{
		clock_t begin_time = clock();
		int tree_size = (cont_size)<<1;
		tree_cont.resize(tree_size);
		// the algorithm to build the function 
		for(int i=2*cont_size -1;i>=cont_size;i--)
			tree_cont[i] = value;
		for (int i = cont_size-1; i > 0; --i) tree_cont[i] = segtree_build_function( tree_cont[i<<1] ,tree_cont[i<<1|1] );
		clock_t end_time = clock();
		// here the time is calculated for building the tree
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	}
	// build for container
	void build_iter(const Container &build_container)
	{
		clock_t begin_time = clock();
		int tree_size = (cont_size)<<1;
		tree_cont.resize(tree_size);
		// the algorithm to build the function 
		for(int i=2*cont_size -1;i>=cont_size;i--)
			tree_cont[i] = build_container[i-cont_size];
		for (int i = cont_size-1; i > 0; --i) tree_cont[i] = segtree_build_function( tree_cont[i<<1] ,tree_cont[i<<1|1] );
		clock_t end_time = clock();
		// here the time is calculated for building the tree
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	}
	Type query_iter(int l, int r)
	{
		// making sure the tree is not empty 
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		r+=1;
		// A pointer because c++ does not have a default keyword for generic type like C#
		Type *obj = NULL;
		// The algorithm to build the tree iteratively
		for (l += cont_size, r += cont_size; l < r; l >>= 1, r >>= 1) {
    		if (l&1) {
    			if(obj==NULL)
    			{
    				obj=new Type;
    				*obj= tree_cont[l++];
    			}
    			else
    				*obj = segtree_build_function(*obj,tree_cont[l++]);
    		}
   		 	if (r&1) {
   		 		if(obj==NULL)
    			{
    				obj=new Type;
    				*obj= tree_cont[--r];
    			}
    			else
    				*obj = segtree_build_function(*obj,tree_cont[--r]);

   		 	}
  		}
  		Type ret = *obj;
  		// Delete the object and set it to null 
  		SAFE_DELETE(obj);
  		return ret;

	}// iterative update method
	void update_iter(int l,int r, Type value)
	 { 
	 // asserting the tree is not empty 
	 assert(("Cannot query on object whose size is zero", cont_size> 0));
	 // The algorithm to update the nodes
	 for(int i=l;i<=r;i++)
	 	{
	 		int j=i;
     		for (tree_cont[j+= cont_size] = value; j > 1; j >>= 1) tree_cont[j>>1] = segtree_build_function(tree_cont[j],tree_cont[j^1]);
 	 	}
	 }// print the elements on the terminal in top down or bottom up fashion based on the option. 0 is default for option and diplays elements in top down fashion 
	 void log_terminal(int option = 0, std::function<void(Type)> print_function = [](Type element){ std::cout<<element;} ) 
	{
		std::cout<<"Segment Tree - iterative Log"<<"\n";
		std::cout<<"Time to build "<< build_time<<"\n";
		std::cout<<"Contents of tree "<<"\n";
		if(!option)
		{
			// top down display of elements
			std::cout<<"Top down format display\n";
			iterate_through st_begin = tree_cont.begin()+1,st_end = tree_cont.end();
			for(int i=1;st_begin!=st_end;i++,st_begin++)
				std::cout<<"element "<<i<<") ",
				print_function(*st_begin),
				std::cout<<"\n";

		}
		else
		{
			// bottom down display of elements
			std::cout<<"bottom up format display\n";
			reverse_iterate_through st_rbegin =  tree_cont.rbegin(),st_rend=tree_cont.rend();
			for(int i=1;st_rbegin!=st_rend;i++,st_rbegin++)
				std::cout<<"element "<<i<<") ",
				print_function(*st_rbegin),
				std::cout<<"\n";

		}
		
	}// the total time taken const keyword is used to prevent modification in this function
	double time_taken() const
	{
		return build_time;
	}
	//returns the element at the top const keyword is used to prevent modification in this function
	Type top() const
	{
		return tree_cont[1];
	}

};

/****************************************************************

*Below is the Implementation of a Segment tree Data Structure in "Recurrsive"  approach

*This is a generic Segment tree 

*A vector Container is used

*the approach takes more time than iterative approach

********************************************************************/



template<typename Type , typename Container=std::vector<Type> >
class segtree_recur
{
private:
	Container tree_cont; // Container to store the segment tree by using the container passed by user
	std::function<Type(Type,Type)> segtree_build_function; // The function used to calculate the build function
	int cont_size; // The size of the container passed by the user
	double build_time; // The time taken to build the tree.
	typedef typename Container::iterator iterate_through; // Iterator to list the element in the tree in top down fashion
	typedef typename Container::reverse_iterator reverse_iterate_through; // reverse Iterator to list the element in the tree in top down fashion
public:
	segtree_recur():
	build_time(0.0),
	cont_size(0)
	{

	}
	template<typename InputIterator> // if the user passes the iterator to the constructor
	segtree_recur(const InputIterator start,const InputIterator end,std::function<Type(Type, Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	cont_size((int)(end-start)),
	segtree_build_function(build_function)
	{
		build_recur(start,end);
	} // if the user passes size and type
	segtree_recur(int size , Type value,std::function<Type(Type, Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	cont_size(size),
	segtree_build_function(build_function)
	{
		build_recur(value);
	}// if the user passes a container directly
	segtree_recur(const Container &build_container,std::function<Type(Type, Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	cont_size((int)build_container.size()),
	segtree_build_function(build_function)
	{
		build_recur(build_container);
	}
	// this build function recursively builds the tree
	template<typename InputIterator>
	void build_recur(const InputIterator start,const InputIterator end)
	{
		clock_t begin_time = clock();
		//Size of the segment tree is always not greater than 4 times the size of the container in recursive mode of approach
		int tree_size = (int)(log((double)cont_size)/log(2));
		tree_size = 1<<(2+tree_size);
		tree_cont.resize(tree_size);
		// below is the implementation of a lambda function for recursively build the tree. The lambda function captures elements outside by reference
		std::function<void(int,int, int)> recur_build = [&](int st,int en, int node)
		{
			if(st==en)
				tree_cont[node] = *(start+st);
			else
			{
				int m = (st+en)/2;
				recur_build(st,m,2*node);
				recur_build(m+1,en,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		recur_build(0,cont_size-1,1);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
		
	}
	void build_recur(Type value)
	{
		clock_t begin_time = clock();
		//Size of the segment tree is always not greater than 4 times the size of the container in recursive mode of approach
		int tree_size = (int)(log((double)cont_size)/log(2));
		tree_size = 1<<(2+tree_size);
		tree_cont.resize(tree_size);
		// below is the implementation of a lambda function for recursively build the tree. The lambda function captures elements outside by reference
		std::function<void(int,int, int)> recur_build = [&](int st,int en, int node)
		{
			if(st==en)
				tree_cont[node] = value;
			else
			{
				int m = (st+en)/2;
				recur_build(st,m,2*node);
				recur_build(m+1,en,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		recur_build(0,cont_size-1,1);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
		
	}
	void build_recur(const Container &build_container)
	{
		clock_t begin_time = clock();
		//Size of the segment tree is always not greater than 4 times the size of the container in recursive mode of approach
		int tree_size = (int)(log((double)cont_size)/log(2));
		tree_size = 1<<(2+tree_size);
		tree_cont.resize(tree_size);
		// below is the implementation of a lambda function for recursively build the tree. The lambda function captures elements outside by reference
		std::function<void(int,int, int)> recur_build = [&](int st,int en, int node)
		{
			if(st==en)
				tree_cont[node] = build_container[st];
			else
			{
				int m = (st+en)/2;
				recur_build(st,m,2*node);
				recur_build(m+1,en,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		recur_build(0,cont_size-1,1);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
		
	}
	// this build function recursively updates the tree for a range
	void  update_recur(int left, int right,Type value)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		int node =1,start=0,end=cont_size-1;
		// recursive lambda function to update the nodes for a range of values
		std::function<void(int , int , int)> recur_build= [&](int start, int end, int node)
		{
			if(start>right)
				return;
			if(end<left)
				return;
			if(start==end)
				tree_cont[node] = value;
			else
			{
				int mid = (start+end)/2;
				recur_build(start,mid,2*node);
				recur_build(mid+1,end,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		recur_build(start,end,node);
	}
	//recursively updates the tree for a index
	void update_recur(int index, int value)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		int node =1,start=0,end=cont_size-1;
		// recursive lambda function to update the nodes for a given index
		std::function<void(int , int , int)> functor= [&](int start, int end, int node)
		{
			if(start>index)
				return;
			if(end<index)
				return;
			if(start==end)
				tree_cont = value;
			else
			{
				int mid = (start+end)/2;
				functor(start,mid,2*node);
				functor(mid+1,end,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		functor(start,end,node);
	}
	// gives the query in a range 
	Type query_recur(int l ,int r)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		Type *obj = NULL;
		std::function<void(int ,int ,int)> function_query= [&](int st, int en, int node)
		{
			if(r<st)
				return;
			if(en<l)
				return;
			if(l<=st&&r>=en)
			{
				if(obj==NULL)
				obj = new Type,*obj = tree_cont[node];
				return ;
			}
			
			int mid  = (st+en)/2;
			function_query(st,mid,2*node);
			function_query(mid+1,en,2*node+1);
		};
		function_query(0,cont_size-1,1);
		Type ret = *obj;
		SAFE_DELETE(obj);
		return ret;
	}
	// print the elements on the terminal in top down or bottom up fashion based on the option. 0 is default and diplays elements in top down fashion 
	void log_terminal( int option = 0, std::function<void(Type)> print_function = [](Type element){ std::cout<<element;} ) 
	{
		std::cout<<"Segment Tree - Recurrsive Log"<<"\n";
		std::cout<<"Time to build "<< build_time<<"\n";
		std::cout<<"Contents of tree "<<"\n";
		if(!option)
		{
			// top down display of elements
			std::cout<<"Top down format display\n";
			iterate_through st_begin = tree_cont.begin()+1,st_end = tree_cont.end();
			for(int i=1;st_begin!=st_end;i++,st_begin++)
				std::cout<<"element "<<i<<") ",
				print_function(*st_begin),
				std::cout<<"\n";

		}
		else
		{
			// bottom up display of elements
			std::cout<<"bottom up format display\n";
			reverse_iterate_through st_rbegin =  tree_cont.rbegin(),st_rend=tree_cont.rend();
			for(int i=1;st_rbegin!=st_rend;i++,st_rbegin++)
				std::cout<<"element "<<i<<") ",
				print_function(*st_rbegin),
				std::cout<<"\n";

		}
		
	}
	//return the time taken const keyword is used to prevent modification in this function
	double time_taken() const
	{
		return build_time;
	}
	//returns the element at the top const keyword is used to prevent modification in this function
	Type top() const
	{
		return tree_cont[1];
	}
};


/****************************************************************

*Below is the Implementation of a Generic Segment tree Data Structure in Recurrsive node approach

*Here the Segment tree is stored in the heap structure 

*The Segment uses a node Structure to store each element 

*This function is best to be used when memory is to stored in the heap

********************************************************************/


// Container of vector type if a container is passed to the constructor by the user
template<typename Type,typename Container=std::vector<Type> >
class segtree_node // this the encapsulating class for the node class
{
	// node class to store the elements
	class node
{
public:
	node *left; // the left child 
	node *right; // the right child
	Type ele; // The element in the node 
public:
	node(){
		left=NULL;
		right=NULL;
	}
	~node() // destructor
	{
		SAFE_DELETE(left);
		SAFE_DELETE(right);
	}
};
private:
	node *head; // Pointer pointing to the top most element
	int cont_size; // size of the number of elements passed
	std::function<Type(Type,Type)> segment_build_function;
	double build_time;
public:
	segtree_node():
	build_time(0.0),
	cont_size(0),
	head(NULL)
	{
	}
	template<typename InputIterator>
	// Constructor which takes iterators as parameters and a function that has a default value which can be overidden by the user
	segtree_node(const InputIterator start,const InputIterator end,std::function<Type(Type,Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	segment_build_function(build_function),
	cont_size(end-start)
	{
		build_node(start,end);
	}
	// Constructor which takes size and value as parameters and a function that has a default value which can be overidden by the user
	segtree_node(int size,Type val,std::function<Type(Type,Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	segment_build_function(build_function),
	cont_size(size)
	{
		build_node(val);
	}
	// Constructor which takes a Container as parameters and a function that has a default value which can be overidden by the user
	segtree_node(const Container &build_container,std::function<Type(Type,Type)> build_function=[](Type a,Type b)->Type{return a>b?a:b;}):
	segment_build_function(build_function),
	cont_size(build_container.size())
	{
		build_node(build_container);
	}
	template<typename InputIterator>
	void build_node(const InputIterator start,const InputIterator end)
	{
		// measure  time at the beginning of  build 
		clock_t begin_time = clock();
		int st=0,en=cont_size-1;
		// The recursive algorithm implemented below using lambda functions
		std::function< node *(int, int)> node_build = [&](int st, int en)
		{
			if(st==en)
				{
					node *child = new node;
					child->ele = *(start+st);
					return child;
				}
			else
			{
				node *child = new node;
				int mid= (st+en)/2;
				child->right = node_build(mid+1,en);
				child->left = node_build(st,mid);
				child->ele = segment_build_function(child->left->ele,child->right->ele);
				return child;
			}
		};
		this->head = node_build(st,en);
		//measure time at the end of build function
		clock_t end_time = clock();
		build_time =(double) (end_time-begin_time)/CLOCKS_PER_SEC;

	}
	void build_node( Type value)
	{
		clock_t begin_time = clock();
		int st=0,en=cont_size-1;
		std::function< node *(int, int)> node_build = [&](int st, int en)
		{
			if(st==en)
				{
					node *child = new node;
					child->ele = value;
					return child;
				}
			else
			{
				node *child = new node;
				int mid= (st+en)/2;
				child->right = node_build(mid+1,en);
				child->left = node_build(st,mid);
				child->ele = segment_build_function(child->left->ele ,child->right->ele);
				return child;
			}
		};
		this->head = node_build(st,en);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	}
	void build_node(const Container &build_container)
	{
		clock_t begin_time = clock();
		int st=0,en=cont_size-1;
		std::function< node *(int, int)> node_build = [&](int st, int en)
		{
			if(st==en)
				{
					node *child = new node;
					child->ele = build_container[st];
					return child;
				}
			else
			{
				node *child = new node;
				int mid= (st+en)/2;
				child->right = node_build(mid+1,en);
				child->left = node_build(st,mid);
				child->ele = segment_build_function(child->left->ele,child->right->ele);
				return child;
			}
		};
		this->head = node_build(st,en);
		clock_t end_time = clock();
		build_time =(double) (end_time-begin_time)/CLOCKS_PER_SEC;
	}
	void update_node(int l,int r,Type value)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		node *tree_temp = this->head;
		std::function<void(int, int,node *) > node_update  = [&](int st,int en,node *tree_node)
		{
			if(r<st)
				return;
			if(en<l)
				return;
			if(st==en)
				tree_node->ele = value;
			else
			{
				int mid = (st+en)/2;
				node_update(st,mid,tree_node->left);
				node_update(mid+1,en,tree_node->right);
				tree_node->ele = segment_build_function(tree_node->left->ele,tree_node->right->ele);
			}
			return ;

		};
		int st=0,en=cont_size-1;
		node_update(st,en,tree_temp);
	}
	void update_node(int l,Type val)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		node *tree_temp = this->head;
		std::function<void(int, int,node *) > node_update  = [&](int st,int en,node *tree_node)
		{
			if(l<st)
				return;
			if(en<l)
				return;
			if(st==en)
				tree_node->ele = val;
			else
			{
				int mid = (st+en)/2;
				node_update(st,mid,tree_node->left);
				node_update(mid+1,en,tree_node->right);
				tree_node->ele =segment_build_function(tree_node->left->ele, tree_node->right->ele);
			}
			return ;

		};
		int st=0,en=cont_size-1;
		node_update(st,en,tree_temp);
		
	}
	
	Type query_node(int l,int r)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		node *tree_temp = this->head;
		//Pointer to the value to be returned
		node *capture = NULL;
		//Algorithm to query in the range
		std::function<void(int, int,node *) > node_query  = [&](int st,int en,node *tree_node)
		{
			
			if(r<st)
				return;
			if(en<l)
				return;
			if(l<=st&&r>=en)
				{
					if(capture==NULL)
						capture = new node,capture->ele = tree_node->ele;
					else
						capture->ele = segment_build_function(capture->ele,tree_node->ele);
				}
			else
			{
				int mid = (st+en)/2;
				node_query(st,mid,tree_node->left);
				node_query(mid+1,en,tree_node->right);
			}
			return;

		};
		int st=0,en=cont_size-1;
		node_query(st,en,tree_temp);
		Type ret = capture->ele;
		SAFE_DELETE(capture);
		return ret;
	}
	// returns the time taken const to prevent modification in the function
	double time_taken() const
	{
		return build_time;
	}
	// return the element at the top const to prevent modification in the function
	Type top() const
	{
		return this->head->ele;
	}
	// print the elements preorder format or postorder format based on the option . By default it prints in preorder format
	void log_terminal(int option = 0, std::function<void(Type)> print_function=[](Type element){std::cout<<element;})
	{
		node *ret_1 = this->head;
		std::cout<<"Segment Tree - Node Log"<<"\n";
		std::cout<<"Time to build "<< build_time<<"\n";
		std::cout<<"Contents of tree "<<"\n";
		int count=0;
		if(!option)
		{
			std::cout<<"preorder format display\n";
			std::function<void(node *)> print_node = [&print_node,&print_function,&count](node *ret)
			{
				
				if(ret!=NULL)
					{
						count++;
						std::cout<<"\nelement "<<count<<") ";
						print_function(ret->ele);
						print_node(ret->left);
						print_node(ret->right);
					}
			};
		print_node(ret_1);
		}
		else
		{
			std::cout<<"postorder format display\n";
			std::function<void(node *)> print_node_r = [&print_node_r,&print_function,&count](node *ret)
			{
				
				if(ret!=NULL)
					{
						
						print_node_r(ret->right);
						print_node_r(ret->left);
						count++;
						std::cout<<"\nelement "<<count<<") ";
						print_function(ret->ele);
					}
			};
		print_node_r(ret_1);
		}
	}
	~segtree_node()
	{
		SAFE_DELETE(head);
	}
};

#endif
