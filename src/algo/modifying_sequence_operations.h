/*
copy          
copy_n        
copy_if       
copy_backward 
move          
move_backward 
swap          
swap_ranges   
iter_swap     
transform     
replace       
replace_if    
replace_copy  
replace_copy_i
fill          
fill_n        
generate      
generate_n    
remove        
remove_if     
remove_copy   
remove_copy_if
unique        
unique_copy   
reverse       
reverse_copy  
rotate        
rotate_copy   
random_shuffle
shuffle       
*/
#ifndef __MODIFYING_SEQUENCE_OPERATIONS_H
#define __MODIFYING_SEQUENCE_OPERATIONS_H

namespace stl {

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);

template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result);

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred);

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);

template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last, OutputIterator result);

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);
} // namespace stl
#endif