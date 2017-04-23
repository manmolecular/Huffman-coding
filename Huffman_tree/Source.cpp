#include "Huffman_tree.h"
#define alphabet 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
const string filename = "input.txt";
const bool debug_mode = true;
using namespace std;

/* Помещение текста из файла в string text */
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

/* Создание алфавита */
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
			if (abc[j] == text[i])						//Если в нашем алфавите уже есть такая буква
			{
				exit_flag = 1;							//Выходим, если нашли такую букву
				break;
			}
		}
		if (exit_flag == 1)								//Если мы находили букву ранее
		{
			continue;									//Переходим на следующую итерацию для след. буквы
		}
		else											//Если буква найдена не была
		{
			abc.push_back(text[i]);
			continue;
		}
	}
	return abc;
}

/* Получение массива частоты использования символов */
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

/* Ввод входого текста с клавиатуры */
string get_input()
{
	string text;
	cout << "Message: ";
	getline(std::cin, text);
	cout << endl;
	return text;
}

int main()
{
	string text;
	text = get_input();									//Ввод с клавиатуры
	//text = get_data(filename);						//Ввод из файла

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

	char *arr = new char[abc.size()];
	strncpy(arr, abc.c_str(), abc.length() + 1);

	huffman_coding encoding;
	cout << endl << "Character: Code-word" << endl;
	encoding.HuffmanCodes(arr, frequencies, abc.size());
	encoding.encode_text(text);

	string temp = encoding.get_encode();
	cout << endl << "Code-string: " << temp;

	temp = encoding.decode_text(temp);
	cout << endl << "Decode-string: " << temp << endl;
	return 0;
}