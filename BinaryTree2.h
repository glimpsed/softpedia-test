#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include <deque>
#include <iostream>

//Traversal method

enum Traversal
{
	Preorder, Postorder, Inorder
};

template <class T>
class Node
{
	public:
	T info;
	Node* left;
	Node* right;
	Node* parent;

	Node();
	Node(T& val);
	~Node();
};

template <class T>
Node<T>::Node()
{
	left = right = parent = 0;
}

template <class T>
Node<T>::Node(T& val)
{
	info = val;
}

template <class T>
Node<T>::~Node()
{
}

template <class T>
class BinaryTree
{
	public:
	Node<T>* root;
	int dim;
	
	class Iterator
	{
		public:
		Node<T>* crt;
		Node<T>* stacknode;
		std::deque<Node<T>*> stack;
		std::deque<Node<T>*> stack2;
		
		Iterator()
		{
			crt = 0;
		}
	
		Iterator& operator=(const Iterator& it)
		{
			crt = it.crt;
			stack = it.stack;
			stacknode = it.stacknode;
		}
	

		~Iterator()
		{
		}
	

		bool operator==(const Iterator& it)
		{
			return (crt == it.crt);
		}
	

		bool operator!=(const Iterator& it)
		{
			return (crt != it.crt);
		}
	

		T& operator*()
		{
			return crt -> info;
		}
	
		/*virtual Iterator operator++()
		{
			std::cout<<"NOT OVERRIDEN\n";
			return (*this);
		}*/
		
		virtual Iterator operator++() = 0;

		Iterator operator++(int)
		{
			Iterator aux(*this);
			++(*this);
			return aux;
		}
	};
	
	class IteratorPostOrd : public Iterator
	{
		public:
		IteratorPostOrd(Node<T>* node)
		{
			Iterator::crt = node;
			Iterator::stack.push_front(Iterator::crt);
			while(Iterator::stack.empty() == false)
			{
				Iterator::crt = Iterator::stack.front();
				Iterator::stack.pop_front();
				Iterator::stack2.push_front(Iterator::crt);
				
				if(Iterator::crt != 0)
				{
					if(Iterator::crt -> left != 0)
						Iterator::stack.push_front(Iterator::crt -> left);
					if(Iterator::crt -> right != 0)
						Iterator::stack.push_front(Iterator::crt -> right);
				}
			}
			
			if(Iterator::stack2.empty() == false)
			{
				Iterator::crt = Iterator::stack2.front();
				Iterator::stack2.pop_front();
			}
			
			else
			{
				Iterator::crt = 0;
			}
		}
		
		Iterator operator++()
		{
			if(Iterator::stack2.empty() == false)
			{
				Iterator::crt = Iterator::stack2.front();
				Iterator::stack2.pop_front();
			}
			
			else
			{
				Iterator::crt = 0;
			}
			
			return (*this);
			
		}				
	};
	
	class IteratorPreOrd : public Iterator
	{
		public:
		
		IteratorPreOrd()
		{
			Iterator::crt = 0;
		}
		
		IteratorPreOrd(Node<T>* node)
		{
			Iterator::crt = node;
			if(node != 0)
			{
				if(node -> right != 0)
					Iterator::stack.push_front(node -> right);
				if(node -> left != 0)
					Iterator::stack.push_front(node -> left);
			}
		}
		
		Iterator operator++()
		{
			if(Iterator::stack.empty() == true)
			{
				Iterator::crt = 0;
				return (*this);
			}
		
			else
			{
				Iterator::crt = Iterator::stack.front();
				Iterator::stack.pop_front();
				if(Iterator::crt -> right != 0)
					Iterator::stack.push_front(Iterator::crt -> right);
				if(Iterator::crt->left != 0)
					Iterator::stack.push_front(Iterator::crt -> left);
				if(Iterator::stack.empty() == true)
				{
					Iterator::crt = 0;
					return (*this);
				}
				else
					return (*this);
			}
		}	
	};
	
	class IteratorInOrd : public Iterator
	{
		public:
		IteratorInOrd(Node<T>* node)
		{
			Iterator::crt = node;
			Iterator::stacknode = node;
			
			while(Iterator::stacknode != 0)
			{
				Iterator::stack.push_front(Iterator::stacknode);
				Iterator::stacknode = Iterator::stacknode -> left;
			}
			
			if(Iterator::stack.empty() == false)
			{
				Iterator::crt = Iterator::stack.front();
				Iterator::stacknode = Iterator::stack.front();
				Iterator::stack.pop_front();
				Iterator::stacknode = Iterator::stacknode -> right;
			}
			
			else
			{
				Iterator::crt = 0;
			}
		}
		
