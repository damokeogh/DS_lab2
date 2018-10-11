#include <iostream>

#pragma once

template <typename T>class SListNode;  // Forward reference.

//using namespace std;

template <typename T>
class SListIterator : public std::iterator<std::forward_iterator_tag, T> { 
public:
    SListIterator(SListNode<T>* initialNode = 0) {
        m_current = initialNode; 
    }
        
    T & operator *() const { 
	    return (*m_current).element();  
    } 
    
	SListNode<T>* get() {
		return m_current;
	}

	SListIterator<T>& operator ++(); // Prefix ++
	SListIterator<T> operator ++(int); // Postfix ++	
	bool operator ==(SListIterator<T> other) const; 
	bool operator !=(SListIterator<T> other) const; 
    T & operator [](int index) ;
	

private:
	SListNode<T>* m_current;
};

template <typename T>
SListIterator<T>& SListIterator<T> :: operator ++() { 
     m_current = m_current->next().get();
     return *this;
}
	
template <typename T>
SListIterator<T> SListIterator<T> :: operator ++(int) {
     SListIterator<T> original(m_current);
     m_current = m_current->next().get();
     return original;      	  
}

template <typename T>
bool SListIterator<T> :: operator ==(const SListIterator<T> other) const { 
     return m_current == other.m_current;  
}
	
template <typename T>
bool SListIterator<T> :: operator !=(const SListIterator<T> other) const {
     return m_current != other.m_current;   
}

template <typename T>
T & SListIterator<T> :: operator [](int index) {
	for (int i = 0; i < index; i++) {
		m_current = m_current->next().get();		
	}
	return m_current->element();
}

#include "SListNode.h"

