#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>

template<typename T>
class Vector
{
public:
	/**
	* Конструктор по подразбиране.
	* Създава празен вектор с капацитет 0 и брой елементи 0.
	*/
	Vector();

	/**
	* Конструктор за запълване.
	* Създава вектор с капацитет count и брой елементи count.
	* @param count - размер на векторът
	*/
	Vector(size_t count);

	/**
	* Конструктор за запълване.
	* Създава вектор с капацитет cout и брой елементи cout.
	* @param cout - размер на векторът
	* @param value - стойност с която да се запълни векторът
	*/
	Vector(size_t count, const T& value);

	/**
	* Конструктор за копиране.
	* Създава вектор, който съдържа копие на всеки от елементите на other.
	* @param other - вектор
	*/
	Vector(const Vector& other);

	/**
	* Оператор за присвояващо копиране.
	* Копира данните от векторът other.
	* @param other - вектор
	*/
	Vector& operator=(const Vector& other);

	/**
	* Връща референция към елемента на позиция index
	* @param index - позиция на елемента който ще се върне
	* @return референция към изискания елемент
	*/
	T& operator[](size_t index)
	{
		return data[index];
	}

	/**
	* Връща капацитетът на векторът
	* @return капацитет на векторът
	*/
	size_t capacity() const
	{
		return capacity_;
	}

	/**
	* Връща размерът на векторът
	* @return размер на векторът
	*/
	size_t size() const
	{
		return size_;
	}

	/**
	* Заделя памет с посочения капацитет new_capacity.
	* Ако новия капацитет е по-голям от текущия капацитет, тогава се заделя нова памет. В противен
	* случай не се прави нищо.
	* @param new_capacity нов капацитет
	* @return
	*/
	void reserve(size_t newCapacity);

	/**
	* Преоразмерява векторът, така, че да съдържа new_size елемента
	* @param new_size нов нов брой елементи
	* @return
	*/
	void resize(size_t newSize);

	/**
	* Връша елемента в края на вектора
	* @return адреса на последния елемент в вектора
	*/
	T& back();

	/**
	* Връша елемента в началото на вектора
	* @return адреса на първия елемент в вектора
	*/
	T& front();

	/**
	*Свива вектора до с капацитет = размер
	* @return
	*/
	void shrink_to_fit();

	/**
	* Разменя два вектора
	* @return
	*/
	void swap(Vector<T> &other);

	/**
	* Вмъква елемент на мястото на index
	* @param index - мястото на вмъкната стойност
	* @param value - вмъкнатия елемент
	* @return
	*/
	void insert(size_t index, const T& value);


	/**
	* Изтрива елемент от вектора на мястото index
	* @param index - мястото във вектора на изтритата стойност
	* @return
	*/
	void erase(size_t index);


	/**
	* Извежда елементите на вектора на екрана
	* @return
	*/
	void print() const;

	/**
	* Добавя елемент в края на векторът - след текущия последен елемент
	* @param value - стойност, която да бъде добавена
	* @return
	*/
	void push_back(const T& value);

	/**
	* Премахва последния елемент на векторът
	* @return
	*/
	void pop_back();

	/*
	* Проверява дали векторът е празен
	* @return true or false
	*/
	bool empty();

	/*
	* Изтрива съдържанието на вектора
	* @return
	*/
	void clear();

	/**
	* Деструктор.
	* Освобождава заделената памет.
	*/
	~Vector();

private:
	size_t capacity_;
	size_t size_;
	T* data;

	/**
	* Заделя памет за типът T с капацитет capacity
	* capacity - размер на заделената памет
	* @return указател към заделената памет
	*/
	static T* allocateMemory(size_t capacityAlloc)
	{
		return static_cast<T*> (operator new(sizeof(T)* capacityAlloc)); 
	} 

