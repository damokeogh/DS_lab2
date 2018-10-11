#pragma once
// Forward references.
template <typename T> class Container;

#include <memory>

template <typename T>
class SListNode {

public:    
    SListNode(T element, Container<T>* container=0);
	~SListNode();
    
    T & element();
    const Container<T>* container() const;
    void setElement(T element);
        
    void setNext(std::unique_ptr<SListNode<T>> & next);
	std::unique_ptr<SListNode<T>> & next();
     
    
private:
    T m_element;                // The data field - notice it's a generic type
    std::unique_ptr<SListNode<T>> m_next;      // A pointer to the next node
    Container<T>* m_container; // A pointer to the container of which this node belongs   
};

template <typename T>
SListNode<T>::SListNode(T element, Container<T>* container) :
    m_element(element), 
    m_container(container), 
    m_next(nullptr) 
    {}

template <typename T>
SListNode<T>::~SListNode() {
	std::cout << "Deleted: " << m_element << std::endl;
}

template <typename T>
T & SListNode<T>::element() {
    return m_element;    
}

template <typename T>
const Container<T>* SListNode<T>::container() const {
    return m_container;   
}

template <typename T>
void SListNode<T>::setElement(T element) {
   m_element = element;
}


template <typename T>
void SListNode<T>::setNext(std::unique_ptr<SListNode<T>> & next) {
	std::swap(m_next, next);
}

template <typename T>
std::unique_ptr<SListNode<T>> & SListNode<T>::next() {
	return m_next;
}


