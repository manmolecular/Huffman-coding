#pragma once
#include "huffman_tree_node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#define filename_output "output_code.txt"
using namespace std;

class huffman_coding
{
	private:
		pointer_huffman root_main;
		map <char, string> replace_abc;
		string encode;
		string decode;
	public:
		struct compare
		{
			bool operator()(huffman_tree_node* left, huffman_tree_node* right)
			{
				return (left->freq > right->freq);
			}
		};
		void printCodes(huffman_tree_node* root, string str);						// Печать кодов
		void HuffmanCodes(string data, int freq[], bool flag_ex);					// Кодирование
		void print_map();															// Вывод мапы для проверки
		void encode_text(string text);												// Кодирование-замена в самой стринге
		string get_encode();														// Возврат encode строки
		void output_in_file();														// Вывод в файл
		void decode_text_from_map(string text);										// Раскодирование через map (пробное)
		string decode_text(string str, bool flag_ex);								// Раскодирование через дерево
};

/* Вывод текста в файл*/
void huffman_coding::output_in_file()
{
	fstream file;
	file.open(filename_output, ios::out);
	for (int i = 0; i < encode.size(); i++)
	{
		file << encode[i];
	}
	file.close();
}

/* Получение кодовой строки */
string huffman_coding::get_encode()
{
	return encode;
}

/* Раскодирование текста */
void huffman_coding::encode_text(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		for (auto it = replace_abc.begin(); it != replace_abc.end(); ++it)
		{
			if (text[i] == it->first)
			{
				encode += it->second;
			}
		}
	}
}

/* Раскодирование текста через map */
void huffman_coding::decode_text_from_map(string text)
{
	for (auto it = replace_abc.begin(); it != replace_abc.end(); ++it)
	{
		int replace_position = text.find(it->second);
		string temp;
		temp.push_back((char)it->first);
		text.replace(replace_position, it->second.size(), temp);
		cout << "String is: " << text << endl;
	}
}

/* Вывод map на экран */
void huffman_coding::print_map()
{
	cout << "Map contains: " << endl;
	for (auto it = replace_abc.begin(); it != replace_abc.end(); ++it)			//вывод на экран
	{
		cout << it->first << " : " << it->second << endl;
	}
}

/* Раскодирование текста */
string huffman_coding::decode_text(string str, bool flag_ex)
{
	int main_counter = 0;
	string decode = "";
	for (int i = main_counter; i < str.size();)
	{
		pointer_huffman temp = root_main;
		while (true)
		{
			if (str[i] == '0')
			{
				if (temp->left != NULL)
				{
					temp = temp->left;
				}
				else
				{
					decode += temp->data;
					break;
				}
			}
			else
			{
				if (temp->right != NULL)
				{
					temp = temp->right;
				}
				else
				{
					decode += temp->data;
					break;
				}
			}
			i++;
			main_counter = i;
		}
		
		if (flag_ex)
		{
			i++;
		}
		else
		{
			i = main_counter;
		}
	}
	return decode;
}

/* Вывод набора кодов Хаффмана в паре с символами */
void huffman_coding::printCodes(huffman_tree_node* root, string str)
{
	if (!root)
	{
		return;
	}
	if (root->data != '$')
	{
		cout << root->data << ": " << str << endl;
		replace_abc.insert(pair <char, string>(root->data, str));
	}

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// Основная функция которая строит дерево Хаффмана
// И печатает коды обходя это построенное 
// Дерево Хаффмана
void huffman_coding::HuffmanCodes(string data, int freq[], bool flag_ex)
{
	pointer_huffman left, right, top;

	// Создаем узлы с данными и частотой (учитывая compare функцию сравнения)
	priority_queue<pointer_huffman, vector<huffman_tree_node*>, compare> min_heap;
	for (int i = 0; i < data.size(); ++i)
	{
		pointer_huffman temp = new huffman_tree_node(data[i], freq[i]);
		min_heap.push(temp);		
	}

	// Пока размер очереди не дойдёт до единицы
	while (min_heap.size() != 1)
	{
		// Достаем два минимальных по частоте элемента из дерева
		left = min_heap.top();
		min_heap.pop();

		right = min_heap.top();
		min_heap.pop();

		// Создаем новый узел с частотой, равной сумме двух 
		// частот узлов c наименьшей частотой

		top = new huffman_tree_node('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		min_heap.push(top);
	}

	// Выводим на экран код Хаффмана
	root_main = min_heap.top();
	if (flag_ex)
	{
		printCodes(root_main, "0");
	}
	else
	{
		printCodes(root_main, "");
	}
}