	/**
	* Копира елементите от посочения обхват (опеределн от begin и end) в destination.
	* @param begin - указател към началото на източника
	* @param end - указател към края на източника
	* @param destination - указател към мястото, където ще се извърши копирането
	* @return
	*/
	static void copyRange(T* begin, T* end, T* destination)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//Използваме placement new за инициализация с конструктор за копиране
				new((void*)destination) T(*current);
				++destination;
			}
		}
		catch (...)
		{
			//Извиква деструкторите
			deleteRange(begin, current);
			throw;
		}
	}

	/**
	* Конструира с конструктор по подразбиране обектите върху паметта, определена от обхвата begin и end
	* @param begin - указател към началото
	* @param end - указател към края
	* @return
	*/
	static void constructRange(T* begin, T* end)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//Използваме placement new за инициализация с подразбиращ се конструктор
				new((void*)current) T();
			}
		}
		catch (...)
		{
			//Извиква деструкторите
			deleteRange(begin, current);
			throw;
		}

	}

	/**
	* Конструира с конструктор, приемащ стойност fill_value ,oбектите върху паметта, определена от обхвата begin и end
	* @param begin - указател към началото
	* @param end - указател към края
	* @return
	*/
	static void constructRange(T* begin, T* end, const T& fillValue)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//Използваме placement new за инициализация с конструктор за запълване
				new((void*)current) T(fillValue);
			}
		}
		catch (...)
		{
			//Извиква деструкторите
			deleteRange(begin, current);
			throw;
		}
	}

	/**
	* Извиква деструкторите на обектите върху паметта, определна от обхвата begin и end
	* @param begin - указател към началото
	* @param end - указател към края
	*/
	static void deleteRange(T* begin, T* end)
	{
		while (begin != end)
		{
			begin->~T();
			++begin;
		}
	}
};

template<typename T>
Vector<T>::Vector() : capacity_(0), size_(0), data(nullptr)
{

}

template<typename T>
Vector<T>::Vector(size_t count) : capacity_(count), size_(count), data(allocateMemory(count))
{
	try
	{
		constructRange(data, data + size_);
	}
	catch (...)
	{
		//Освобождава паметта
		operator delete(data);
		throw;
	}
}

template<typename T>
Vector<T>::Vector(size_t count, const T& value) : capacity_(count), size_(count), data(allocateMemory(count))
{
	try
	{
		constructRange(data, data + size_, value);
	}
	catch (...)
	{
		//Освобождава паметта
		operator delete(data);
		throw;
	}
}

