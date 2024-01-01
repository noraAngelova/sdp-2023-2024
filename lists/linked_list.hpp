#ifndef _LINKED_LIST_HPP
#define _LINKED_LIST_HPP

/*	Представяне на елемент на свързан списък с една връзка
	 ___________
	|ст/ст| адр |
	|_____|_____|
	 data   next
*/
template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement<T>* next;
};

// Декларация на клас LinkedList
template <typename T>
class LinkedList;

// Дефиниране на клас Итератор
template <typename T>
class LinkedListIterator {
	// Съкратени записи за шаблон на елемент от свързан списък и итератор
	using LLE = LinkedListElement<T>;
	using I = LinkedListIterator<T>;

	// Осигурява достъп до вътрешното представяне на списъка
	friend LinkedList<T>;

	// Реализира абстракция на позиция чрез ptr към елемент
	LLE* ptr;
public:
	// Подразбиращ се конструктор и конструктор с един параметър
	LinkedListIterator(LLE* pos = nullptr) : ptr(pos) {}

	// Метод за взимане на итератор към следващ елемент
	I next() const {
		// Проверка за валидност на текущия итератор
		if (!valid()) {
			// Запазва и връща текущия итератор
			return *this;
		}
		// Създава нов обект итератор, който се свързва със следващия елемент на списъка
		return I(ptr->next);
	}

	// Проверка за валидност (обхваща и случая с достигането на края на свързания списък)
	bool valid() const {
		return ptr != nullptr;
	}

	// Методи за извличане на стойността на елемента свързан с итератора
	T const& getConst() const {
		return ptr->data;
	}

	T& get() const {
		return ptr->data;
	}

	// Синтактична захар
	// it <=> it.valid();
	operator bool() const {
		return valid();
	}

	// ++it
	I& operator++() {
		return (*this = next());
	}

	// it++
	I operator++(int) {
		I saved = *this;
		++(*this);
		return saved;
	}

	// *it = 3;
	T& operator*() {
		return get();
	}

	// T data = *it;
	T const& operator*() const {
		return getConst();
	}
	// Сравнение на итератори
	// it1 == it2
	bool operator==(I const& it) const {
		return ptr == it.ptr;
	}

	// it1 != it2
	bool operator!=(I const& it) const {
		return !(*this == it);
	}

	// Преместване с n позиции
	// it += n
	I& operator+=(unsigned n) {
		for (int i = 0; i < n; ++i) {
			++(*this);
		}

		return *this;
	}
};

// Дефиниране на клас Свързан списък
template <typename T>
class LinkedList {
public:
	// Ще използваме I като тип за LinkedListIterator<T>
	using I = LinkedListIterator<T>;
	using Type = T;

private:
	using LLE = LinkedListElement<T>;

	// Представяне на свързан списък с два указателя
	LLE* front, * back;

	// Помощна член-функция за изтриване на динамично заделената памет
	void erase();

	// Допълнителен метод за намиране на предходен елемент
	I findPrev(I const& it);

public:
	// Подразбиращ се конструктор, който създава празен списък
	LinkedList() : front(nullptr), back(nullptr) {}

	// Конструктор за копиране и оператор за присвояване за свързан списък
	LinkedList(LinkedList<T> const& ll);
	LinkedList<T>& operator=(LinkedList<T> const& ll);

	// Деструктор
	~LinkedList() {
		erase();
	}

	// Move конструктор и оператор за присвояване
	LinkedList(LinkedList<T>&& ll) {
		front = ll.front;
		back = ll.back;
		ll.front = ll.back = nullptr;
	}

	LinkedList<T>& operator=(LinkedList<T>&& ll) {
		if (this != &ll) {
			erase();
			front = ll.front;
			back = ll.back;
			ll.front = ll.back = nullptr;
		}

		return *this;
	}


	// Методи за взимане на позиции в свързания списък
	// Метод за начало на свързан списък
	I begin() const {
		return I(front);
	}

	// Метод връщащ края на свързан списък
	I end() const {
		// Създава итератор от nullptr, 
		// което позволява използване на цикли до края на списъка - до невалидна позиция
		// Реализацията е сходна с stl-ската
		return I();
	}

	I last() const {
		return I(back);
	}

	// Метод, който проверява дали списъкът е празен
	bool empty() const {
		return front == nullptr && back == nullptr;
	}

	// Методи за извличане на стойност на елемент
	T const& getAt(I const& it) const;
	T& getAt(I const& it);

	// Основни методи за добавяне на елемент
	bool insertBefore(I const& it, T const& x);
	bool insertAfter(I const& it, T const& x);

