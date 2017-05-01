#pragma once
#include "Huffman_tree.h"
#include <cstddef>

class huffman_tree_node
{
	private:
		char data;									// Символ
		unsigned freq;								// Частота
		huffman_tree_node *left, *right;			// Левый и правый потомок
		friend class huffman_coding;
	public:
		huffman_tree_node() {};
		huffman_tree_node(char _data, unsigned _freq);			// Создание узла
};

typedef huffman_tree_node *pointer_huffman;
typedef huffman_tree_node **p_pointer_huffman;

inline huffman_tree_node::huffman_tree_node(char _data, unsigned _freq)
{
	left = right = NULL;
	data = _data;
	freq = _freq;
}