#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include <stdexcept>
#include <iostream>
#include <ctime>
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
	void debugPanel(const std::string& operation, clock_t start, clock_t end);
};

template <typename T>
ArrayList<T>::ArrayList()
{
	m_capacity = 2;
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
	clock_t start = clock();
	m_capacity *= 2;
	T* new_data = new T[m_capacity];

	for (size_t i = 0; i < m_size; ++i) 
	{
		new_data[i] = data[i];
	}

	delete[] data;
	data = new_data;

	clock_t end = clock();
	debugPanel("resize", start, end);
}

template <typename T>
void ArrayList<T>::append(T v)
{
	clock_t start = clock();
	if (m_size == m_capacity) 
	{
		resize();
	}

	data[m_size] = v;
	++m_size;
	clock_t end = clock();
	debugPanel("append", start, end);
}

template <typename T>
void ArrayList<T>::insert(size_t idx, T v)
{
	clock_t start = clock();
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
	clock_t end = clock();
	debugPanel("insert", start, end);
}

template <typename T>
T ArrayList<T>::at(size_t idx)
{
	clock_t start = clock();
	if (idx >= m_size)
	{
		throw std::range_error("Idx out of bounds!");
	}
	T result = data[idx];
	clock_t end = clock();
	debugPanel("at", start, end);
	return result;
}

template <typename T>
void ArrayList<T>::remove(size_t idx)
{
	clock_t start = clock();
	if (idx >= m_size)
	{
		throw std::range_error("Idx out of bounds!");
	}

	for (size_t i = idx; i < m_size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--m_size;
	clock_t end = clock();
	debugPanel("remove", start, end);
}

template <typename T>
size_t ArrayList<T>::find(T v)
{
	clock_t start = clock();
	for (size_t i = 0; i < m_size; ++i)
	{
		if (data[i] == v)
		{
			clock_t end = clock();
			debugPanel("find", start, end);
			return i;
		}
	}

	clock_t end = clock();
	debugPanel("find", start, end);
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
	return m_size == 0;
}

template <typename T>
void ArrayList<T>::debugPanel(const std::string& operation, clock_t start, clock_t end)
{
	double duration = double(end - start) / CLOCKS_PER_SEC;

	const std::string color_blue = "\033[34m";
	const std::string color_green = "\033[32m";
	const std::string color_reset = "\033[0m";

	std::cout << color_green << "\n\t| Operation: " << operation 
		<< " | Time: " << std::fixed << std::setprecision(6) 
		<< duration << " seconds |" << color_reset << std::endl;
}

#endif