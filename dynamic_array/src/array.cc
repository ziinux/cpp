//============================================================================
// Name        : array.cc
// Author      : BADR EL HAFIDI badr@gatech.edu GTID:903243763
// Version     : 1
// Copyright   : GATECH ECE GRAD
// Description : Implementation of dynamic array
//============================================================================

#include "array.h"

/* 
 * array class implementation
 */

//default constructor
template<typename T>
array<T>::array()
{
    m_elements = nullptr;
    m_size = 0;
    m_reserved_size = 0;
}

// initialize array with elements in initializer
template<typename T>
array<T>::array(std::initializer_list<T> l)
{
    m_size = l.size();
    m_reserved_size = l.size();
    m_elements = (T*)malloc(sizeof(T) * l.size());
    for (size_t i=0; i<m_size; i++)
    {
        new (&m_elements[i]) T(l[i]);
    }
}

//copy constructor
template<typename T>
array<T>::array(const array& a)
{
    m_size = a.m_size;
    m_reserved_size = a.m_reserved_size;
    m_elements = (T*)malloc(sizeof(T) * a.m_size);
    for (size_t i=0; i<m_size; i++)
    {
        new (&m_elements[i]) T(a[i]);
    }
}

//move constructor
template<typename T>
array<T>::array(array&& a)
{
    m_size = a.m_size;
    m_reserved_size = a.m_reserved_size;
    m_elements = (T*)malloc(sizeof(T) * a.m_size);
    for (size_t i=0; i<m_size; i++)
    {
        new (&m_elements[i]) T(a[i]);
    }

    for (size_t i=0; i<a.m_size; i++)
    {
        a.m_elements[i].~T();
    }

    free(a.elements);
    a.elements = nullptr;
    a.m_size = 0;
    a.m_reserved_size = 0;

}

//construct with initial "reserved" size
template<typename T>
array<T>::array(size_t p_reserved_size)
{
    m_elements = (T*)malloc(sizeof(T) * p_reserved_size);
    m_size = 0;
    m_reserved_size = p_reserved_size;
}

//construct with n copies of t
template<typename T>
array<T>::array(size_t n, const T& t)
{
    m_size = n;
    m_reserved_size = n;
    m_elements = (T*)malloc(sizeof(T) * m_size);
	for (size_t i=0; i<m_size; i++)
	{
		new (&m_elements[i]) T(t);
	}
}

//destructor
template<typename T>
array<T>::~array()
{
    for(size_t i=0; i<m_size; i++)
    {
        m_elements[i].~T();
    }

    free(m_elements);
    m_elements = nullptr;
    m_size = 0;
    m_reserved_size = 0;
}

//ensure enough memory for n elements
template<typename T>
void array<T>::reserve(size_t n)
{
	T* tmp_elements = (T*)malloc(sizeof(T) * n);
	
	for (size_t i=0; i<m_size; i++)
	{
		new (&tmp_elements[i]) T(m_elements[i]);
		m_elements[i].~T();
	}
	free(m_elements);
	m_elements = tmp_elements;
	m_reserved_size = n;
}

//add to end of vector
template<typename T>
void array<T>::push_back(const T& t)
{
	if (m_size+1 > m_reserved_size)
	{
		reserve(m_size+1);
	}
	new (&m_elements[m_size]) T(t);
	m_size++;
}

//add to front of vector
template<typename T>
void array<T>::push_front(const T& t)
{
	if (m_reserved_size > m_size)
	{
		for (size_t i=m_size; i>0; i--)
		{
			m_elements[i] = m_elements[i-1];
		}
		m_size++;
		new (&m_elements[0]) T(t);
	}
	else
	{
		m_reserved_size = m_size+1;
		T* tmp_elements = (T*)malloc(sizeof(T) * m_reserved_size);
		for (size_t i=m_size; i>0; i--)
		{
			new (&tmp_elements[i]) T(m_elements[i-1]);
			m_elements[i-1].~T();
		}
		free(m_elements);
		m_elements = tmp_elements;
		m_size++;
		new (&m_elements[0]) T(t);
	}	
}

//remove last element
template<typename T>
void array<T>::pop_back()
{
	m_elements[m_size-1].~T();
	m_size--;
}

