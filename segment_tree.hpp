#include <vector>
#include <utility>
#include <functional>
#include <math.h>
#include <ctime>
#include <assert.h>
#define SAFE_DELETE(p) if (p) delete p,p = nullptr;


/************************************************
Note - 

Below is implementation of a generic segment tree in three method

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

**************************************************/

/****************************************************************

*Below is the Implementation of a Segment tree Data Structure in Iterative  approach

*This is a generic Segment tree 

*A vector Container is used

*This approach takes the least time to create the tree

********************************************************************/
template<typename Type , typename Container=std::vector<Type> >
class segtree_iter
{
private:
	Container cont_; // Container to store the elements that are passed by the user
	Container tree_cont; // Container to store the segment tree by using the container passed by user
	std::function<Type(Type,Type)> segtree_build_function; // The function used to calculate the build function
	int cont_size; // The size of the container passed by the user
	double build_time; // The time taken to build the tree.
public:
	segtree_iter():
	build_time(0.0),
	cont_size(0)
	{

	}
	template<typename InputIterator> // if the user passes the iterator to the constructor
	segtree_iter(InputIterator start, InputIterator end,std::function<Type(Type, Type)> build_function):
	cont_(start,end),// iiterator list for storing the container
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		build_iter();
	} // if the user passes a value and size
	segtree_iter(int size , int value,std::function<Type(Type, Type)> build_function):
	cont_(size,value),
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		build_iter();
	}// if the user passes a container directly
	segtree_iter(Container new_container,std::function<Type(Type, Type)> build_function):
	cont_(new_container),
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		
		build_iter();
	}// iterative build method
	void build_iter()
	{
		clock_t begin_time = clock();
		int tree_size = (cont_size)<<1;
		tree_cont.resize(tree_size);
		// the algorithm to build the function 
		for(int i=2*cont_size -1;i>=cont_size;i--)
			tree_cont[i] = cont_[i - cont_size];
		for (int i = cont_size-1; i > 0; --i) tree_cont[i] = segtree_build_function( tree_cont[i<<1] ,tree_cont[i<<1|1] );
		clock_t end_time = clock();
		// here the time is calculated for building the tree
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	} // iterative query method
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
	 }// output the tree on to the terminal
	 void log_terminal(std::function<void(Type)> print_function)
	{
		for(auto i:tree_cont)
			print_function(i);
		
	}// the total time taken
	double time_taken()
	{
		return build_time;
	}
	//returns the element at the top
	Type top()
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
	Container cont_; // Container to store the elements that are passed by the user
	Container tree_cont; // Container to store the segment tree by using the container passed by user
	std::function<Type(Type,Type)> segtree_build_function; // The function used to calculate the build function
	int cont_size; // The size of the container passed by the user
	double build_time; // The time taken to build the tree.
