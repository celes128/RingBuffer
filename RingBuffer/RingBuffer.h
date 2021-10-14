#pragma once

#include <cassert>

template <class T, size_t CAPACITY>
class RingBuffer {
public:
	RingBuffer()
		: m_head(0)
		, m_tail(0)
		, m_size(0)
	{}

	// Returns the current number of elements.
	size_t Size() const { return m_size; }

	// Returns the maximum number of elements that the buffer can contain.
	size_t Capacity() const { return CAPACITY; }

	int Empty() const { return m_size == 0; }
	int Full() const { return m_size >= CAPACITY; }

	// PRECONDITIONS
	//	* !Full()
	// Push does not overwrite items if the buffer is full.
	// If one call Push on a full buffer the behaviour is undefined.
	void Push(const T &x)
	{
		assert(!Full());

		m_buffer[m_tail] = x;
		advance(m_tail);
		++m_size;
	}

	// PRECONDITIONS
	//	* !Empty()
	void Pop()
	{
		assert(!Empty());

		advance(m_head);
		--m_size;
	}

	// PRECONDITIONS
	//	* !Empty()
	T Front() const
	{
		assert(!Empty());

		return m_buffer[m_head];
	}

private:
	void advance(size_t &i)
	{
		i = (i + 1) % CAPACITY;
	}

private:
	T		m_buffer[CAPACITY];
	size_t	m_head;
	size_t	m_tail;
	size_t	m_size;
};