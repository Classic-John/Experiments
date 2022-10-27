#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>

template <class T> struct Node
{
public:
	T val;
	Node<T>* next;
	Node()
	{

	}
	Node(T val)
	{
		this->val = val;
	}
};

template <class A> class Queue
{
private:
	Node<A>* front;
	Node<A>* rear;
	int n;
	//It is better to pass the original when using templates so the risk of getting an error decreases.
	Node<A>* createNode(Node<A>*& node, A val)
	{
		node = new Node<A>(val);
		node->next = NULL;
		return node;
	}
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
		n = 0;
	}
	bool empty()
	{
		return (front == NULL);
	}
	int size()
	{
		return n;
	}
	void push(A& val)
	{
		Node<A>* node = createNode(node, val);
		if (empty())
		{
			front = node;
			rear = node;
		}
		else
		{
			rear->next = node;
			rear = node;
		}
		n++;
	}
	void pop()
	{
		Node<A>* temp = front;
		front = front->next;
		delete temp;
	}
	A peek()
	{
		return front->val;
	}
	A back()
	{
		return rear->val;
	}
	void clear()
	{
		Node<A>* temp = 0;
		for (Node<A>* i = front; i != rear->next; i = temp)
		{
			temp = i->next;
			delete i;
		}
	}
};

template<class A, class B> struct Student
{
public:
	A name;
	A surname;
	B time;
	Student()
	{

	}
	Student(A name, A surname, B time)
	{
		this->name = name;
		this->surname = surname;
		this->time = time;
	}

};

void readPb3(Queue<Student<std::string, int>>& queue, int& x)
{
	int n = 0;
	std::ifstream file;
	file.open("file1.txt");
	if (!file)
	{
		std::cerr << "File didn't open\n";
		exit(0);
	}
	file >> n >> x;

	std::string t1 = "", t2 = "";
	int nr = 0;
	while (file)
	{
		file >> t1 >> t2 >> nr;
		Student<std::string, int> temp(t1, t2, nr);
		queue.push(temp);
	}
	file.close();
}

void resolve(Queue<Student<std::string, int>>& queue, int x)
{
	Student<std::string, int> temp;
	Student<std::string, int> temp1("", "", 0);
	while (!queue.empty() && x - queue.peek().time > -1)
	{
		temp = queue.peek();
		x -= temp.time;
		queue.pop();
	}
	if (!queue.empty())
	{
		std::fstream file;
		file.open("file2.txt");
		if (!file)
		{
			std::cerr << "Second file didn't open\n";
		}
		while (!queue.empty())
		{
			temp = queue.peek();
			if (temp1.name == temp.name && temp1.surname == temp.surname)
			{
				queue.pop();
				continue;
			}
			file << temp.name << " " << temp.surname << " " << temp.time << "\n";
			temp1 = temp;
			queue.pop();
		}
		file.close();
	}
}

int main()
{
	Queue<Student<std::string, int>> queue;
	int x = 0;
	readPb3(queue, x);
	resolve(queue, x);
	return 0;
}