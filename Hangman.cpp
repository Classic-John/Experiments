// Pb8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

/*
Jocul spânzurătoarea: dintr-o multime de cuvinte distincte se alege aleator de către algoritm un cuvânt.
Pe ecran se afisează _ _ _ _ cu atâtea liniute câte litere are cuvântul ales (cu spatii între ele, pentru vizibilitate).
Apoi se asteaptă input de la utilizator câte o literă.
Dacă litera face parte din cuvânt, se completează spatiile corespunzătoare cu acea literă. Se repretă până când s-a completat cuvântul sau utilizatorul
a depăsit numărul de esecuri permise.
Exemplu: se permit 6 esecuri.

Se consideră cuvântul CONTRATENOR. Pe ecran initial apare
_ _ _ _ _ _ _ _ _ _ _
Se permite citirea unei litere si utilizatorul introduce A
Se afisează _ _ _ _ _ A _ _ _ _ _
Se mai citeste o literă, E
Se afisează _ _ _ _ _ A _ E _ _ _
Se citeste o literă, I
Se afisează EROARE, mai aveti 5 esecuri permise, _ _ _ _ _ A _ E _ _ _
Se citeste o literă O
_ O _ _ _ A _ E _ O _
Se citeste o literă, R
_ O _ _ R A _ E _ O R
Se citeste o literă, S
Se afisează EROARE, mai aveti 4 esecuri permise, _ O _ _ R A _ E _ O R
Se citeste o literă, T
_ O _T R A T E _ O R
Se citeste o literă, N _ O N T R A T E N O R
Se citeste o literă, C
C O N T R A T E N O R
FELICITĂRI ATI REUSIT!

*/

struct Info
{
public:
	std::vector<int> m_i;
	char m_cnt;
	int i;
	Info()
	{
		m_cnt = -1;
	}
	Info(int &i, const char& cnt)
	{
		m_i.push_back(i);
		m_cnt = cnt;
		this->i = 0;
	}
	void add()
	{
		m_cnt++;
	}
	void add_i(const char &ii)
	{
		m_i.push_back(ii);
	}
	void move()
	{
		i++;
	}
	int next()
	{
		return m_i[i];
	}
	int i_size()
	{
		return m_i.size();
	}
	~Info()
	{

	}
};

void chooseWord(std::string& word)
{
	srand(time(0));
	std::ifstream file;
	file.open("file.txt");
	if (!file)
	{
		std::cerr << "File error\n";
		exit(0);
	}
	int n = 0;
	file >> n;
	std::vector<std::string> words;
	word = "";
	while (file)
	{
		file >> word;
		words.push_back(word);
	}
	word = words[rand() % n];
	file.close();
}

void wordPreparation(std::unordered_map<char, Info>& info, const std::string& word)
{
	for (int i = 0; i < word.size(); i++)
	{
		Info ob(i, 0);
		if (info.try_emplace(word[i], ob).second == false)
		{
			info[word[i]].add_i(i);
		}
		info[word[i]].add();

	}
}

void showProgress(const std::string& progress)
{
	for (char i = 0; i < progress.size(); i++)
	{
		std::cout << progress[i] << " ";
	}
}

void resolve(std::unordered_map<char, Info>& info, const std::string& word)
{
	int n = word.size();
	std::string progress = "";
	for (char i = 0; i < word.size(); i++)
	{
		progress += "_";
	}
	char mistakes = 0;
	char c = 0;
	int guessed = 0;
	while (mistakes != 6)
	{
		std::cout << "Here is your progress :";
		showProgress(progress);
		std::cout << "\nInsert a character:";
		std::cin >> c;
		info[c].add();
		bool failed = false;
		int temp1 = info[c].i;
		int temp2 = info[c].i_size();
		if (info[c].m_cnt < 1)
		{
			mistakes++;
			info[c].m_cnt = -1;
			std::cout << "Wrong character. " << 6 - mistakes << " trys left\n";
			failed = true;
		}
		else if (info[c].i >= info[c].i_size())
		{
			mistakes++;
			std::cout << "Wrong character. " << 6 - mistakes << " trys left\n";
			failed = true;
		}
		if (mistakes == 6)
		{
			std::cout << "\nYOU HAVE BEEN HANGED\n";
			return;
		}
		if (failed == true)
		{
			continue;
		}
		progress[info[c].next()] = c;
		guessed++;
		info[c].move();
		if (guessed == word.size())
		{
			std::cout << "\n";
			showProgress(progress);
			std::cout << "\n\nYOU ESCAPED\n";
			return;
		}
	}
}


int main()
{
	std::unordered_map<char, Info> info;
	std::string word;
	chooseWord(word);
	wordPreparation(info, word);
	resolve(info, word);
	return 0;
}

