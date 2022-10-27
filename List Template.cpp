#include <iostream>

template <class u>struct Node
{
public:
	u val;
	Node<u>* next;
	Node<u>* before;
	Node()
	{

	}
	Node(u val)
	{
		this->val = val;
	}
};

template <class T> class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int n;
	void alocare(Node<T>*& node)
	{
		node = new Node<T>;
		node->before = NULL;
		node->next = NULL;
	}
public:
	List()
	{
		head = NULL;
		tail = NULL;
		n = 0;
	}
	friend std::ostream& operator<<(std::ostream& COUT, Node<T>* i)
	{
		COUT << i->val << " ";
		return COUT;
	}
	bool empty()
	{
		return (n==0);
	}
	void push_back(Node<T>* newNode)
	{
		if (!empty())
		{
			tail->next = newNode;
			newNode->before = tail;
			tail = newNode;
		}
		else
		{
			head = newNode;
			tail = newNode;
		}
		n++;
		std::cout << "\n";
	}
	void push_front(Node<T>* newNode)
	{
		if (!empty())
		{
			head->before = newNode;
			newNode->next = head;
			head = newNode;
		}
		else
		{
			head = newNode;
			tail = newNode;
		}
		n++;
	std::cout << "\n";
	}
	void pop_back()
	{
		if (empty())
		{
			return;
		}
		Node<T>* temp = tail;
		if (n == 1)
		{
			delete temp;
			n--;
			return;
		}
		tail = temp->before;
		tail->next = NULL;
		delete temp;
		n--;
		std::cout << "\n";
	}
	void pop_front()
	{
		if (empty())
		{
			return;
		}
		Node<T>* temp = head;
		if (n == 1)
		{
			delete temp;
			n--;
			return;
		}
		head = temp->next;
		head->before = NULL;
		delete temp;
		n--;
		std::cout << "\n";
	}

	Node<T>* conditionedFind(Node<T>* node, int cnt)
	{
		int k = 1;
		for (Node<T>* i = head; k<=cnt; i = i->next)
		{
			if (k == cnt)
			{
				return i;
			}
			k++;
		}
		return NULL;
	}

	Node<T>* find(Node<T>*&node)
	{
		for (Node<T>* i = head; i; i = i->next)
		{
			if (i->val == node->val)
			{
				return i;
			}
		}
		return NULL;
	}
	void erase(Node<T>*& node)
	{
		if (empty()||!node)
		{
			return;
		}
		if (node == head)
		{
			pop_front();
			return;
		}
		if (node == tail)
		{
			pop_back();
			return;
		}
		Node<T>* temp = node;
		temp->before->next = temp->next;
		temp->next->before = temp->before;
		delete temp;
		n--;
		std::cout << "\n";
	}
	void remove(Node<T>* node)
	{
		if (empty())
		{
			return;
		}
		Node<T>* next=0;
		bool fin = false;
		for (Node<T>* i = head; i!=tail->next; i = next)
		{
			if (i != tail)
			{
				next = i->next;
			}
			else
			{
				next = i;
				fin = true;
			}
			if (i->val == node->val)
			{
				erase(i);
			}
			if (fin == true)
			{
				break;
			}
		}
		std::cout << "\n";
	}
	void insert(Node<T>* nodul, T val)
	{
		if (!nodul)
		{
			return;
		}
		Node<T>* nodNou=new Node<T>(val);
		if (nodul == tail)
		{
			push_back(nodNou);
			return;
		}
		if (nodul == head)
		{
			push_front(nodNou);
			return;
		}
		nodNou->next = nodul;
		if (nodul != head)
		{
			nodul->before->next = nodNou;
			nodNou->before = nodul->before->next;
		}
			nodul->before= nodNou;
		n++;
		std::cout << "\n";
	}
	void clear()
	{
		if (empty())
		{
			return;
		}
		Node<T>* next=0;
		bool iesiAfara = false;
		for (Node<T>* i = head; i!=tail->next; i = next)
		{
			if (i != tail)
			{
				next = i->next;
			}
			else
			{
				next = i;
				iesiAfara = true;
			}
			delete i;
			if (iesiAfara == true)
			{
				break;
			}
		}
		n = 0;
	}
	void show()
	{
		if (empty())
		{
			return;
		}
		for (Node<T>* i = head; i!=tail->next; i = i->next)
		{
			std::cout << i->val<<" ";
		}
		std::cout << "\n";
	}
	int size()
	{
		return n;
	}
};

void instructions()
{
	std::cout << "For push_front : 1\n";
	std::cout << "For push_back : 2\n";
	std::cout << "For pop_front : 3\n";
	std::cout << "For pop_back : 4\n";
	std::cout << "For find : 5\n";
	std::cout << "For erase : 6\n";
	std::cout << "For  remove: 7\n";
	std::cout << "For insert : 8\n";
	std::cout << "For empty: 9\n";
	std::cout << "For clear: A\n";
	std::cout << "For afisare : B\n";
	std::cout << "For size : C\n";
	std::cout << "For exit : D\n";
}

int main()
{
	List<int> l;
	instructions();

	while (1)
	{
		int cnt = 1;
		char d = 0;
		int val = 0;
		Node<int>* temp = new Node<int>(0);
		int i = 1;
		std::cin >> d;
		switch (d)
		{
		case'1':
			std::cout << "Add a number:";
			std::cin >> val;
			temp->val = val;
			l.push_front(temp);
			break;

		case'2':
			std::cout << "Add a number:";
			std::cin >> val;
			temp->val = val;
			l.push_back(temp);
			break;
		case'3':
			l.pop_front();
			std::cout << "Deleted\n";
			break;
		case'4':
			l.pop_back();
			std::cout << "Deleted\n";
			break;
		case'5':
			std::cout << "What number do you want to find?:";
			std::cin >> val;
			temp->val = val;
			if (l.find(temp))
			{
				std::cout << "Found\n";
			}
			else
			{
				std::cout << "Not found\n";
			}
			break;
		case'6':
			std::cin >> val;
			temp->val = val;
			temp = l.find(temp);
			l.erase(temp);
			std::cout << "Deleted\n";
			break;
		case'7':
			std::cout << "Number to be removed:";
			std::cin >> val;
			temp->val = val;
			l.remove(temp);
			std::cout << "Terminated\n";
			break;
		case'8':
			std::cout << "The value and the index:";
			std::cin >> val >> i;
			if (i > l.size())
			{
				std::cout << "Out of range\n";
				break;
			}
			cnt = 1;
			temp = l.conditionedFind(temp, i);
			l.insert(temp, val);
			std::cout << "Inserted\n";
			break;
		case'9':
			if (l.empty())
			{
				std::cout << "The list is empty\n";
			}
			else
			{
				std::cout << "Not empty\n";
			}
			break;
		case'A':
			l.clear();
			std::cout << "Cleared\n";
			break;
		case'B':
			l.show();
			break;
		case'C':
			std::cout<<"Size:" << l.size() << "\n";
			break;
		case'D':
			std::cout << "Thanks for stopping by\n";
			return 0;
		}
	}
	return -1;
}