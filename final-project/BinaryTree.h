#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include "BlackScholes.h"

template <typename T>
class BinaryTree {
	private :
		int _depth; //represents N
		std::vector<std::vector<T>> _tree; //hold data of type T
	public :
		BinaryTree(int depth = 0) : _depth{ depth } { setDepth(depth); }
		T getNode(int, int) const;
		void setDepth(int);
		void setNode(int, int, T);
		void display() const; 
		int verifIndex(int, int) const;
		int maxDigit() const;

		//liens antoine (� ne pas effacer svp): 
		//https://www.geeksforgeeks.org/vector-in-cpp-stl/
		//https://cplusplus.com/reference/vector/vector/ (best)
		//https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
		//https://stackoverflow.com/questions/40054600/searching-binary-tree-of-objects-for-a-single-class-member

		//https://www.youtube.com/watch?v=B6eIfpcAXKk
};

#pragma region TESTS BINARY TREE : 
void test_bt_1(int);
void test_bt_2();
#pragma endregion 

class CRRPricer {
	private :
		//Option* _option = nullptr;
		int _depth;
		double _assetPrice;
		double _up;
		double _down;
		double _interestRate;
		BinaryTree<double> _tree;
	public:
		CRRPricer(/*Option* option,*/ int depth, double assetPrice, double up, double down, double interestRate) :
			/*_option{option},*/ _depth{depth}, _assetPrice{assetPrice}, _up{up}, _down{down}, _interestRate{interestRate} {
			BinaryTree<double> _tree(depth);
		}
		void compute();
		double get(int n, int i) { return _tree.getNode(n, i); }
		double operator()(bool closedForm = false) {
			if (closedForm) {

			}
			else {
				compute();
			}
		}
};