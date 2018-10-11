#pragma once

// Forward references.
template <typename T, typename Iterator>class Sequence;

template <typename T, typename Iterator>
class List : public Sequence<T, Iterator> {
public:        
    virtual void insertFirst(T element) = 0;
    virtual void insertLast(T element) = 0;
    virtual void insertAfter(Iterator & position, T element) = 0;
	virtual void insertBefore(Iterator & position, T element) = 0;
    virtual Iterator remove(Iterator & position) = 0;    
    virtual int remove(T element) = 0;	
};

#include "Sequence.h"

