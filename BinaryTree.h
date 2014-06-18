#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include <deque>
#include <iostream>

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
	
	Node<T>* root;
	int dim;
	
	public:
	BinaryTree();
	~BinaryTree();
	void push(T val);
	void remove(T val);
	int size();
	
	class IteratorPostOrd
	{
		Node<T>* crt;
		std::deque<Node<T>*> stack;
		std::deque<Node<T>*> stack2;
		
		public:
		IteratorPostOrd(Node<T>* node)
		{
			crt = node;
			stack.push_front(crt);
			while(stack.empty() == false)
			{
				crt = stack.front();
				stack.pop_front();
				stack2.push_front(crt);
				
				if(crt != 0)
				{
					if(crt -> left != 0)
						stack.push_front(crt -> left);
					if(crt -> right != 0)
						stack.push_front(crt -> right);
				}
			}
			
			if(stack2.empty() == false)
			{
				crt = stack2.front();
				stack2.pop_front();
			}
			
			else
			{
				crt = 0;
			}
		}

		IteratorPostOrd& operator=(const IteratorPostOrd& it)
		{
			crt = it.crt;
			stack = it.stack;
			stack2 = it.stack2;
		}
	
		bool operator==(const IteratorPostOrd& it)
		{
			return (crt == it.crt);
		}
	

		bool operator!=(const IteratorPostOrd& it)
		{
			return (crt != it.crt);
		}
	

		T& operator*()
		{
			return crt -> info;
		}

		IteratorPostOrd operator++(int)
		{
			IteratorPostOrd aux(*this);
			++(*this);
			return aux;
		}
		
		IteratorPostOrd operator++()
		{
			if(stack2.empty() == false)
			{
				crt = stack2.front();
				stack2.pop_front();
			}
			
			else
			{
				crt = 0;
			}
			return (*this);
		}				
	};
	
	class IteratorPreOrd
	{
		Node<T>* crt;
		std::deque<Node<T>*> stack;
		
		public:
		IteratorPreOrd(Node<T>* node)
		{
			crt = node;
			if(node != 0)
			{
				if(node -> right != 0)
					stack.push_front(node -> right);
				if(node -> left != 0)
					stack.push_front(node -> left);
			}
		}

		IteratorPreOrd& operator=(const IteratorPreOrd& it)
		{
			crt = it.crt;
			stack = it.stack;
		}
	
		bool operator==(const IteratorPreOrd& it)
		{
			return (crt == it.crt);
		}
	

		bool operator!=(const IteratorPreOrd& it)
		{
			return (crt != it.crt);
		}
	

		T& operator*()
		{
			return crt -> info;
		}

		IteratorPreOrd operator++(int)
		{
			IteratorPreOrd aux(*this);
			++(*this);
			return aux;
		}
		
		IteratorPreOrd operator++()
		{
			if(stack.empty() == true)
			{
				crt = 0;
				return (*this);
			}
		
			else
			{
				crt = stack.front();
				stack.pop_front();
				if(crt -> right != 0)
					stack.push_front(crt -> right);
				if(crt->left != 0)
					stack.push_front(crt -> left);
				return (*this);
			}
		}	
	};
	
	class IteratorInOrd
	{

		Node<T>* crt;
		Node<T>* stacknode;
		std::deque<Node<T>*> stack;
		
		public:
		IteratorInOrd(Node<T>* node)
		{
			crt = node;
			stacknode = node;
			
			while(stacknode != 0)
			{
				stack.push_front(stacknode);
				stacknode = stacknode -> left;
			}
			
			if(stack.empty() == false)
			{
				crt = stack.front();
				stacknode = stack.front();
				stack.pop_front();
				stacknode = stacknode -> right;
			}
			
			else
			{
				crt = 0;
			}
		}

		IteratorInOrd& operator=(const IteratorInOrd& it)
		{
			crt = it.crt;
			stack = it.stack;
			stacknode = it.stacknode;
		}
	
		bool operator==(const IteratorInOrd& it)
		{
			return (crt == it.crt);
		}
	

		bool operator!=(const IteratorInOrd& it)
		{
			return (crt != it.crt);
		}
	

		T& operator*()
		{
			return crt -> info;
		}

		IteratorInOrd operator++(int)
		{
			IteratorInOrd aux(*this);
			++(*this);
			return aux;
		}

		IteratorInOrd operator++()
		{
			while(stacknode != 0)
			{
				stack.push_front(stacknode);
				stacknode = stacknode -> left;
			}
			
			if(stack.empty() == false)
			{
				crt = stack.front();
				stacknode = stack.front();
				stack.pop_front();
				stacknode = stacknode -> right;
			}
			
			else
			{
				crt = 0;
			}
			return (*this);
		}		
	};
	
	IteratorPreOrd begin_preord()
	{
		return IteratorPreOrd(root);
	}
	
	IteratorPostOrd begin_postord()
	{
		return IteratorPostOrd(root);
	}
	
	IteratorInOrd begin_inord()
	{
		return IteratorInOrd(root);
	}
	
	IteratorPreOrd begin()
	{
		return IteratorPreOrd(root);
	}

	IteratorPostOrd end_postord()
	{
		return IteratorPostOrd(0);
	}
	
	IteratorPreOrd end_preord()
	{
		return IteratorPreOrd(0);
	}
	
	IteratorInOrd end_inord()
	{
		return IteratorInOrd(0);
	}
	
	IteratorPreOrd end()
	{
		return IteratorPreOrd(0);
	}
	
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = 0;
	dim = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree() // parcurgere in adancime
{
	std::deque<Node<T>*> stiva;
	if(root != 0)
	{
		stiva.push_front(root);
		while(stiva.empty() == false)
		{
			Node<T>* crt = stiva.front();
			stiva.pop_front();
			if(crt -> right != 0)
			{
				stiva.push_front(crt -> right);
			}
			
			if(crt -> left != 0)
			{
				stiva.push_front(crt -> left);
			}
			
			delete crt;
		}
	}
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
				Node<T>* aux = found -> parent;
				if(aux -> right == found)
				{
					delete found;
					found = 0;
					aux -> right = 0;
				}
				
				else
				{
					delete found;
					found = 0;
					aux -> left = 0;
				}
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
					found = 0;
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
					found = 0;
					dim--;					
				}
			}
		}
	}
}
#endif
