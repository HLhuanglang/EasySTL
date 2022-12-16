#ifndef __LIST_H
#define __LIST_H
/*
* ```
* doubly linked
* ```
* list::list
* list::~list
*
* ``` member functions
* assign
* back
* begin
* cbegin
* cend
* clear
* crbegin
* crend
* emplace
* emplace_back
* emplace_fron
* empty
* end
* erase
* front
* get_allocator
* insert
* max_size
* merge
* operator=
* pop_back
* pop_front
* push_front
* push_back
* rbegin
* remove
* remove_if
* reverse
* size
* sort
* splice
* swap
* unique
* ```
*/

#include "allocator.h"
#include <iterator>
#include <memory>

namespace stl
{
	template<typename T>
	class list_iterator_t :public std::iterator<std::bidirectional_iterator_tag, T> {
	};

	template<typename T>
	class list_const_iterator_t :public std::iterator<std::bidirectional_iterator_tag, T> {
	};

	template<typename T>
	class list {
		using value_type = T;
		using allocator_type = stl::allocator<T>;
		using reference = value_type &;
		using const_reference = const value_type &;
		using pointer = typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
		using difference_type = typename std::iterator_traits<iterator>::difference_type;
		using size_type = typename std::iterator_traits<iterator>::size_type;
	};

	/*
	* non-member overloads
	* a==b、a!=b
	* a<b、a>b
	* a<=b、!(b<a)
	* a>=b、!(b>a)
	*/
	//--relation operators

	//--swap
	template<class T>
	void swap(list<T> &x, list<T> &y) {
		//todo
	}
}
#endif