		Iterator operator++()
		{
			while(Iterator::stacknode != 0)
			{
				Iterator::stack.push_front(Iterator::stacknode);
				Iterator::stacknode = Iterator::stacknode -> left;
			}
			
			if(Iterator::stack.empty() == false)
			{
				Iterator::crt = Iterator::stack.front();
				Iterator::stacknode = Iterator::stack.front();
				Iterator::stack.pop_front();
				Iterator::stacknode = Iterator::stacknode -> right;
			}
			
			else
			{
				Iterator::crt = 0;
			}

			return (*this);
		}		
	};

	BinaryTree();
	~BinaryTree();
	void push(T val);
	void remove(T val);
	int size();
	
	Iterator begin(int x) // factory
	{
		switch(x)
		{
			case 0:
				return IteratorPreOrd(root);
			case 1:
				return IteratorPostOrd(root);
			case 2:
				return IteratorInOrd(root);
			default:
				return IteratorPreOrd(root);
		}
	}
	
	Iterator begin()
	{
		IteratorPreOrd it(root);
		return it;
	}

	Iterator end()
	{
		return IteratorPreOrd();
	}
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = 0;
	dim = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
}

template <class T>
void BinaryTree<T>::push(T val)
{
	if(root == 0) // arbore vid
	{
		root = new Node<T>(val);
		dim++;
	}

	else // parcurgere in latime
	{
		std::deque<Node<T>* > queue;
		queue.push_back(root);
		bool inserted = false;
		while(inserted == false)
		{
			Node<T>* crt = queue.front();
			queue.pop_front();
			if(crt -> left == 0)
			{
				Node<T>* aux = new Node<T>(val);
				crt -> left = aux;
				aux -> parent = crt;
				dim++;
				inserted = true;
			}

			else
			if(crt -> right == 0)
			{
				Node<T>* aux = new Node<T>(val);
				crt -> right = aux;
				aux -> parent = crt;
				dim++;
				inserted = true;
			}

			else
			{
				if(crt -> left != 0)
					queue.push_back(crt -> left);
				if(crt -> right != 0)
					queue.push_back(crt -> right);
			}
		}
	}
}

template <class T>
int BinaryTree<T>::size()
{
	return dim;
}

//stack traversal

template <class T>
void BinaryTree<T>::remove(T val)
{
	std::deque<Node<T>* > stack;
	stack.push_front(root);
	Node<T>* found = 0;
	while(found == 0 && !stack.empty()) // parcurgere in adancime
	{
		Node<T>* crt = stack.front();
		stack.pop_front();
		if(crt -> info == val)
		{
			found = crt;
		}

		else
		{
			if(crt -> right != 0)
				stack.push_front(crt -> right);
			if(crt -> left != 0)
				stack.push_front(crt -> left);
		}
	}

	if(found == 0)
	{
		return;
	}

	else
	{
		if(root == found) // daca valoarea e in radacina
		{
			if(root -> left == 0 && root -> right == 0)
			{
				delete root;
				root = 0;
				dim = 0;
			}

			else
			if(root -> left != 0 && root -> right != 0)
			{
				return;
			}

			else
			{
				if(root -> left != 0)
				{
					Node<T>* aux = root -> left;
					delete root;
					root = aux;
					dim--;
				}

				else
				{
					Node<T>* aux = root -> right;
					delete root;
					root = aux;
					dim--;					
				}
			}
		}

		else
		{
			if(found -> right == 0 && found -> left == 0) // daca e frunza
			{
				delete found;
				found = 0;
				dim--;
			}

			else
			if(found -> right != 0 && found -> left != 0) // daca are 2 copii
				return;

			else // daca are un singur copil
			{
				if(found -> right != 0)
				{
					Node<T>* aux = found -> parent;
					if(found == aux -> right)
					{
						aux -> right = found -> right;
					}

					else
					{
						aux -> left = found -> right;
					}

					delete found;
					dim--;
				}

				else
				{
					Node<T>* aux = found -> parent;
					if(found == aux -> right)
					{
						aux -> right = found -> left;
					}

					else
					{
						aux -> left = found -> left;
					}

					delete found;
					dim--;					
				}
			}
		}
	}
}
#endif
