#include"myListNode.h"

template<class dataType>
class myList {
private:
	int maxSize;
	int top;
	listNode<dataType> * head;
public:
	myList(int = 0);
	~myList();
	bool Empty();
	void Clear();
	bool Push(dataType);
	bool Pop();
	bool Top(dataType&);
	template<class dataType>
	friend ostream & operator<<(ostream &, myList<dataType> &);
	dataType& operator [] (int i);
};

template<class dataType>
myList<dataType>::myList(int max ) {
	listNode<dataType> * temp = this->head;
	this->maxSize = max;
	this->top = -1;
	for (int i = 0; i < max; i++)
	{
		if (i == 0)
		{
			this->head = new listNode<dataType>;
			temp = head;
			this->head->next_node_point = NULL;
		}
		else
		{
			this->head = new listNode<dataType>;
			this->head->next_node_point = temp;
			temp = this->head;
		}
	}
	this->head = temp;
}

template<class dataType>
myList<dataType>::~myList() {
	listNode<dataType> *temp =NULL;
	if (this->head != NULL)
	{
		temp = this->head->next_node_point;
	}
	for (int num = 0; num < this->maxSize; num++)
	{
		delete this->head;
		this->head = temp;
		if (num != this->maxSize - 1)
			temp = temp->next_node_point;
	}
}

template<class dataType>
bool myList<dataType>::Empty() {
	if (this->top == -1)  return true;
	return false;
}

template<class dataType>
void myList<dataType>::Clear() {
	listNode<dataType> *temp;
	if (this->maxSize == 0)
		return;
	temp = this->head->next_node_point;
	delete this->head;
	for (; temp->next_node_point != NULL;)
	{
		delete temp;
		temp = temp->next_node_point;
	}
}

template<class dataType>
bool myList<dataType>::Push(dataType  item) {
	listNode<dataType> * temp = this->head;
	this->head = new listNode<dataType>;
	this->head->node_data = new dataType(item);
	this->head->next_node_point = temp;
	this->top++;
	return true;
}

template<class dataType>
bool myList<dataType>::Pop() {
	listNode<dataType> * temp;
	if (this->Empty())
	{
		cout << "Stack is Empty. Pop ERR" << endl;
		return false;
	}
	else
	{
		temp = this->head->next_node_point;
		delete this->head;
		this->head = temp;
		top--;
		return true;
	}
}

template<class dataType>
bool myList<dataType>::Top(dataType& item) {
	if (this->Empty())
	{
		cout << "No Elements.";
		return false;
	}
	else
	{
		item = *((this->head)->node_data);
		return true;
	}
}

template<class dataType>
ostream & operator<<(ostream &out, myList<dataType> &item)
{
	listNode<dataType> *temp; int i = 0;
	if (item.Empty())
	{
		cout << "Stack is Empty. Output ERR" << endl;
		return out;
	}
	else
	{
		for (temp = item.head; i <= item.top; i++)
		{
			cout << *temp;
			temp = temp->next_node_point;
		}
		cout << endl;
	}
	return out;
}

template<class dataType>
dataType& myList<dataType>:: operator [] (int sum) {
	listNode<dataType> *temp;
	int num = 0;
	for (; temp->next_node_point != NULL; num ++)
	{
		if (num == sum)
			break;
		temp = temp->next_node_point
	}
	return *(temp->node_data);
}
#pragma once
