/*
 * Created by Miguel Canton Cortes, 2014
 */

#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include <iostream>

template <class T>
class MinHeap {
	private:
		T** nodes;
		unsigned lastNode;
		unsigned capacity;
		void resize();
		
	public:
		MinHeap(unsigned _capacity = 10);
		~MinHeap();
		bool isEmpty();
		unsigned size();
		void insert(const T& val);
		const T& top();
		void pop();
};

template <class T>
MinHeap<T>::MinHeap(unsigned _capacity) {
	capacity = _capacity;
	if(capacity < 2)
		capacity = 2;
	nodes = new T*[capacity];
	
	lastNode = 1;
}

template <class T>
MinHeap<T>::~MinHeap() {
	if(!nodes) return;
	
	for(unsigned i = 0; i < lastNode; i++)
		delete nodes[i];
	delete [] nodes;
}

template <class T>
void MinHeap<T>::resize() {
	capacity *= 2;
	T** newNodes = new T*[capacity];
	
	for(unsigned i = 0; i < lastNode; i++)
		newNodes[i] = nodes[i];
	
	delete [] nodes;
	nodes = newNodes;
}

template <class T>
bool MinHeap<T>::isEmpty() {
	return lastNode == 1;
}

template <class T>
unsigned MinHeap<T>::size() {
	return lastNode-1;
}

template <class T>
void MinHeap<T>::insert(const T& val) {
	if(lastNode == capacity)
		resize();
	
	unsigned insertPos = lastNode;
	
	while(insertPos > 1 && *(nodes[insertPos/2]) > val) {
		nodes[insertPos] = nodes[insertPos/2];
		insertPos /= 2;
	}
	
	nodes[insertPos] = new T(val);
	
	lastNode++;
}

template <class T>
const T& MinHeap<T>::top() {
	return *(nodes[1]);
}

template <class T>
void MinHeap<T>::pop() {
	if(isEmpty()) return;
	
	if(nodes[1])
		delete nodes[1];
	
	lastNode--;
	T* last = nodes[lastNode];
	
	unsigned curr = 1;
	unsigned child = 2;
	while(child < lastNode) {
		if(child < lastNode-1 && *(nodes[child]) > *(nodes[child+1])) //which child is the smallest?
			child++;
		
		if(*last < *(nodes[child])) break; ////Det.
		
		nodes[curr] = nodes[child];
		curr = child;
		child *= 2;
	}
	
	nodes[curr] = last;
}



#endif