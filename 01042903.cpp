#include <iostream>

using namespace std;
class stack_size_error : public length_error {
public:
	explicit stack_size_error(const std::string& msg);
};
class stack_bad_alloc : public std::bad_alloc {
public:
	explicit stack_bad_alloc(void);
};
class stack_overflow : public std::logic_error {
public:
	explicit stack_overflow(const std::string& msg);
};
class stack_empty : public std::logic_error {
public:
	explicit stack_empty(const std::string& msg);
};

stack_size_error::stack_size_error(const std::string& msg) : std::length_error(msg) {};
stack_bad_alloc::stack_bad_alloc(void) : std::bad_alloc() {};
stack_overflow::stack_overflow(const std::string& msg) : std::logic_error(msg) {};
stack_empty::stack_empty(const std::string& msg) : std::logic_error(msg) {};

class Stack {
private:
	int* stackstore;
	int stacksize;
	int SP;
public:
	Stack(int size = 100);
	~Stack();
	void push(int value);
	int pop(void);
};

Stack::Stack(int size) {
	if (size <= 0)
		throw stack_size_error("Розмір має бути додатним!");
	try {
		stackstore = new int[size];
	}
	catch (const std::bad_alloc& ba) {
		delete[] stackstore; 
		throw stack_bad_alloc();
	}
	stacksize = size;
	SP = 0;
}

Stack::~Stack(void) {
	cout << "deleted" << endl;
	delete[] stackstore;
}

void Stack::push(int value) {
	if (SP == stacksize)
		throw stack_overflow("Переповнення стоса!");
	stackstore[SP++] = value;
}

int Stack::pop(void) {
	if (SP == 0)
		throw stack_empty("Стос порожній!");
	return stackstore[--SP];
}

int main() 
{
	system("chcp 1251>nul");
	Stack stk;

	try
	{
		int value = stk.pop();
	}
	catch (stack_empty& exc)
	{
		cout << "Стос порожній: " << exc.what() << endl;
	}
	try {
		for (int i = 0; i < 100; i++) {
			stk.push(i);
		}
		stk.push(8);

	}
	catch (stack_overflow& exc)
	{
		cout << "Переповнення стоса: елемент не доданий." << endl;
	}

	try 
	{
		Stack stk1(-10);
	}
	catch (stack_size_error& exc) 
	{
		cout << "Помилка розміру стоса: " << exc.what() << endl;
	}

	try
	{
		Stack stk2(1000000000);
	}
	catch (stack_bad_alloc& exc) 
	{
		cout << "Помилка виділення пам'яті для стоса." << endl;
	}

	cout << stk.pop() << endl;
	return 0;
}