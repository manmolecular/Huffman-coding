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
		void printCodes(huffman_tree_node* root, string str);						// ������ �����
		void HuffmanCodes(char data[], int freq[], int size);						// �����������
		void print_map();															// ����� ���� ��� ��������
		void encode_text(string text);												// �����������-������ � ����� �������
		string get_encode();														// ������� encode ������
		void output_in_file();														// ����� � ����
		void decode_text_from_map(string text);										// �������������� ����� map (�������)
		string decode_text(string str);												// �������������� ����� ������
};

/* ����� ������ � ����*/
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

/* ��������� ������� ������ */
string huffman_coding::get_encode()
{
	return encode;
}

/* �������������� ������ */
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

/* �������������� ������ ����� map */
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

/* ����� map �� ����� */
void huffman_coding::print_map()
{
	cout << "Map contains: " << endl;
	for (auto it = replace_abc.begin(); it != replace_abc.end(); ++it)			//����� �� �����
	{
		cout << it->first << " : " << it->second << endl;
	}
}

/* �������������� ������ */
string huffman_coding::decode_text(string str)
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
		i = main_counter;
	}
	return decode;
}

/* ����� ������ ����� �������� � ���� � ��������� */
void huffman_coding::printCodes(pointer_huffman root, string str)
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

// �������� ������� ������� ������ ������ ��������
// � �������� ���� ������ ��� ����������� 
// ������ ��������
void huffman_coding::HuffmanCodes(char data[], int freq[], int size)
{
	pointer_huffman left, right, top;

	// ������� ���� � ������� � �������� (�������� compare ������� ���������)
	priority_queue<pointer_huffman, vector<huffman_tree_node*>, compare> min_heap;
	for (int i = 0; i < size; ++i)
	{
		pointer_huffman temp = new huffman_tree_node(data[i], freq[i]);
		min_heap.push(temp);		
	}

	// ���� ������ ������� �� ����� �� �������
	while (min_heap.size() != 1)
	{
		// ������� ��� ����������� �� ������� �������� �� ������
		left = min_heap.top();
		min_heap.pop();

		right = min_heap.top();
		min_heap.pop();

		// ������� ����� ���� � ��������, ������ ����� ���� 
		// ������ �����

		top = new huffman_tree_node('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		min_heap.push(top);
	}

	// ������� �� ����� ��� ��������
	root_main = min_heap.top();
	printCodes(root_main, "");
}