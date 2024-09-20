#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
struct Node {
  T value;
  Node<T>* next;
  Node<T>* prev;

  Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr) : value(value), next(next), prev(prev) {}
};

template <typename T>
class LinkedList : public List<T> {
public:
	LinkedList();
	~LinkedList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();
  Node<T>* getNode(size_t idx); // helper function

private:
  Node<T>* head;
  Node<T>* tail;
  size_t m_size;

	Node<T>* data;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), m_size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
      Node<T>* nextNode = current->next;
      delete current;
      current = nextNode;
    }
}

template <typename T>
void LinkedList<T>::append(T v) {
  Node<T>* newNode = new Node<T>(v);
  if (m_size == 0) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
  ++m_size;
}

template <typename T>
void LinkedList<T>::insert(size_t idx, T v) {
  if (idx > m_size) {
    throw std::out_of_range("Idx is out of bounds!");
  }
  if (idx == m_size) {
    append(v);
    return;
  }
  Node<T>* current = getNode(idx);
  Node<T>* newNode = new Node<T>(v, current, current->prev);
  if (current->prev) {
    current->prev->next = newNode;
  } else {
    head = newNode;
  }
  current->prev = newNode;
  ++m_size;
}

template <typename T>
T LinkedList<T>::at(size_t idx) {
  if (idx >= m_size) {
    throw std::out_of_range("Idx out of bounds!");
  }
  return getNode(idx)->value;
}

template <typename T>
void LinkedList<T>::remove(size_t idx) {
  if (idx >= m_size) {
    throw std::out_of_range("Idx out of bounds!");
  }
  Node<T>* nodeToRemove = getNode(idx);
  if (nodeToRemove->prev) {
    nodeToRemove->prev->next = nodeToRemove->next;
  } else {
    head = nodeToRemove->next;
  }
  if (nodeToRemove->next) {
    nodeToRemove->next->prev = nodeToRemove->prev;
  } else {
    tail = nodeToRemove->prev;
  }
  delete nodeToRemove;
  --m_size;
}

template <typename T>
size_t LinkedList<T>::find(T v) {
  Node<T>* current = head;
  size_t index = 0;
  while (current) {
    if (current->value == v) {
      return index;
    }
    current = current->next;
    ++index;
  }
  return -1;
}

template <typename T>
size_t LinkedList<T>::size()
{
  return m_size;
}

template <typename T>
bool LinkedList<T>::empty() {
  return m_size == 0;
}

template <typename T>
Node<T>* LinkedList<T>::getNode(size_t idx) {
  Node<T>* current = head;
  for (size_t i = 0; i < idx; ++i) {
    current = current->next;
  }
  return current;
}

#endif
