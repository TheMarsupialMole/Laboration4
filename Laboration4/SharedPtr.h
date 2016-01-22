#pragma once
#include "SP_use_count.h"
#include <iostream>


/*
pointer kan vara nullpointer men då är uc(countern) också nullpointer
om pointern pekar på något är också countern "aktiv"
*/
template <class T>
class SharedPtr
{
private:
	T* pointer = nullptr;
	SP_use_count* uc = nullptr;
public:
	SharedPtr<T>();
	SharedPtr<T>(std::nullptr_t);
	SharedPtr<T>(T*);
	SharedPtr<T>(SharedPtr&);
	~SharedPtr<T>();
	SharedPtr<T>& operator=(const SharedPtr<T>&);
	bool operator==(std::nullptr_t);
	bool operator==(SharedPtr&);
	T& operator*();
	bool operator<(const SharedPtr<T>& rhs);
	operator bool();
	void reset(T* in);
	T* get();
	T* operator->();
	bool unique();
	int getUseCount();
	SP_use_count& getUC();


};

//default constructor
template<class T>
SharedPtr<T>::SharedPtr()
{
	
}

//constructor that accepts a nullptr
template<class T>
SharedPtr<T>::SharedPtr(std::nullptr_t)
{
	SharedPtr();
}

//constructor that takes a T pointer
template<class T>
SharedPtr<T>::SharedPtr(T* in)
{
	uc = new SP_use_count(1);
	pointer = in;
}

//copy constructor
template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& in)
{
	if (in.pointer != nullptr) {
		pointer = in.pointer;
		uc = &in.getUC();
		uc->addUseCount();
	}
	else {
		SharedPtr(nullptr);
	}
}

//destructor
template<class T>
SharedPtr<T>::~SharedPtr()
{
	if (unique()) {
		delete pointer;
		delete uc;
	}
	else
		uc->decUseCount();
}

//= operator that sets THIS pointer to the incoming pointer and adds on the use count
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& in)
{
	if (!unique()) 
		uc->decUseCount();

	pointer = in.pointer;
	uc = in.uc;
	uc->addUseCount();
	return *this;
}

// kolla om klassens pekare är en null-pekare
template<class T>
bool SharedPtr<T>::operator==(std::nullptr_t)
{
	return pointer == nullptr;
}

//method that checks if the "this" pointer is equal to the parameter pointer
template<class T>
bool SharedPtr<T>::operator==(SharedPtr<T>& in)
{
	return pointer == in.pointer;
}

//pointer dereferencing, get the value that the pointer holds
template<class T>
T& SharedPtr<T>::operator*()
{
	return *this->pointer;
}


template<class T>
bool SharedPtr<T>::operator<(const SharedPtr<T>& rhs)
{
	return this->pointer < rhs.pointer;
}

//check if the pointer is a null pointer
template<class T>
SharedPtr<T>::operator bool()
{
	return pointer != nullptr;
}

//method that resets the "this" object
template<class T>
void SharedPtr<T>::reset(T* in)
{
	if (in != nullptr) {
		delete pointer;
		pointer = in;
		uc->setUseCount(1);
	}
	else {
		delete pointer;
		pointer = nullptr;
		delete uc;
	}
}

//method that returns the pointer
template<class T>
T* SharedPtr<T>::get()
{
	return pointer;
}

//same as the "get" but does not return a null pointer
template<class T>
T* SharedPtr<T>::operator->()
{
	if (pointer != nullptr)
		return pointer;
}

//method that checks if the pointer is a null pointer or if the use count is over 1.
template<class T>
bool SharedPtr<T>::unique()
{
	if (pointer == nullptr || uc->getUseCount() > 1)
		return false;
	return true;
}

//returns the number of sharings of the pointer
template<class T>
int SharedPtr<T>::getUseCount()
{
	return uc->getUseCount();
}

template<class T>
SP_use_count& SharedPtr<T>::getUC() {
	return uc->getThis();
}

