#include "Huffman_tree.h"
const string filename = "input.txt";
const bool debug_mode = true;
using namespace std;

/* ��������� ������ �� ����� � string text */
string get_data(string filename)
{
	string text;
	fstream input;
	input.open(filename, ios::in);
	getline(input, text);
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		text += temp;
	}
	input.close();
	return text;
}

/* �������� �������� */
string get_repeat(string text)
{
	string abc;
	bool exit_flag = 0;
	abc.push_back(text[0]);
	for (int i = 1; i < text.size(); i++)
	{
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++)
		{
			if (abc[j] == text[i])						//���� � ����� �������� ��� ���� ����� �����
			{
				exit_flag = 1;							//�������, ���� ����� ����� �����
				break;
			}
		}
		if (exit_flag == 1)								//���� �� �������� ����� �����
		{
			continue;									//��������� �� ��������� �������� ��� ����. �����
		}
		else											//���� ����� ������� �� ����
		{
			abc.push_back(text[i]);
			continue;
		}
	}
	return abc;
}

/* ��������� ������� ������� ������������� �������� */
void get_frequency(string text, int *frequencies, string abc)
{
	for (int i = 0; i < abc.size(); i++)
	{
		frequencies[i] = 0;
	}
	for (int j = 0; j < abc.size(); j++)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (abc[j] == text[i])
			{
				frequencies[j]++;
			}
		}
	}
}

/* ���� ������� ������ � ���������� */
string get_input()
{
	string text;
	cout << "Message: ";
	getline(std::cin, text);
	cout << endl;
	return text;
}

void opener()
{
	cout << "	" << " _   _          __   __                          " << endl;
	cout << "	" << "| | | |        / _| / _|                         " << endl;
	cout << "	" << "| |_| | _   _ | |_ | |_  _ __ ___    __ _  _ __  " << endl;
	cout << "	" << "|  _  || | | ||  _||  _|| '_ ` _ \\  / _` || '_ \\ " << endl;
	cout << "	" << "| | | || |_| || |  | |  | | | | | || (_| || | | |" << endl;
	cout << "	" << "\\_| |_/ \\__,_||_|  |_|  |_| |_| |_| \\__,_||_| |_|" << endl;
	cout << "	" << "c o d i n g " << endl << endl;
}

int main()
{
	opener();
	string choose;
	cout << "input from (0) - keyboard, (1) - file: ";
	getline(std::cin, choose);
	cout << endl;
	string text;
	if (choose[0] == '0')
	{
		text = get_input();									//���� � ����������
	}
	else if (choose[0] == '1')
	{
		text = get_data(filename);							//���� �� �����
	}
	else
	{
		cout << "incorrect input" << endl;
		exit(1);
	}

	/*�������� ������ ������*/
	string abc = get_repeat(text);
	int *frequencies = new int[abc.size()];
	get_frequency(text, frequencies, abc);

	if (debug_mode)
	{
		cout << "Text is: " << text << endl;
		cout << "Alphabet: " << abc << endl;
		cout << "Size of alphabet: " << abc.size() << endl;
		cout << "Frequencies: ";
		for (int i = 0; i < abc.size(); i++)
		{
			cout << frequencies[i];
		}
		cout << endl;
	}

	/* ��������� ����������: ���� ������ */
	bool flag_ex = 0;
	if (abc.size() < 2)
	{
		flag_ex = !flag_ex;
	}

	/* ����������� */
	huffman_coding encoding;
	cout << endl << "Character: Code-word" << endl;
	encoding.HuffmanCodes(abc, frequencies, flag_ex);
	encoding.encode_text(text);

	string temp = encoding.get_encode();
	cout << endl << "Code-string: " << temp;

	/* �������������� */
	temp = encoding.decode_text(temp, flag_ex);
	cout << endl << "Decode-string: " << temp << endl;
	return 0;
}