template<typename T>
Vector<T>::Vector(const Vector& other) : capacity_(other.capacity_), size_(other.size_), data(allocateMemory(other.capacity_))
{
	try
	{
		copyRange(other.data, other.data + other.size_, data);
	}
	catch (...)
	{
		//Освобождава паметта
		operator delete(data);
		throw;
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> & other)
{
	if (this == &other)
	{
		return *this;
	}

	//Извиква деструкторите на текущите елементи
	deleteRange(data, data + size_);
	//Освобождава текущо заделената памет
	operator delete(data);
	capacity_ = other.capacity_;
	size_ = other.size_;
	try
	{
		data = allocateMemory(capacity_);
		try
		{
			//Извършва копиране на елементите
			copyRange(other.data, other.data + other.size_, data);
		}
		catch (...)
		{
			//Освобождава паметта
			operator delete(data);
			throw;
		}
	}
	catch (...)
	{
		Vector<T>();
		throw;
	}

	return *this;
}

template<typename T>
void Vector<T>::reserve(size_t newCapacity)
{
if (newCapacity > capacity_)
{
//Заделяме памет за новия капацитет
T* newData = allocateMemory(newCapacity);
try
{
//Копираме старите стойности
copyRange(data, data + size_, newData);
}
catch (...)
{
//Освобождава паметта
operator delete(newData);
throw;
}
//Извикваме деструкторите на старите обекти
deleteRange(data, data + size_);
//освобождаваме паметта, която се използва за старите обекти
operator delete(data);
data = newData;
capacity_ = newCapacity;
}
}

template<typename T>
void Vector<T>::resize(size_t newSize)
{
	if (newSize <= size)
	{
		deleteRange(data + newSize, data + size_);
		size = newSize;
		return;
	}

	if (newSize <= capacity)
	{
		constructRange(data + size_, data + newSize);
		size = newSize;
		return;
	}

	size_t newCapacity = newSize;
	size_t defaultGrowth = (size_t)round(size_ * 1.5);
	if (newCapacity < defaultGrowth)
	{
		newCapacity = defaultGrowth;
	}
	//Заделяме памет за новия капацитет
	T* newData = allocateMemory(newCapacity);
	try
	{
		//Копираме старите стойности
		copyRange(data, data + size_, newData);
	}
	catch (...)
	{
		//Освобождава паметта
		operator delete(newData);
		throw;
	}
	//Извикваме деструкторите на старите обекти
	deleteRange(data, data + size_);
	//освобождаваме паметта, която се използва за старите обекти
	operator delete(data);
	data = newData;
	capacity_ = newCapacity;
	constructRange(data + size_, data + newSize);
	size = newSize;
}

template<typename T>
void Vector<T>::push_back(const T& value)
{
	if (size_ != capacity_)
	{
		//Използваме placement new за инициализация с конструктор за копиране
		new((void*)(data + size_)) T(value);
		++size_;
		return;
	}

	//Задаваме нов капацитет, като се използва следната стратегия за растеж:
	size_t newCapacity;
	if (capacity_)
	{
		newCapacity = (size_t)ceil(capacity_ * 1.5);
	}
	else newCapacity = 1;


	//Заделяме памет за новия капацитет
	T* newData = allocateMemory(newCapacity);
	try
	{
		//Копираме старите стойности
		copyRange(data, data + size_, newData);
	}
	catch (...)
	{
		//Освобождава паметта
		operator delete(newData);
		throw;
	}
	//Използваме placement new за инициализация с конструктор за копиране
	new((void*)(newData + size_)) T(value);
	//Извикваме деструкторите на старите обекти
	deleteRange(data, data + size_);
	//освобождаваме паметта, която се използва за старите обекти
	operator delete(data); //data = nullptr
	data = newData;
	capacity_ = newCapacity;
	++size_;
}

template<typename T>
T& Vector<T>::back()
{
	if (data != nullptr)
	{
		return *(data + size_ - 1);
	}
}

template<typename T>
T& Vector<T>::front()
{
	if (data != nullptr)
	{
		return *data;
	}
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	if (size_ < capacity_)
	{
		if (empty())
		{
			deleteRange(data, data + size_);
			operator delete(data); //data = nullptr
			capacity_ = 0;

		}
		else
		{
			data = allocateMemory(size_);
			capacity_ = size_;
		}
	}
}

template<typename T>
void Vector<T>::insert(size_t index, const T& value)
{
	if (index <= size_ && index > 0)
	{
		// заделяме памет с размер capacity_ 
		T* newDataBegin = allocateMemory(capacity_);
		T* newDataEnd = allocateMemory(capacity_);
		try
		{
			//копираме старите стойности от data[0] до data[index-1] в единия указател
			copyRange(data, data + index - 1, newDataBegin);
			//копираме старите стойности от data[index-1] до data[size-1] в единия указател
			copyRange(data + index - 1, data + size_, newDataEnd);

			++capacity_;
			//заделяме си нова памет за вектора
			data = allocateMemory(capacity_);
			// на дата[index - 1 ]  слагаме стойност value
			new((void*)(data + index - 1)) T(value);

			//поставяме си стойностите на старото им място 
			copyRange(newDataBegin, newDataBegin + index - 1, data);
			copyRange(newDataEnd, newDataEnd + size_ - (index - 1), data + index);
			++size_;

		}
		catch (...)
		{
			
			operator delete(newDataBegin);
			operator delete(newDataEnd);
			throw;
		}

		operator delete(newDataBegin);
		operator delete(newDataEnd);
	}
}

template<typename T>
void Vector<T>::erase(size_t index)
{
	if (index <= size_ && index > 0)
	{
		try
		{
			copyRange(data, data + index - 1, data);
			copyRange(data + index, data + size_, data + index - 1);
			--size_;
			--capacity_;
		}
		catch (...)
		{
			operator delete(data);
			throw;
		}
	}

}

template<typename T>
void Vector<T>::swap(Vector<T> &other)
{
	if (this == &other)
	{
		return;
	}


	T* thirdWheel = allocateMemory(capacity_);
	size_t changeSize;
	size_t changeCapacity;

	try
	{
		copyRange(data, data + size_, thirdWheel);
		copyRange(other.data, other.data + size_, data);
		copyRange(thirdWheel, thirdWheel + size_, other.data);

	
		changeCapacity = capacity_;
		capacity_ = other.capacity_;
		other.capacity_ = changeCapacity;

		changeSize = size_;
		size_ = other.size_;
		other.size_ = changeSize;

	}
	catch (...)
	{
		deleteRange(thirdWheel, thirdWheel + size_);
		operator delete(thirdWheel);
		throw;
	}
	deleteRange(thirdWheel, thirdWheel + size_);
	operator delete(thirdWheel);
}

template<typename T>
void Vector<T>::print() const
{
	int i = 0;
	while (i < size_)
	{
		
		cout << *(data + i) << " ";
		i++;
	}
}

template<typename T>
bool Vector<T>::empty()
{
	
	if (data == data + size_ - 1)
	{
		return true;
	}
	else return false;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (empty())
	{
		return;
	}
	else
	{
		deleteRange(data + size_ - 1, data + size_);
		--size_;
		if (empty())
		{
			capacity_ = 0;
			size_ = 0;
			data = nullptr;
		}
	}
}

template<typename T>
void Vector<T>::clear()
{
	//Извиква деструкторите
	deleteRange(data, data + size_);
	operator delete(data);
	size_ = 0;
	capacity_ = 0;
	data = nullptr;
}


template<typename T>
Vector<T>::~Vector()
{
	//Извиква деструкторите
	deleteRange(data, data + size_);
	//Освобождава паметта
	delete(data);
}

#endif
