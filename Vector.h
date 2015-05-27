#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>

template<typename T>
class Vector
{
public:
	/**
	* ����������� �� ������������.
	* ������� ������ ������ � ��������� 0 � ���� �������� 0.
	*/
	Vector();

	/**
	* ����������� �� ���������.
	* ������� ������ � ��������� count � ���� �������� count.
	* @param count - ������ �� ��������
	*/
	Vector(size_t count);

	/**
	* ����������� �� ���������.
	* ������� ������ � ��������� cout � ���� �������� cout.
	* @param cout - ������ �� ��������
	* @param value - �������� � ����� �� �� ������� ��������
	*/
	Vector(size_t count, const T& value);

	/**
	* ����������� �� ��������.
	* ������� ������, ����� ������� ����� �� ����� �� ���������� �� other.
	* @param other - ������
	*/
	Vector(const Vector& other);

	/**
	* �������� �� ����������� ��������.
	* ������ ������� �� �������� other.
	* @param other - ������
	*/
	Vector& operator=(const Vector& other);

	/**
	* ����� ���������� ��� �������� �� ������� index
	* @param index - ������� �� �������� ����� �� �� �����
	* @return ���������� ��� ��������� �������
	*/
	T& operator[](size_t index)
	{
		return data[index];
	}

	/**
	* ����� ����������� �� ��������
	* @return ��������� �� ��������
	*/
	size_t capacity() const
	{
		return capacity_;
	}

	/**
	* ����� �������� �� ��������
	* @return ������ �� ��������
	*/
	size_t size() const
	{
		return size_;
	}

	/**
	* ������ ����� � ��������� ��������� new_capacity.
	* ��� ����� ��������� � ��-����� �� ������� ���������, ������ �� ������ ���� �����. � ��������
	* ������ �� �� ����� ����.
	* @param new_capacity ��� ���������
	* @return
	*/
	void reserve(size_t newCapacity);

	/**
	* ������������� ��������, ����, �� �� ������� new_size ��������
	* @param new_size ��� ��� ���� ��������
	* @return
	*/
	void resize(size_t newSize);

	/**
	* ����� �������� � ���� �� �������
	* @return ������ �� ��������� ������� � �������
	*/
	T& back();

	/**
	* ����� �������� � �������� �� �������
	* @return ������ �� ������ ������� � �������
	*/
	T& front();

	/**
	*����� ������� �� � ��������� = ������
	* @return
	*/
	void shrink_to_fit();

	/**
	* ������� ��� �������
	* @return
	*/
	void swap(Vector<T> &other);

	/**
	* ������ ������� �� ������� �� index
	* @param index - ������� �� �������� ��������
	* @param value - ��������� �������
	* @return
	*/
	void insert(size_t index, const T& value);


	/**
	* ������� ������� �� ������� �� ������� index
	* @param index - ������� ��� ������� �� ��������� ��������
	* @return
	*/
	void erase(size_t index);


	/**
	* ������� ���������� �� ������� �� ������
	* @return
	*/
	void print() const;

	/**
	* ������ ������� � ���� �� �������� - ���� ������� �������� �������
	* @param value - ��������, ����� �� ���� ��������
	* @return
	*/
	void push_back(const T& value);

	/**
	* �������� ��������� ������� �� ��������
	* @return
	*/
	void pop_back();

	/*
	* ��������� ���� �������� � ������
	* @return true or false
	*/
	bool empty();

	/*
	* ������� ������������ �� �������
	* @return
	*/
	void clear();

	/**
	* ����������.
	* ����������� ���������� �����.
	*/
	~Vector();

private:
	size_t capacity_;
	size_t size_;
	T* data;

	/**
	* ������ ����� �� ����� T � ��������� capacity
	* capacity - ������ �� ���������� �����
	* @return �������� ��� ���������� �����
	*/
	static T* allocateMemory(size_t capacityAlloc)
	{
		return static_cast<T*> (operator new(sizeof(T)* capacityAlloc)); 
	} 