	// Основни методи за изтриване на елемент
	bool deleteBefore(I const& it);
	bool deleteAfter(I const& it);
	bool deleteAt(I& it);

	// Допълнителни методи за добавяне и изтриване на елементи
	// O(1) по време и памет
	bool insertFirst(T const& x) {
		return insertBefore(begin(), x);
	}
	bool insertLast(T const& x) {
		return insertAfter(last(), x);
	}

	// O(1) по време и по памет
	bool deleteFirst() {
		I beg = begin();
		return deleteAt(beg);
	}

	bool deleteLast() {
		I it = end();
		return deleteAt(it);
	}

	// Методи за конкатенация на елементи от списъка подаден като параметър
	void append(LinkedList<T> const& ll);
	void appendAssign(LinkedList<T>& ll);

	// Синтактична захар
	// Добавяне на елемент чрез оператора +=
	LinkedList<T>& operator+=(T const& x) {
		insertLast(x);
		return *this;
	}

	void print() const {
		for (T x : *this)
			std::cout << x << " ";
	}
};

template <typename T>
void LinkedList<T>::append(LinkedList const& l) {
	for (T const& x : l)
		insertLast(x);
}

// Методът използва паметта за елементите на списъка l и го променя
template <typename T>
void LinkedList<T>::appendAssign(LinkedList& l) {
	// Проверява дали списъкът е празен
	if (back != nullptr)
		back->next = l.front;
	else
		front = l.front;

	// Проверка дали подадения като параметър списък е празен
	if (l.back != nullptr)
		back = l.back;

	// Занулява указателите, за да избегне поделянето на памет
	l.front = l.back = nullptr;
}

// Метод за изтриване на динамично заделената памет
template <typename T>
void LinkedList<T>::erase() {
	while (!empty())
		deleteFirst();
}

// O(n) по време и O(1) по памет
template <typename T>
LinkedListIterator<T> LinkedList<T>::findPrev(LinkedListIterator<T> const& it) {
	I result = begin();
	while (result && result.next() != it)
		++result;

	// !result || result.next() == it
	return result;
}

// Конструктор за копиране
template <typename T>
LinkedList<T>::LinkedList(LinkedList const& l) : front(nullptr), back(nullptr) {
	// Използва се функцията append
	// Функцията вмъква елементи със същите стойности от списъка l в списъка *this
	append(l);
}

// Оператор за присвояване
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList const& l) {
	if (this != &l) {
		erase();
		append(l);
	}
	return *this;
}


// O(1) по време и памет
template <typename T>
bool LinkedList<T>::insertAfter(I const& it, T const& x) {
	if (empty()) {
		front = back = new LLE{ x, nullptr };
		return true;
	}

	it.ptr->next = new LLE{ x, it.ptr->next };

	// Добавя се елемент в края
	if (it.ptr == back) {
		back = back->next;
	}

	return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::insertBefore(I const& it, T const& x) {
	if (it == begin()) {
		// Вмъкваме в началото: специален случай
		LLE* newElem = new LLE{ x, front };
		front = newElem;
		// Проверка дали списъкът е празен
		if (back == nullptr)
			// вмъкваме в празен списък
			back = newElem;
		return true;
	}
	return insertAfter(findPrev(it), x);
}

// O(1) по време и по памет
template <typename T>
bool LinkedList<T>::deleteAfter(I const& it) {
	if (!it) {
		// Не може да се изтрива след невалиден итератор(позиция)
		return false;
	}

	LLE* deletedElem = it.ptr->next;

	if (!deletedElem) {
		// Не може да се изтрива след края
		return false;
	}

	it.ptr->next = deletedElem->next;

	if (back == deletedElem) {
		// Изтрива се последният елемент
		back = it.ptr;
	}

	delete deletedElem;
	return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::deleteAt(I& it) {
	if (empty()) {
		return false;
	}

	if (it == begin()) {
		LLE* deletedElem = front;
		front = front->next;
		if (back == deletedElem) {
			// Изтрива се последният елемент от списъка
			back = nullptr;
		}
		delete deletedElem;

		// Зануляване на указателя в итератора за следваща употреба
		it.ptr = nullptr;
		return true;
	}
	I prev = findPrev(it);
	it.ptr = nullptr;

	return deleteAfter(prev);
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::deleteBefore(I const& it) {
	if (it == begin()) {
		return false;
	}

	// Използване на допълнителен итератой, който може да бъде занулен
	I prev = findPrev(it);

	return deleteAt(prev);
}

#endif
