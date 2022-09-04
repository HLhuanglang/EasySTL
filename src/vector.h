/*
* https://github.com/llvm/llvm-project/blob/main/libcxx/include/vector
* https://cplusplus.com/reference/vector/vector/
*/
#ifndef __VECTOR_H
#define __VECTOR_H

#include "allocator.h"

#include <memory>	//allocator_traits
#include <iterator>

namespace stl
{
	template<typename T>
	class vector {
	public:

		using value_type = T;
		using allocator_type = stl::allocator<T>;
		using reference = value_type &;
		using const_reference = const value_type &;
		using size_type = typename std::allocator_traits<allocator_type>::size_type;
		using difference_type = typename std::allocator_traits<allocator_type>::difference_type;
		using pointer = typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer = typename std::allocator_traits<allocator_type>::const_poiner;
		using iterator = value_type *;
		using const_iterator = const value_type *;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		static_assert((std::is_same<typename allocator_type::value_type, value_type>::value), "Allocator::value_type must be same type as value_type");

	private:
		iterator begin_;
		iterator end_;
		iterator end_of_storage_;
	public:
	};
}
#endif // !__VECTOR_H
