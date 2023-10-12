#ifndef _STATIC_QUEUE_HPP
#define _STATIC_QUEUE_HPP

const int MAX_SIZE = 1024;

template <typename T>
class StaticQueue {
	T elements[MAX_SIZE];
	unsigned front, back, size;  // Индекси и текущ брой на елементите

public:
	StaticQueue();         // Създаване на празна опашка

	bool full() const;
	bool empty() const;    // Проверка дали опашка е празна
	void push(T const& x); // Включване на елемент
	void pop();            // Изключване на елемент
	T head() const;       // Достъп до първия елемент в опашка
};

// Задава индексите на първата празна позиция
template <typename T>
StaticQueue<T>::StaticQueue() : front(0), back(0), size(0) {}

template <typename T>
bool StaticQueue<T>::full() const {
	return size == MAX_SIZE;
}

template <typename T>
bool StaticQueue<T>::empty() const {
	return size == 0;
}

template <typename T>
T StaticQueue<T>::head() const {
	if (empty()) {
		throw std::runtime_error("Can not get elem from an empty queue");
	}
	return elements[front];
}

template <typename T>
void StaticQueue<T>::push(T const& x) {
	if (full()) {
		throw std::runtime_error("The queue is full!");
	}

	elements[back] = x;
	size++;
	back++;
	back = back % MAX_SIZE;
}

template <typename T>
void StaticQueue<T>::pop() {
	if (empty()) {
		throw std::runtime_error("Can not delete element from an empty queue");
	}
	size--;
	front++;
	front = front % MAX_SIZE;
}

#endif
