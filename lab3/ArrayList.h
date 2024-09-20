#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
public:
	ArrayList();
	~ArrayList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();

private:
	void resize(); //double the size of the array and copy the items
	size_t m_capacity;
	size_t m_size;
	T* data;
};

template <typename T>
ArrayList<T>::ArrayList()
{
	m_capacity = 8;
	m_size = 0;
	data = new T[m_capacity];
}

template <typename T>
ArrayList<T>::~ArrayList()
{
	delete[] data;
}

template <typename T>
void ArrayList<T>::resize()
{
	m_capacity *= 2;
	T* new_data = new T[m_capacity];

	for (size_t i = 0; i < m_size; ++i) 
	{
		new_data[i] = data[i];
	}

	delete[] data;
	data = new_data;
}

template <typename T>
void ArrayList<T>::append(T v)
{
	if (m_size == m_capacity) 
	{
		resize();
	}

	data[m_size] = v;
	++m_size;
}

template <typename T>
void ArrayList<T>::insert(size_t idx, T v)
{
	if (idx > m_size)
	{
		throw std::range_error("Idx out of bounds!");
	}
	if (m_size == m_capacity)
	{
		resize();
	}

	for (size_t i = m_size; i > idx; --i)
	{
		data[i] = data[i - 1];
	}
	data[idx] = v;
	++m_size;
}

template <typename T>
T ArrayList<T>::at(size_t idx)
{
	if (idx >= m_size)
	{
		throw std::range_error("Idx out of bounds!");
	}
	return data[idx];
}

template <typename T>
void ArrayList<T>::remove(size_t idx)
{
	if (idx >= m_size)
	{
		throw std::range_error("Idx out of bounds!");
	}

	for (size_t i = idx; i < m_size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--m_size;
}

template <typename T>
size_t ArrayList<T>::find(T v)
{
	for (size_t i = 0; i < m_size; ++i)
	{
		if (data[i] == v)
		{
			return i;
		}
	}

	return static_cast<size_t>(-1);
}

template <typename T>
size_t ArrayList<T>::size()
{
	return m_size;
}

template <typename T>
bool ArrayList<T>::empty()
{
	if (m_size == 0) 
	{
		return true;
	} 
	else 
	{
		return false;
	}
}

#endif
