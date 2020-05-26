#pragma once
#ifndef __Tree_H__
#define __Tree_H__
#include <iostream>;
#include <cmath>;

using std::cout;


template <class ValType>
struct Val_Collum
{
	int key;
	ValType val;
	Val_Collum()
	{
		key = -1;
	}
	Val_Collum(int inp_key, ValType inp_val)
	{
		key = inp_key;
		val = inp_val;
	}
	Val_Collum(const Val_Collum &cop)
	{
		key = cop.key;
		val = cop.val;
	}
	Val_Collum& operator=(const Val_Collum &inp)
	{

		key = inp.key;
		val = inp.val;
		return *this;
	}
	bool operator==(Val_Collum &rigth)
	{
		return (key == rigth.key);
	}
	bool operator!=(Val_Collum &rigth)
	{
		return (key != rigth.key);
	}
	bool operator<(Val_Collum &rigth)
	{
		return (key < rigth.key);
	}
	bool operator>(Val_Collum &rigth)
	{
		return (key > rigth.key);
	}
	friend std::ostream& operator<<(std::ostream& out, Val_Collum &inp)
	{
		out << inp.val;
		return out;
	}
};

template <class ValType> class AVL_Tree
{
private:
	template <class ValType> struct TNode
	{
		TNode<ValType> *prev;
		TNode<ValType> *right;
		TNode<ValType> *left;
		int diff;
		ValType val;
		TNode()
		{
			prev = NULL;
			left = NULL;
			right = NULL;
			diff = 0;
		}
		TNode(const TNode<ValType> *cop)
		{
			prev = cop->prev;
			right = cop->right;
			left = cop->left;
			diff = cop->diff;
			val = cop->val;
		}
		TNode<ValType> operator=(const TNode<ValType> &cop)
		{
			prev = cop->prev;
			right = cop->right;
			left = cop->left;
			diff = cop->diff;
			val = cop->val;
			return *this;
		}
	};
	TNode<ValType> *head_node;
	int size;
	void cutbranch(TNode<ValType> *curnode)
	{
		if (curnode == NULL)
			return;
		TNode<ValType> *curright = curnode->right;
		TNode<ValType> *curleft = curnode->left;
		delete curnode;
		cutbranch(curright);
		cutbranch(curleft);
	}
	TNode<ValType>* findprev(ValType val, TNode<ValType> *step)
	{
		if (step == NULL)
			throw 1;
		if (val > step->val)
		{
			if (step->right == NULL)
				return step;
			return findprev(val, step->right);
		}
		else if (val < step->val)
		{
			if (step->left == NULL)
				return step;
			return findprev(val, step->left);
		}
		else
		{
			return step;
		}
	}
	TNode<ValType>* findnearest(TNode<ValType> *snode)
	{
		TNode<ValType> *near_right = NULL;
		if (snode->right != NULL)
			near_right = findnearest_right(snode);
		TNode<ValType> *near_left = NULL;
		if (snode->left != NULL)
			near_left = findnearest_left(snode);
		if ((near_left != NULL) && (near_right != NULL))
		{
			if (snode->val - near_left->val > near_right->val - snode->val)
				return near_right;
			else
				return near_left;
		}
		else if (near_left != NULL)
			return near_left;
		else if (near_right != NULL)
			return near_right;
		else 
			return snode;
	}
	TNode<ValType>* findnearest_right(TNode<ValType> *snode)
	{
		TNode<ValType> *tnear_node = snode->right;
		while (tnear_node->left != NULL)
			tnear_node = tnear_node->left;
		return tnear_node;
	}
	TNode<ValType>* findnearest_left(TNode<ValType> *snode)
	{
		TNode<ValType> *tnear_node = snode->left;
		while (tnear_node->right != NULL)
			tnear_node = tnear_node->right;
		return tnear_node;
	}
	void RecountDiff(TNode<ValType>* inp, int one)
	{
		TNode<ValType> *prev = inp->prev;
		if (prev == NULL)
			return;
		if (prev->left == inp)
		{
			prev->diff = prev->diff + one;
			if (prev->diff == 0)
			{
				if (one == -1)
					RecountDiff(prev, one);
				else
					return;
			}
			else if (prev->diff == 1)
				RecountDiff(prev, one);
			else if (prev->diff == 2)
			{
				CRotateRight(prev);
				if (prev->prev->diff == 0)
					return;
				else 
					RecountDiff(prev->prev, one);
			}
			else if (prev->diff == -1)
			{
				RecountDiff(prev, one);
			}
			else if (prev->diff == -2)
			{
				CRotateLeft(prev);
				if (prev->prev->diff == 0)
					return;
				else
					RecountDiff(prev->prev, one);
			}
		}
		else
		{
			prev->diff = prev->diff - one;
			if (prev->diff == 0) 
			{
				if (one == -1)
					RecountDiff(prev, one);
				else
					return;
			}
			else if (prev->diff == -1)
			{
				RecountDiff(prev, one);
			}
			else if (prev->diff == -2)
			{
				CRotateLeft(prev);
				if (prev->prev->diff == 0)
					return;
				else
					RecountDiff(prev->prev, one); 
			}
			else if (prev->diff == 1)
				RecountDiff(prev, one);
			else if (prev->diff == 2)
			{
				CRotateRight(prev);
				if (prev->prev->diff == 0)
					return;
				else
					RecountDiff(prev->prev, one);
			}
		}
	}
	void CRotateRight(TNode<ValType> *rt)
	{
		if (rt->left->diff == 1)
		{
			rt->diff = 0;
			rt->left->diff = 0;
			SmallRotateRight(rt);
		}
		else if (rt->left->diff == 0)
		{
			rt->diff = 1;
			rt->left->diff = -1;
			SmallRotateRight(rt);
		}
		else if (rt->left->diff == -1)
		{
			if (rt->left->right->diff == -1)
			{
				rt->diff = 0;
				rt->left->diff = 1;
				rt->left->right->diff = 0;
			}
			else if (rt->left->right->diff == 1)
			{
				rt->diff = -1;
				rt->left->diff = 0;
				rt->left->right->diff = 0;
			}
			else if (rt->left->right->diff == 0)
			{
				
				rt->diff = 0;
				rt->left->diff = 0;
				rt->left->right->diff = 0;
			}
			BigRotateRight(rt);
		}
	}
	void CRotateLeft(TNode<ValType> *rt)
	{
		if (rt->right->diff == -1)
		{
			rt->diff = 0;
			rt->right->diff = 0;
			SmallRotateLeft(rt);
		}
		else if (rt->right->diff == 0)
		{
			rt->diff = -1;
			rt->right->diff = 1;
			SmallRotateLeft(rt);
		}
		else if (rt->right->diff == 1)
		{
			if (rt->right->left->diff == 1)
			{
				rt->diff = 0;
				rt->right->diff = -1;
				rt->right->left->diff = 0;
			}
			else if (rt->right->left->diff == -1)
			{
				rt->diff = 1;
				rt->right->diff = 0;
				rt->right->left->diff = 0;
			}
			else if (rt->right->left->diff == 0)
			{
				rt->diff = 0;
				rt->right->diff = 0;
				rt->right->left->diff = 0;
			}
			BigRotateLeft(rt);
		}

	}
	void SmallRotateLeft(TNode<ValType> *top)
	{
		TNode<ValType> *next_top = top->right;
		TNode<ValType> *prev_top = top->prev;
		if (prev_top != NULL)
			if (top == prev_top->left)
				prev_top->left = next_top;
			else
				prev_top->right = next_top;
		top->right = next_top->left;
		top->prev = next_top;
		if (next_top->left != NULL)
			next_top->left->prev = top;
		next_top->left = top;
		next_top->prev = prev_top;
		if (prev_top == NULL)
			head_node = next_top;
	}
	void BigRotateLeft(TNode<ValType> *top)
	{

		SmallRotateRight(top->right);
		SmallRotateLeft(top);
	}
	void SmallRotateRight(TNode<ValType> *top)
	{
		TNode<ValType> *next_top = top->left;
		TNode<ValType> *prev_top = top->prev;
		if (prev_top != NULL)
			if (top == prev_top->right)
				prev_top->right = next_top;
			else
				prev_top->left = next_top;
		top->left = next_top->right;
		top->prev = next_top;
		if (next_top->right != NULL)
			next_top->right->prev = top;
		next_top->right = top;
		next_top->prev = prev_top;
		if (prev_top == NULL)
			head_node = next_top;
	}
	void BigRotateRight(TNode<ValType> *top)
	{
		
		SmallRotateLeft(top->left);
		SmallRotateRight(top);
	}
	
public:
	AVL_Tree() 
	{
		head_node = NULL;
		size = 0;
	}
	AVL_Tree(ValType beg)
	{
		head_node = new TNode<ValType>;
		head_node->diff = 0;
		head_node->val = beg;
		head_node->left = NULL;
		head_node->right = NULL;
		head_node->prev = NULL;
	}

	~AVL_Tree()
	{
		cutbranch(head_node);
	}
	ValType find(ValType fval)
	{
		TNode<ValType> *prev = findprev(fval, head_node);
		if (prev->val == fval)
			return prev->val;
		else
			throw 1;
	}
	void insert(ValType inpval)
	{
		if (head_node == NULL)
		{
			head_node = new TNode<ValType>;
			head_node->diff = 0;
			head_node->val = inpval;
			head_node->left = NULL;
			head_node->right = NULL;
			head_node->prev = NULL;
			return;
		}
		TNode<ValType> *prev = findprev(inpval, head_node);
		if (prev->val == inpval)
			throw 1;
		else if (prev->val < inpval)
		{
			prev->right = new TNode<ValType>;
			prev->right->prev = prev;
			prev->right->val = inpval;
			prev->right->left = NULL;
			prev->right->right = NULL;
			RecountDiff(prev->right, 1);
		}
		else
		{
			prev->left = new TNode<ValType>;
			prev->left->prev = prev;
			prev->left->val = inpval;
			prev->left->left = NULL;
			prev->left->right = NULL;
			RecountDiff(prev->left, 1);
		}

	}
	void swap_pointer(TNode<ValType> *first_pointer, TNode<ValType> *second_pointer)
	{
		TNode<ValType> *tmp = new TNode<ValType>;
		if (head_node == first_pointer)
			head_node = second_pointer;
		tmp->prev = second_pointer->prev;
		tmp->left = second_pointer->left;
		tmp->right = second_pointer->right;
		second_pointer->prev = first_pointer->prev;
		if (first_pointer->left == second_pointer)
			second_pointer->left = first_pointer;
		else
			second_pointer->left = first_pointer->left;
		if (first_pointer->right == second_pointer)
			second_pointer->right = first_pointer;
		else
			second_pointer->right = first_pointer->right;
		if (tmp->prev == first_pointer)
			first_pointer->prev = second_pointer;
		else
			first_pointer->prev = tmp->prev;
		first_pointer->left = tmp->left;
		first_pointer->right = tmp->right;
		if (second_pointer->prev != NULL)
			if (second_pointer->prev->left == first_pointer)
				second_pointer->prev->left = second_pointer;
			else
				second_pointer->prev->right = second_pointer;
		if (second_pointer->left != NULL)
			if (second_pointer->left->prev == first_pointer)
				second_pointer->left->prev = second_pointer;
			else
				if (second_pointer->right != NULL)
					second_pointer->right->prev = second_pointer;
		if ((first_pointer->prev != NULL) && (first_pointer->prev != second_pointer))
			if (first_pointer->prev->left == second_pointer)
				first_pointer->prev->left = first_pointer;
			else
				first_pointer->prev->right = first_pointer;
		if ((first_pointer->left != NULL) && (first_pointer->prev != second_pointer))
			if (first_pointer->left->prev == second_pointer)
				first_pointer->left->prev = first_pointer;
			else
				if (first_pointer->right != NULL)
					first_pointer->right->prev = first_pointer;
		delete tmp;
	}
	void erase(ValType delval)
	{
		if (head_node == NULL)
			throw 1;
		TNode<ValType> *dnode = findprev(delval, head_node);
		if (dnode->val != delval)
			throw 1;
		if ((dnode->right == NULL) && (dnode->left == NULL))
		{
			if (dnode->prev == NULL)
			{
				delete head_node;
				head_node = NULL;
				return;
			}
			
			RecountDiff(dnode, -1);
			if (dnode == dnode->prev->left)
			{
				
				dnode->prev->left = NULL;
			}
			else
				dnode->prev->right = NULL;
			delete dnode;
		}
		else
		{
			TNode<ValType> *snode = findnearest(dnode);
			swap_pointer(dnode, snode);
			RecountDiff(dnode, -1);
			if (dnode->right != NULL)
			{
				if (dnode->prev->left == dnode)
					dnode->prev->left = dnode->right;
				else if (dnode->prev->right == dnode)
					dnode->prev->right = dnode->right;
				dnode->right->prev = dnode->prev;
			}
			else if (dnode->left != NULL)
			{
				if (dnode->prev->left == dnode)
					dnode->prev->left = dnode->left;
				else if (dnode->prev->right == dnode)
					dnode->prev->right = dnode->left;
				dnode->left->prev = dnode->prev;
			}
			else 
			{
				if (dnode->prev->left == dnode)
					dnode->prev->left = NULL;
				else
					dnode->prev->right = NULL;
			}
			delete dnode;
		}
	}
	void print(TNode<ValType> *print_node)
	{
		if (print_node == NULL)
			return;
		std::cout << print_node->val << ' ';
		print(print_node->left);
		print(print_node->right);
	}
	TNode<ValType>* get_head()
	{
		return head_node;
	}
};
#endif