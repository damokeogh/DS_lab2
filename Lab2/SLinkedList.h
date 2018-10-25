#pragma once

#include <list>
#include <memory>	// for std::unique_ptr
#include <stack>

using std::list;

// Forward references.
template <typename T, typename InputIterator>class List;
template <typename T>class SListNode;
template <typename T>class SListIterator;

// First the class interface
template <typename T, typename InputIterator>
class SLinkedList : public List<T,InputIterator> {
public:        
               
    SLinkedList();           

    int size() const override;
    bool isEmpty() const override;
	void swap(InputIterator & first, InputIterator & second) override;
    void replace(InputIterator & position, T element) override;        
    void insertFirst(T element) override;
    void insertLast(T element) override;
	void makeNewHead(InputIterator & position);
	void splice(InputIterator & position, list<T> & x);
    void insertAfter(InputIterator & position, T element) override;  	
	void insertBefore(InputIterator & position, T element) override;
	void reverse();
	InputIterator remove(InputIterator & position) override;
    int remove(T element) override;
	

    // Member functions specific to SLinkedList
    SListNode<T>* head() const;
    SListNode<T>* tail() const;
    
    SListIterator<T> begin() const;        
    SListIterator<T> end() const;        
	SListIterator<T> last() const;
    
private:
    std::unique_ptr<SListNode<T>> m_head;
	SListNode<T>* m_tail;
    int m_count;
};

// Now the class implementation.

template <typename T, typename InputIterator>
SLinkedList<T, InputIterator>::SLinkedList() :
    m_head(nullptr),
    m_tail(nullptr),
    m_count(0)
    {}

template <typename T, typename InputIterator>
int SLinkedList<T, InputIterator>::size() const {
    return m_count;
}

template <typename T, typename InputIterator>
bool SLinkedList<T, InputIterator>::isEmpty() const {
    return m_count == 0;
}


template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::swap(InputIterator & first, InputIterator & second) {    
    T temp = *first;
	*first = *second;        
    *second = temp;		
}

template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::replace(InputIterator & position, T element) {    
    *position = element; 
}

template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::insertFirst(T element) {
        // create the new node.
		
		std::unique_ptr<SListNode<T>> newNode = std::make_unique<SListNode<T>>(element, this);       
        newNode->setNext(m_head);
        // set the head node, and the tail node if needed.
		std::swap(m_head, newNode);
        
        if( m_tail == nullptr ) {			
			m_tail = m_head.get();
        }    
        
        m_count++;  
}

template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::insertLast(T element) {
    
	std::unique_ptr<SListNode<T>> newNode = std::make_unique<SListNode<T>>(element, this);

	if (m_head == NULL) {
		newNode->setNext(m_head);
		// set the head node, and the tail node if needed.
		std::swap(m_head, newNode);
		m_tail = m_head.get();
	}
	else
	{
		SListNode<T>* temp = m_tail;
		m_tail = newNode.get();
		temp->setNext(newNode);
		
	}
	m_count++;
	
}

template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::insertAfter(InputIterator & position, T element) {
        //create pointer to current iterator position
		SListNode<T>* temp = position.get();       
		
		//check if replacing after end of list
		if (temp != nullptr) {
			//create new node at the iterator position
			std::unique_ptr<SListNode<T>> newNode = std::make_unique<SListNode<T>>(element, this);

			//sets pointer to next node in list
			newNode->setNext(temp->next());
			// if the new node is the new end of list node
			if (newNode->next() == nullptr) {
				m_tail = newNode.get();
			}
			temp->setNext(newNode);	// newNode is now nullptr
			
			m_count++;
		}
}

template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::insertBefore(InputIterator & position, T element) {
	//create new node at the iterator position
	std::unique_ptr<SListNode<T>> newNode = std::make_unique<SListNode<T>>(element, this);
	/*SListNode<T>* pred = m_head.get();
	SListNode<T>* temp = position.get();*/
	if (m_head.get() == position.get()) {
		newNode->setNext(m_head);
		std::swap(m_head, newNode);
	}
	else {
		//this loop sets pred to the preceeding node
		SListNode<T>* previous = m_head.get();

		// Set up 'previous' to point to the node one before the node we wish to delete.
		for (; previous->next().get() != position.get(); previous = previous->next().get());

		newNode->setNext(previous->next());
		previous->setNext(newNode);
		

	}
	
	m_count++;


}


