#pragma once

// Forward references.
template <typename T> class Container;

template <typename T, typename InputIterator>
class Sequence : public Container<T> {
public:       
    virtual void swap(InputIterator & first, InputIterator & second) = 0;
	virtual void replace(InputIterator & position, T element) = 0;    
};

#include "Container.h"

