// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef __STACK_H__
#define __STACK_H__
const int MAX_STACK_SIZE = 1000000;

template <class ValType>
class Stack
{
private:
	int stackSize;
	int top;
	ValType* data;
public:
	Stack()
	{
		stackSize = 100; data = new ValType[stackSize]; top = -1;
	}
	Stack(int size)
	{
		if (!size) throw "Can't have null size";
		if (size > MAX_STACK_SIZE) throw "Size more than MAX_VECTOR_SIZE";
		stackSize = size; data = new ValType[stackSize]; top = -1;
	}
	ValType getTop();
	ValType getSize();
	ValType pop();
	void push(const ValType& x);
	void clear();
	bool isEmpty();
	bool isFull();
};
template <class ValType>
void Stack<ValType>::clear()
{
	top = -1;
	delete[] data;
	data = new ValType[stackSize];
}
template<class ValType>
ValType Stack<ValType>::getSize()
{
	return top + 1;
}
template <class ValType>
ValType Stack<ValType>::getTop()
{
	if (isEmpty())
		throw "Stack is empty";
	return data[top];
}
template <class ValType>
bool Stack<ValType>::isEmpty()
{
	return top == -1;
}
template <class ValType>
void Stack <ValType>::push(const ValType& x)
{
	if (isFull()) {
		stackSize = (stackSize + 1) * 2;
		ValType* tmp = new ValType[stackSize];
		for (int i = 0; i < top + 1; i++) {
			tmp[i] = data[i];
		}
		delete[] data;
		data = tmp;
	}
	top++;
	data[top] = x;
}
template <class ValType>
ValType Stack <ValType>::pop()
{
	if (!isEmpty())
		return data[top--];
	else throw "Stack is empty";
}
template <class ValType>
bool Stack<ValType>::isFull()
{
	return top >= stackSize - 1;
}
#endif