public:
	segtree_recur():
	build_time(0.0),
	cont_size(0)
	{

	}
	template<typename InputIterator> // if the user passes the iterator to the constructor
	segtree_recur(InputIterator start, InputIterator end,std::function<Type(Type, Type)> build_function):
	cont_(start,end),
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		build_recur();
	} // if the user passes size and type
	segtree_recur(int size , int value,std::function<Type(Type, Type)> build_function):
	cont_(size,value),
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		build_recur();
	}// if the user passes a container directly
	segtree_recur(Container new_container,std::function<Type(Type, Type)> build_function):
	cont_(new_container),
	cont_size((int)cont_.size()),
	segtree_build_function(build_function)
	{
		build_recur();
	}
	// this build function recursively builds the tree
	void build_recur()
	{
		clock_t begin_time = clock();
		//Size of the segment tree is always not greater than 4 times the size of the container in recursive mode of approach
		int tree_size = (int)(log((double)cont_.size())/log(2));
		tree_size = 1<<(2+tree_size);
		tree_cont.resize(tree_size);
		// below is the implementation of a lambda function for recursively build the tree. The lambda function captures elements outside by reference
		std::function<void(int,int, int)> recur_build = [&](int start,int end, int node)
		{
			if(start==end)
				tree_cont[node] = cont_[start];
			else
			{
				int m = (start+end)/2;
				recur_build(start,m,2*node);
				recur_build(m+1,end,2*node+1);
				tree_cont[node] = segtree_build_function(tree_cont[2*node],tree_cont[2*node+1]);
			}
		};
		recur_build(0,cont_.size()-1,1);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
		
	}
	// this build function recursively updates the tree for a range
	void  update_recur(int left, int right,Type value)
	{
		assert(("Cannot query on object whose size is zero", cont_size> 0));
		int node =1,start=0,end=cont_.size()-1;
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
		int node =1,start=0,end=cont_.size()-1;
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
	// print the elements on the terminal
	void log_terminal(std::function<void(Type)> print_function)
	{
		for(auto i:tree_cont)
			print_function(i);
		
	}
	//return the time taken
	double time_taken()
	{
		return build_time;
	}
	//returns the element at the top
	Type top()
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



template<typename Type>
class segtree_node
{
	// node class to store the elements
	class node
{
public:
	node *left; // the left child 
	node *right; // the right child
	Type ele;
public:
	node(){
		left=NULL;
		right=NULL;
	}
	~node()
	{
		SAFE_DELETE(left);
		SAFE_DELETE(right);
	}
};
private:
	node *head;
	int size;
	std::function<Type(Type,Type)> segment_build_function;
	double build_time;
public:
	segtree_node():
	build_time(0.0),
	size(0),
	head(NULL)
	{
	}
	template<typename iter>
	segtree_node(iter start,iter end,std::function<Type(Type,Type)> build_function):
	segment_build_function(build_function)
	{
		build_node(start,end);
	}
	segtree_node(int n,Type val,std::function<Type(Type,Type)> build_function):
	segment_build_function(build_function)
	{
		build_node(n,val);
	}
	template<typename iter>
	void build_node(iter start,iter end)
	{
		clock_t begin_time = clock();
		std::vector<Type> cont(start,end);
		this->size = cont.size()-1;
		int st=0,en=size;
		std::function< node *(int, int)> node_build = [&](int st, int en)
		{
			if(st==en)
				{
					node *val = new node;
					val->ele = cont[st];
					return val;
				}
			else
			{
				node *val = new node;
				int m= (st+en)/2;
				val->right = node_build(m+1,en);
				val->left = node_build(st,m);
				val->ele = segment_build_function(val->right->ele,val->left->ele);
				return val;
			}
		};
		this->head = node_build(st,en);
		clock_t end_time = clock();
		build_time = (end_time-begin_time)/CLOCKS_PER_SEC;

	}
	void build_node(int n, Type val)
	{
		clock_t begin_time = clock();
		std::vector<Type> cont(n,val);
		this->size = cont.size()-1;
		int st=0,en=size;
		std::function< node *(int, int)> node_build = [&](int st, int en)
		{
			if(st==en)
				{
					node *val = new node;
					val->ele = cont[st];
					return val;
				}
			else
			{
				node *val = new node;
				int m= (st+en)/2;
				val->right = node_build(m+1,en);
				val->left = node_build(st,m);
				val->ele = segment_build_function(val->right->ele ,val->left->ele);
				return val;
			}
		};
		this->head = node_build(st,en);
		clock_t end_time = clock();
		build_time = (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	}
	void update_node(int l,int r,Type val)
	{
		assert(("Cannot query on object whose size is zero", size> 0));
		node *tree_temp = this->head;
		std::function<void(int, int,node *) > node_update  = [&](int st,int en,node *tree_node)
		{
			if(r<st)
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
				tree_node->ele = segment_build_function(tree_node->left->ele,tree_node->right->ele);
			}
			return ;

		};
		int st=0,en=size;
		node_update(st,en,tree_temp);
	}
	void update_node(int l,Type val)
	{
		assert(("Cannot query on object whose size is zero", size> 0));
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
		int st=0,en=size;
		node_update(st,en,tree_temp);
		
	}
	
	Type query_node(int l,int r)
	{
		assert(("Cannot query on object whose size is zero", size> 0));
		node *tree_temp = this->head;
		node *capture = NULL;
		std::function<void(int, int,node *,node **) > node_query  = [&](int st,int en,node *tree_node,node **cap)
		{
			
			if(r<st)
				return;
			if(en<l)
				return;
			if(l<=st&&r>=en)
				{
					if(*cap==NULL)
						*cap = new node,(*cap)->ele = tree_node->ele;
					else
						(*cap)->ele = segment_build_function((*cap)->ele,tree_node->ele);
				}
			else
			{
				int mid = (st+en)/2;
				node_query(st,mid,tree_node->left,cap);
				node_query(mid+1,en,tree_node->right,cap);
			}
			return;

		};
		int st=0,en=size;
		node_query(st,en,tree_temp,&capture);
		Type ret = capture->ele;
		SAFE_DELETE(capture);
		return ret;
	}
	// returns the time taken
	double time_taken()
	{
		return build_time;
	}
	// return the element at the top
	Type top()
	{
		return this->head->ele;
	}
	// print the elements
	void log_terminal(std::function<void(Type)> print_function)
	{
		node *ret_1 = this->head;
		std::function<void(node *)> print_node = [&print_node,&print_function](node *ret)
		{
			if(ret!=NULL)
			{
				print_node(ret->left);
				print_function(ret->ele);
				print_node(ret->right);
			}
		};
		print_node(ret_1);
	}
	~segtree_node()
	{
		SAFE_DELETE(head);
	}
};
