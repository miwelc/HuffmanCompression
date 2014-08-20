/*
 * Created by Miguel Canton Cortes, 2014
 */

#ifndef _LIST_HPP_
#define _LIST_HPP_

template <class T>
class List {
	private:
		struct Node {
			T data;
			Node* prev;
			Node* next;
		};
		Node firstNode;
		Node lastNode;
		unsigned size;
	
	public:
		unsigned Size() { return size; }
		List();
		List(const List<T>& B);
		~List();
		class iterator {
			private:
				friend class List<T>;
				Node* node;
			public:
				iterator(Node* ptr) : node(ptr) {}
				void operator--(int) { if(node->prev) node = node->prev; }
				void operator++(int) { if(node->next) node = node->next; }
				T& operator*() { return node->data; }
				bool operator==(const iterator& it) { return node == it.node; }
				bool operator!=(const iterator& it) { return node != it.node; }
		};
		class const_iterator {
			private:
				friend class List<T>;
				const Node* node;
			public:
				const_iterator(const Node* ptr) : node(ptr) {}
				const_iterator(const iterator& it) : node(it.node) {}
				void operator--(int) { if(node->prev) node = node->prev; }
				void operator++(int) { if(node->next) node = node->next; }
				const T& operator*() { return node->data; }
				bool operator==(const const_iterator& it) { return node == it.node; }
				bool operator!=(const const_iterator& it) { return node != it.node; }
		};
		void operator=(const List<T>& B);
		iterator remove(iterator it);
		iterator removeLast();
		void clear();
		void insert(const T& data);
		void insert(const iterator it, const T& data);
		void sortedUnion(List<T>& listB);
	
		iterator begin() { return firstNode.next; }
		const_iterator begin() const { return firstNode.next; }
		iterator last() { if(lastNode.prev != &firstNode) return lastNode.prev; else return end(); }
		iterator end() { return &lastNode; }
		const_iterator end() const { return &lastNode; }
};

template <class T>
List<T>::List() {
	firstNode.prev = 0;
	firstNode.next = &lastNode;
	lastNode.prev = &firstNode;
	lastNode.next = 0;
	size = 0;
}


template <class T>
List<T>::List(const List<T>& B) {
	firstNode.prev = 0;
	firstNode.next = &lastNode;
	lastNode.prev = &firstNode;
	lastNode.next = 0;
	size = 0;
	
	*this = B;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
void List<T>::operator=(const List<T>& B) {
	for(List<T>::const_iterator it = B.begin(); it != B.end(); it++) {
		insert(*it);
	}
}

template <class T>
typename List<T>::iterator List<T>::remove(List<T>::iterator it) {
	if(it == end() || it == &firstNode) return end();
	
	iterator nextIt = it.node->next;
	
	it.node->prev->next = nextIt.node;
	nextIt.node->prev = it.node->prev;
	
	delete &*it;
	size--;
	
	return nextIt;
}

template <class T>
typename List<T>::iterator List<T>::removeLast() {
	return remove(end()->prev);
}

template <class T>
void List<T>::clear() {
	for(List<T>::iterator it = begin();
		it != end();
		it = remove(it))
		;
	size = 0;
}

template <class T>
void List<T>::insert(const T& data) {
	insert(end(), data);
}

template <class T>
void List<T>::insert(List<T>::iterator it, const T& data)  {
	Node* prevNode = it.node->prev;
	Node* nextNode = it.node;
	Node* newNode = new Node;
	
	newNode->data = data;
	newNode->next = nextNode;
	newNode->prev = prevNode;
	
	prevNode->next = newNode;
	nextNode->prev = newNode;
	
	size++;
}

template <class T>
void List<T>::sortedUnion(List<T>& listB) {
	for(List<T>::iterator itA = begin(), itB = listB.begin(); itB != listB.end();) {
		if(itA == end() || *itA > *itB) {
			insert(itA, *itB);
			itB++;
		}
		else {
			itA++;
		}
	}
}

#endif