	/**
	* ������ ���������� �� ��������� ������ (��������� �� begin � end) � destination.
	* @param begin - �������� ��� �������� �� ���������
	* @param end - �������� ��� ���� �� ���������
	* @param destination - �������� ��� �������, ������ �� �� ������� ����������
	* @return
	*/
	static void copyRange(T* begin, T* end, T* destination)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//���������� placement new �� ������������� � ����������� �� ��������
				new((void*)destination) T(*current);
				++destination;
			}
		}
		catch (...)
		{
			//������� �������������
			deleteRange(begin, current);
			throw;
		}
	}

	/**
	* ���������� � ����������� �� ������������ �������� ����� �������, ���������� �� ������� begin � end
	* @param begin - �������� ��� ��������
	* @param end - �������� ��� ����
	* @return
	*/
	static void constructRange(T* begin, T* end)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//���������� placement new �� ������������� � ����������� �� �����������
				new((void*)current) T();
			}
		}
		catch (...)
		{
			//������� �������������
			deleteRange(begin, current);
			throw;
		}

	}

	/**
	* ���������� � �����������, ������� �������� fill_value ,o������� ����� �������, ���������� �� ������� begin � end
	* @param begin - �������� ��� ��������
	* @param end - �������� ��� ����
	* @return
	*/
	static void constructRange(T* begin, T* end, const T& fillValue)
	{
		T* current;
		try
		{
			for (current = begin; current != end; ++current)
			{
				//���������� placement new �� ������������� � ����������� �� ���������
				new((void*)current) T(fillValue);
			}
		}
		catch (...)
		{
			//������� �������������
			deleteRange(begin, current);
			throw;
		}
	}

	/**
	* ������� ������������� �� �������� ����� �������, ��������� �� ������� begin � end
	* @param begin - �������� ��� ��������
	* @param end - �������� ��� ����
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
		//����������� �������
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
		//����������� �������
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
		//����������� �������
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

	//������� ������������� �� �������� ��������
	deleteRange(data, data + size_);
	//����������� ������ ���������� �����
	operator delete(data);
	capacity_ = other.capacity_;
	size_ = other.size_;
	try
	{
		data = allocateMemory(capacity_);
		try
		{
			//�������� �������� �� ����������
			copyRange(other.data, other.data + other.size_, data);
		}
		catch (...)
		{
			//����������� �������
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
//�������� ����� �� ����� ���������
T* newData = allocateMemory(newCapacity);
try
{
//�������� ������� ���������
copyRange(data, data + size_, newData);
}
catch (...)
{
//����������� �������
operator delete(newData);
throw;
}
//��������� ������������� �� ������� ������
deleteRange(data, data + size_);
//������������� �������, ����� �� �������� �� ������� ������
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
	//�������� ����� �� ����� ���������
	T* newData = allocateMemory(newCapacity);
	try
	{
		//�������� ������� ���������
		copyRange(data, data + size_, newData);
	}
	catch (...)
	{
		//����������� �������
		operator delete(newData);
		throw;
	}
	//��������� ������������� �� ������� ������
	deleteRange(data, data + size_);
	//������������� �������, ����� �� �������� �� ������� ������
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
		//���������� placement new �� ������������� � ����������� �� ��������
		new((void*)(data + size_)) T(value);
		++size_;
		return;
	}

	//�������� ��� ���������, ���� �� �������� �������� ��������� �� ������:
	size_t newCapacity;
	if (capacity_)
	{
		newCapacity = (size_t)ceil(capacity_ * 1.5);
	}
	else newCapacity = 1;


	//�������� ����� �� ����� ���������
	T* newData = allocateMemory(newCapacity);
	try
	{
		//�������� ������� ���������
		copyRange(data, data + size_, newData);
	}
	catch (...)
	{
		//����������� �������
		operator delete(newData);
		throw;
	}
	//���������� placement new �� ������������� � ����������� �� ��������
	new((void*)(newData + size_)) T(value);
	//��������� ������������� �� ������� ������
	deleteRange(data, data + size_);
	//������������� �������, ����� �� �������� �� ������� ������
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
		// �������� ����� � ������ capacity_ 
		T* newDataBegin = allocateMemory(capacity_);
		T* newDataEnd = allocateMemory(capacity_);
		try
		{
			//�������� ������� ��������� �� data[0] �� data[index-1] � ������ ��������
			copyRange(data, data + index - 1, newDataBegin);
			//�������� ������� ��������� �� data[index-1] �� data[size-1] � ������ ��������
			copyRange(data + index - 1, data + size_, newDataEnd);

			++capacity_;
			//�������� �� ���� ����� �� �������
			data = allocateMemory(capacity_);
			// �� ����[index - 1 ]  ������� �������� value
			new((void*)(data + index - 1)) T(value);

			//��������� �� ����������� �� ������� �� ����� 
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
	//������� �������������
	deleteRange(data, data + size_);
	operator delete(data);
	size_ = 0;
	capacity_ = 0;
	data = nullptr;
}


template<typename T>
Vector<T>::~Vector()
{
	//������� �������������
	deleteRange(data, data + size_);
	//����������� �������
	delete(data);
}

#endif
