// 3.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <typeinfo>
#include <optional>

template<class A, class B> class Hashmap
{
private:
	std::vector<std::list<std::pair<B, std::string>>> tabel;
	int maxBuckets;
	int expectedNr;
	int curr_nr;
	float loadFactor;
public:
	Hashmap()
	{
		this->maxBuckets = 10;
		this->expectedNr = 10;
		this->curr_nr = 0;
		for (int i = 0; i < 10; i++)
		{
			std::list<std::pair<B, std::string>> temp;
			tabel.push_back(temp);
		}
		this->loadFactor = ((expectedNr / maxBuckets) + 0.0 + (expectedNr % maxBuckets));
	}
	Hashmap(int expectedNr, int maxDim)
	{
		this->curr_nr = 0;
		this->maxBuckets = maxDim;
		this->expectedNr = expectedNr;
		for (int i = 0; i < maxDim; i++)
		{
			std::list<std::pair<B, std::string>> temp;
			tabel.push_back(temp);
		}
		float intPart = expectedNr / maxBuckets;
		intPart += 0.0;
		this->loadFactor = intPart + (expectedNr % maxBuckets);
		if (full())
		{
			reHashing();
		}
	}
	int MaxBuckets()
	{
		return maxBuckets;
	}
	int size()
	{
		return curr_nr;
	}
	bool empty()
	{
		return (tabel.size() == 0);
	}
	bool full(int i)
	{
		return((tabel[i].size() + 0.0) > loadFactor);
	}
	void clear()
	{
		tabel.clear();
		maxBuckets = 0;
		curr_nr = 0;
	}
	void reHashing()
	{
		if (empty())
		{
			maxBuckets = 10;
			expectedNr = 9;
			loadFactor = ((expectedNr / maxBuckets) + 0.0 + (expectedNr % maxBuckets));
			for (int i = 0; i < maxBuckets; i++)
			{
				std::list < std::pair<B, std::string>> temp;
				tabel.push_back(temp);
			}
			return;
		}
		int cnt = 1;
		if(loadFactor> 1)
		{
			cnt += (int)loadFactor;
		}
		else
		{
			cnt++;
		}
		int prevBuckets = maxBuckets;
		maxBuckets *= cnt;
		expectedNr *= cnt;
		std::vector<std::list<std::pair<B, std::string>>> temp;
		for (int i = 0; i < prevBuckets; i++)
		{
			std::list<std::pair<B, std::string>>bucket;
			temp.push_back(bucket);
		}
		for (int i = 0; i < prevBuckets; i++)
		{
			for (std::pair<B,std::string>&x : tabel[i])
			{
				temp[i].push_back(x);
			}
		}
		tabel.clear();
		for (int i = 0; i < maxBuckets; i++)
		{
			std::list<std::pair<B, std::string>>oneList;
			tabel.push_back(oneList);
		}
		int in = 0;
		for (int i = 0; i < temp.size(); i++)
		{
			for (std::pair<B,std::string>& x : temp[i])
			{
				for (int i = 0; i < x.second.size(); i++)
				{
					in += x.second[i] - '0';
				}
				in %= maxBuckets;
				tabel[in].push_back(x);
			}


		}
	}
	std::pair<int, std::string> ind(A key)
	{
		std::string address = "";
		int cnt = 0;
		if (typeid(key).name() != typeid(std::string).name())
		{
			std::fstream ref;
			ref.open("references.txt");
			if (!ref)
			{
				std::cerr << "References file error\n";
				exit(0);
			}
			ref << &key;
			std::getline(ref, address);
			ref.close();
		}
		else
		{
			address = key;
		}
		int index = 0;
		for (int i = 0; i < address.size(); i++)
		{
			index += address[i] - '0';
		}
		index %= maxBuckets;
		std::pair<int, std::string> result = { index,address };
		return result;
	}
	void insert(A key, B value)
	{
		if (empty())
		{
			reHashing();
		}
		std::pair<int, std::string> i = ind(key);
		if (full(i.first))
		{
			reHashing();
		}
		curr_nr++;
		if (curr_nr == tabel.size())
		{
			reHashing();
		}
		tabel[i.first].push_back({ value,i.second });
		
	}
	//It can't deduce the argument type here (in erase), reason why i have avoided STL iterator-eraseand went for another way to solve //this.

	void erase(A key, B value)
	{
		if (empty())
		{
			return;
		}
		std::pair<int, std::string> i = ind(key);
		for (std::pair<B, std::string>& x : tabel[i.first])
		{
			if (x.second == i.second)
			{
				std::list<std::pair<B,std::string>>temp;
				for (std::pair<B,std::string>y : tabel[i.first])
				{
					if (y.second == i.second)
					{
						continue;
					}
					temp.push_back(y);
				}
				tabel[i.first].clear();
				for (std::pair<B,std::string&> x : temp)
				{
					tabel[i.first].push_back(x);
				}

				curr_nr--;
				return;
			}
		}
	}
	B* find(A key)
	{
		std::pair<int, std::string> details = ind(key);
		for (std::pair<B,std::string>& x : tabel[details.first])
		{
			if (x.second == details.second)
			{
				B* temp = &x.first;
				return temp;
			}
		}
		return NULL;
	}
};

void readPb1(std::pair<std::string, std::string>*& members, int& n)
{
	std::ifstream file;
	file.open("file.txt");
	if (!file)
	{
		std::cerr << "File error\n";
		exit(0);
	}
	std::string job = "";
	std::string name = "";
	file >> n;
	members = new std::pair<std::string, std::string>[n];
	int k = 0;
	while (file)
	{
		if (k >= n)
		{
			break;
		}
		file >> job >> name;
		members[k++] = { job,name };
	}
	file.close();
}
void instructions()
{
	std::cout << "For insertion: 1\n";
	std::cout << "For find: 2\n";
	std::cout << "For erase: 3\n";
	std::cout << "For max number of buckets: 4\n";
	std::cout << "For current size: 5\n";
	std::cout << "For clearing the hash: 6\n";
	std::cout << "For exit: 7\n";
}

int main()
{
	std::pair<std::string, std::string>* members;
	int n = 0;
	int i = 0;
	Hashmap<std::string, std::string> hash;
	std::string temp1 = "";
	readPb1(members, n);
	std::string* temp=NULL;
	instructions();
	char d = 0;
	while (1)
	{
		std::cin >> d;
		switch (d)
		{
		case '1':
			std::cout << "Choose an index within [" << 0 << "," << n - 1 << "]:";
			std::cin >> i;
			if (i >= n)
			{
				std::cout << "The index it outside of bounds.\n";
				break;
			}
			hash.insert(members[i].first, members[i].second);
			break;
		case'2':
			std::cout << "Choose the index:";
			std::cin >> i;
			if (i >= n)
			{
				std::cout << "The index it outside of bounds.\n";
				break;
			}
			temp = hash.find(members[i].first);
			if (temp == NULL)
			{
				std::cout << "The member doesn't exist\n";
				break;
			}
			temp1 = *temp;
			if (temp1.size())
			{
				std::cout << "The member exists\n";
			}
			break;
		case'3':
			std::cout << "Choose index:";
			std::cin >> i;
			if (i >= n)
			{
				std::cout << "The index it outside of bounds.\n";
				break;
			}
			hash.erase(members[i].first, members[i].second);
			break;
		case'4':
			std::cout << hash.MaxBuckets() << "\n";
			break;
		case'5':
			std::cout << hash.size() << "\n";
			break;
		case'6':
			hash.clear();
			std::cout << "Cleared\n";
			break;
		case'7':
			delete[] members;
			exit(0);
		}
	}
	return 0;
}