//remove first element
template<typename T>
void array<T>::pop_front()
{
    if(m_size>1)
    {
	    for (size_t i=0; i<=m_size-2; i++)
	    {
	    	m_elements[i].~T();
	    	new (&m_elements[i]) T(m_elements[i+1]);
	    }
    }

    if(m_size>0)
    {
	    m_elements[m_size-1].~T();
	    m_size--;
    }
}

//return reference to first element
template<typename T>
T& array<T>::front() const
{
    return m_elements[0];
}

//return reference to last element
template<typename T>
T& array<T>::back() const
{
    return m_elements[m_size-1];
}

//return reference to specified element
template<typename T>
const T& array<T>::operator[](size_t k) const
{
	return this->m_elements[k];
}

//return reference to specified element
template<typename T>
T& array<T>::operator[](size_t k)
{
	return this->m_elements[k];
}

//return number of elements
template<typename T>
size_t array<T>::length() const
{
    return m_size;
}

//returns true if empty
template<typename T>
bool array<T>::empty() const
{
    return (m_size == 0);
}

//remove all elements
template<typename T>
void array<T>::clear()
{
	for (size_t i=0; i<m_size; i++)
    {
    	m_elements[i].~T();
    }  
	m_size = 0;
}

//obtain iterator to first element
template<typename T>
array_iterator<T> array<T>::begin() const
{
    return array_iterator<T>(m_elements);
}

//obtain iterator to one beyond element
template<typename T>
array_iterator<T> array<T>::end() const
{
    return array_iterator<T>(m_elements + m_size);
}

//remove specified element
template<typename T>
void array<T>::erase(const array_iterator<T>& it)
{
    for (size_t i=0; i < m_size; i++)
    {
    	if (it.m_current == &m_elements[i])
    	{
            for (size_t j=i; j<=m_size-2; j++)
            {
            	m_elements[j].~T();
            	new (&m_elements[j]) T(m_elements[j+1]);
            }
            m_elements[m_size-1].~T();
            m_size--;
    		break;
    	}
    }
}

//insert element right before itr
template<typename T>
void array<T>::insert(const T& t, const array_iterator<T>& it)
{
    
    for (size_t i = 0; i < m_size; ++i)
    {
    	if (&m_elements[i] == it.m_current)
    	{
	        if (m_reserved_size > m_size)
	        {
	        	for (size_t j=m_size; j>i; j--)
	        	{
	        		m_elements[j] = m_elements[j-1];
	        	}
	        	m_size++;
	        	new (&m_elements[i]) T(t);
	        }
	        else
	        {
	        	m_reserved_size = m_size + 1;
	        	T* tmp_elements = (T*)malloc(sizeof(T) * m_reserved_size);
	        	for (size_t j=0; j<i; j++)
	        	{
	        		new (&tmp_elements[j]) T(m_elements[j]);
	        		m_elements[j].~T();
	        	}

	        	for (size_t j=i+1; j<=m_size; j++)
	        	{
	        		new (&tmp_elements[j]) T(m_elements[j-1]);
	        		m_elements[j-1].~T();
	        	}

	        	new (&tmp_elements[i]) T(t);

	        	m_size++;
	        	free(m_elements);
	        	m_elements = tmp_elements;
	        }
    		break;
    	}
    }
}

/* 
 * array_iterator class implementation
 */

template<typename T>
array_iterator<T>::array_iterator()
{
    m_current = nullptr;
}

template<typename T>
array_iterator<T>::array_iterator(T* t)
{
    m_current = t;
}

template<typename T>
array_iterator<T>::array_iterator(const array_iterator& it)
{
    m_current = it.m_current;
}

template<typename T>
T& array_iterator<T>::operator*() const
{
    return *m_current;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator++()
{
    m_current++;
    return *this;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator++(int __unused)
{
    array_iterator<T> it(*this);
    m_current++;
    return it;
}

template<typename T>
bool array_iterator<T>::operator != (const array_iterator& it) const
{
    return (m_current != it.m_current);
}

template<typename T>
bool array_iterator<T>::operator == (const array_iterator& it) const
{
    return (m_current == it.m_current);
}


