#include <iostream>
#include "BinaryTree.h"

int main()
{
	BinaryTree<int> t;
	t.push(6);
	t.push(4);
	t.push(2);
	t.push(5);
	t.push(7);
	t.push(8);
	t.remove(2);
	
	std::cout<<"Tree of size: "<<t.size()<<"\n";
	
	std::cout<<"Preorder: ";
	for(auto it = t.begin_preord(); it != t.end_preord(); it++)
	{
		std::cout<<*it<<" ";
	}
	
	std::cout<<"\n";
	std::cout<<"Inorder: ";
	for(auto it = t.begin_inord(); it != t.end_inord(); it++)
	{
		std::cout<<*it<<" ";
	}
	
	std::cout<<"\n";
	std::cout<<"Postorder: ";
	for(auto it = t.begin_postord(); it != t.end_postord(); it++)
	{
		std::cout<<*it<<" ";
	}
	
	std::cout<<"\n";
	
	return 0;
}