//Function for Q2
template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::reverse() {
	std::stack<T> s;
	SListIterator<T> temp = m_head.get();
	for (int i = 0; i < m_count; i++)
	{
		s.push(*temp);
		++temp;
	}
	temp = m_head.get();
	for (int i = 0; i < m_count; i++)
	{
		replace(temp, s.top());
		s.pop();
		++temp;

	}

}

//Function for Q3
template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::makeNewHead(InputIterator & position) 
{
	//new node to prevent lost nodes
	std::unique_ptr<SListNode<T>> copyOfPos = std::make_unique<SListNode<T>>(*position, this);
	
	//pointer to passed iterator position
	SListNode<T>* pos = position.get();

	//pointer for looping through until node before position
	SListNode<T>* previous = m_head.get();
	

	// Set up 'previous' to point to the node one before the node we wish to move
	for (; previous->next().get() != position.get(); previous = previous->next().get());

	if (m_head->next().get() == pos)
	{
		copyOfPos->setNext(m_head);
		previous->setNext(pos->next());
		std::swap(m_head, copyOfPos);

	}
	
	else 
	{
		copyOfPos->setNext(m_head->next());

		//this line is the problem
		m_head->setNext(pos->next());

		previous->setNext(m_head);

		std::swap(m_head, copyOfPos);

	}
	

}

//Function for Q4
template <typename T, typename InputIterator>
void SLinkedList<T, InputIterator>::splice(InputIterator & position, list<T> & x) 
{


}



template <typename T, typename InputIterator>
InputIterator SLinkedList<T, InputIterator>::remove(InputIterator & position) {
      SListNode<T>* node = position.get();	     
      
	  // Advance the iterator position to the next node
	  ++position;

      // If the node to be removed is at the head of the list
      if (m_head.get() == node) {
		  m_head = std::move(m_head->next());		  
      }
      else { // Node to be deleted has a predecessor.
		   SListNode<T>* previous = m_head.get();

           // Set up 'previous' to point to the node one before the node we wish to delete.
	       for ( ; previous->next().get() != node; previous = previous->next().get() );

		   // If the node to be deleted is the tail.
           if (node == m_tail) {
              m_tail = previous;
           }
		   // Get a (unique_ptr) reference to the node to be deleted. 
		   std::unique_ptr<SListNode<T>> & deleteMe = previous->next();
           // Link to the node after the one to be deleted.
		   deleteMe = std::move(deleteMe->next());          
       }
                      
       m_count--;

	   // Return the new iterator position
	   return position;       
}


// Implement this function
template <typename T, typename InputIterator>
int SLinkedList<T, InputIterator>::remove(T element) {
    // Remove all occurrences of element
	SListNode<T> *current = m_head.get();
	SListNode<T> *temp;

	int matches = 0;
	while (current != 0) {
		// if we have found a match
		if (current->element() == element) {
			std::cout << "Found a match" << std::endl;
			// Remove the match we have found
			temp = current;
			current = current->next().get();
			SListIterator<T> iterToRemove(temp);
			remove( iterToRemove );
			matches++;
		}
		else {
			current = current->next().get();
		}
	}
	m_count--;
	return matches;
}


template <typename T, typename InputIterator>
SListIterator<T> SLinkedList<T, InputIterator>::last() const {
    if (m_tail != nullptr) {
		return SListIterator<T>(m_tail);
	}
	return this->end();	
}


template <typename T, typename InputIterator>
SListNode<T>* SLinkedList<T, InputIterator>::head() const {
	return m_head.get();
}

template <typename T, typename InputIterator>
SListNode<T>* SLinkedList<T, InputIterator>::tail() const {
	return m_tail;
}

template <typename T, typename InputIterator>
SListIterator<T> SLinkedList<T, InputIterator>::begin() const {
    SListIterator<T> startIterator(m_head.get());
    return startIterator;    
}

template <typename T, typename InputIterator>
SListIterator<T> SLinkedList<T, InputIterator>::end() const {
	// Return a "one past the end" iterator  
	SListNode<T> *temp = nullptr;

	SListIterator<T> endIterator(temp);
	return endIterator;
}

#include "List.h"
#include "SListNode.h"
#include "SListIterator.h"



