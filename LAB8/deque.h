/*

#ifndef COEN79_DEQUE
#define COEN79_DEQUE
#ifdef USEDEBUG
#define Debug(x) std::cout << x
#else
#define Debug(x)
#endif
#include <math.h>
#include <stdio.h>

#include <cassert>
#include <cstdlib>

#include "deque_iterator.h"  // The iterator class for deque (refer to file deque_iterator.h)
namespace coen79_lab8
{
    template <class Item>
    class deque {
       public:
        static const size_t BLOCK_SIZE = 5;               // Number of data items per data block
        static const size_t BLOCKPOINTER_ARRAY_SIZE = 5;  // Number of entries in
        typedef std::size_t size_type;
        typedef Item value_type;                // The type of items stored in the deque
        typedef deque_iterator<Item> iterator;  // A typedef to simplify the use of iterator class
        deque(size_type init_bp_array_size = BLOCKPOINTER_ARRAY_SIZE, size_type initi_block_size = BLOCK_SIZE);
        deque(const deque& source);
        ~deque();
        bool isEmpty();
        value_type front();
        value_type back();
        iterator begin();
        iterator end();
        void operator=(const deque& source);
        void clear();
        void reserve();
        void push_front(const value_type& entry);
        void push_back(const value_type& entry);
        void pop_back();
        void pop_front();

       private:
        value_type** block_pointers;                                         // A pointer to the array of block
        value_type** block_pointers_end;                            // A pointer to the final entry in the
        value_type** first_bp;                       // A pointer to the entry of the array of block
        value_type** last_bp;  // A pointer to the entry of the array of block
        value_type* front_ptr;  // A pointer to the front element of the deque
        value_type* back_ptr;                                                // A pointer to the back element of the deque
        size_type bp_array_size;                                             // Number of entries in the array of block
        size_type block_size;                                       // Number of entries in each data block
    };

template <class Item>
deque<Item>::deque(size_type init_bp_array_size, size_type init_block_size) {
        bp_array_size = init_bp_array_size;
        block_size = init_block_size;
        block_pointers = new value_type*[bp_array_size];
        for (size_type index = 0; index < bp_array_size; ++index) {
            block_pointers[index] = NULL;
        }
        block_pointers_end = block_pointers + (bp_array_size - 1);
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }
    template <class Item>
    deque<Item>::deque(const deque<Item>& source) {
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
        block_pointers = block_pointers_end = NULL;
        bp_array_size = 0;
	*this = source;
    }
    template <class Item>
    void deque<Item>::operator=(const deque<Item>& source)
 {
        
        clear();
        
        delete [] block_pointers;
        block_pointers = NULL;
        block_pointers_end = NULL;
        
        bp_array_size = source.bp_array_size;
        block_size = source.block_size;
        
        block_pointers = new value_type*[bp_array_size];
        
        
        for (size_type bp_array_index = 0; bp_array_index < source.bp_array_size; ++bp_array_index)
        {
	delete[] block_pointers;
        block_pointers = NULL;
        block_pointers_end = NULL;
        bp_array_size = source.bp_array_size;
        block_size = source.block_size;
        block_pointers = new value_type*[bp_array_size];
        block_pointers_end = block_pointers + bp_array_size - 1;

	for (size_type bp_array_index = 0; bp_array_index < source.bp_array_size; ++bp_array_index) {
            if (source.block_pointers[bp_array_index] == NULL) {
                block_pointers[bp_array_index] = NULL; 
            } else {
                if(*source.first_bp == source.block_pointers[bp_array_index]) {
                    first_bp = bp_array_index + block_pointers;
                }
                if(*source.last_bp == source.block_pointers[bp_array_index]) {
                    last_bp = bp_array_index + block_pointers;
                }
                block_pointers[bp_array_index] = new value_type[block_size];
                for (size_type block_item_index = 0; block_item_index < block_size; ++block_item_index) {
                    if (source.block_pointers[bp_array_index] + block_item_index == source.back_ptr) {
                        back_ptr = block_pointers[bp_array_index] + block_item_index;
                    }
                    if (source.block_pointers[bp_array_index] + block_item_index == source.front_ptr) {
                        front_ptr = block_pointers[bp_array_index] + block_item_index;
                    }
                    *(block_pointers[bp_array_index] + block_item_index) = *(source.block_pointers[bp_array_index] + block_item_index);
                }
            }
        }
    }
 
    template <class Item>
    deque<Item>::~deque() {
        clear();
        delete[] block_pointers;
        first_bp = last_bp = block_pointers_end = block_pointers = NULL;
        front_ptr = back_ptr = NULL;
    }

    template <class Item>
    void deque<Item>::clear() {
        for (int i = 0; i<bp_array_size; i++) {
            if(block_pointers[i == NULL]) {
                delete[] block_pointers[i];
                block_pointers[i] = NULL;
            }
        }
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }

    template <class Item>
    void deque<Item>::reserve() {
        size_type newSize = bp_array_size + 20;
        value_type** new_block_pointers = new value_type*[newSize];
        for (size_type index = 0; index < newSize; ++index) {
            new_block_pointers[index] = NULL;
        }
        size_type offsett_first_bp = first_bp - block_pointers;
        size_type offsett_last_bp = last_bp - block_pointers;
        std::copy(first_bp, last_bp + 1, new_block_pointers + 10 + offsett_first_bp);
        delete[] block_pointers;
        block_pointers = new_block_pointers;
        bp_array_size = newSize;
        block_pointers_end = block_pointers + bp_array_size - 1;
        first_bp = block_pointers + offsett_first_bp + 10;
        last_bp = block_pointers + offsett_last_bp + 10;
    }
    template <class Item>
    void deque<Item>::push_front(const value_type& entry) {
        if (first_bp == NULL) {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size / 2);  // Get the mid point of the
            last_bp = first_bp = block_pointers + bp_mid - 1;
            *first_bp = new value_type[block_size];
            *back_ptr = entry;
            front_ptr = *first_bp;
            back_ptr = *last_bp;
        }
        else if (front_ptr != *first_bp) {
            --front_ptr;
            *front_ptr = entry;
        }
        else if ((*first_bp == front_ptr) && (first_bp != block_pointers)) {
            first_bp--;
            *first_bp = new value_type[block_size];
            front_ptr = *first_bp;
            front_ptr = front_ptr + (block_size - 1);
            *front_ptr = entry;
	}
        else if ((*first_bp == front_ptr) && (first_bp == block_pointers)) {
            reserve();
            --first_bp;
            *first_bp = new value_type[block_size];
            front_ptr = *first_bp;
	    front_ptr = ((front_ptr) + (block_size-1));
            *front_ptr = entry;
        }
    }
    template <class Item>
    void deque<Item>::push_back(const value_type& entry) {
        if (last_bp == NULL) {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size / 2);  // Get the mid point of the array of block pointers last_bp = first_bp = block_pointers + bp_mid - 1;
            
            last_bp = first_bp = block_pointers+ bp_mid - 1;
            *first_bp = new value_type[block_size];
            front_ptr = *first_bp;
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
        else if (back_ptr != ((*last_bp) + (block_size - 1))) {
            ++back_ptr;
            *back_ptr = entry;
        }
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp != block_pointers_end)) {
            ++last_bp;
            *last_bp = new value_type[block_size];
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp == block_pointers_end)) {
            reserve();
            ++last_bp;
            *last_bp = new value_type[block_size];
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
    }
    template <class Item>
    void deque<Item>::pop_front() {
        assert(!isEmpty());
        if (back_ptr == front_ptr) {
            clear();
        }
        else if (front_ptr == ((*first_bp) + block_size - 1)) {
            delete[] *first_bp;
            *first_bp = NULL;
            ++first_bp;
            front_ptr = *first_bp;
        }
        else {
            ++front_ptr;
        }
    }
    template <class Item>
    void deque<Item>::pop_back() {
        assert(!isEmpty());
        if (back_ptr == front_ptr) {
            clear();
        } else if (back_ptr == *last_bp) {
            delete[] *last_bp;
            *last_bp = NULL;
            --last_bp;
            back_ptr = *last_bp + block_size - 1;
        } else {
            --back_ptr;
        }
    }
    template <class Item>
    bool deque<Item>::isEmpty() {
        if (front_ptr == NULL) return true;
        return false;
    }
    template <class Item>
    typename deque<Item>::value_type deque<Item>::back() {
        assert(!isEmpty());
        return *back_ptr;
    }
    template <class Item>
    typename deque<Item>::value_type deque<Item>::front() {
        assert(!isEmpty());
        return *front_ptr;
    }
    template <class Item>
    typename deque<Item>::iterator deque<Item>::begin() {
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        if (front_ptr != NULL) {
            tmp_cursor = front_ptr;
            tmp_current_block_pointer = first_bp;
            tmp_current_boundary = (*first_bp) + (block_size - 1);
        }
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp, front_ptr, back_ptr, bp_array_size, block_size, tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
    template <class Item>
    typename deque<Item>::iterator deque<Item>::end() {
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp, front_ptr, back_ptr, bp_array_size, block_size, tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
}*/
//#endif /* deque_hpp */

#ifndef COEN79_DEQUE
#define COEN79_DEQUE


#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <cassert>

#include "deque_iterator.h" // The iterator class for deque (refer to file deque_iterator.h)


namespace coen79_lab8
{
    template <class Item>
    class deque {
    public:
        
        static const size_t BLOCK_SIZE = 5; // Number of data items per data block
        static const size_t BLOCKPOINTER_ARRAY_SIZE = 5; // Number of entries in the array of block pointers (The minimum acceptable value is 2)
        
        typedef std::size_t size_type;
        typedef Item value_type; // The type of items stored in the deque
        
        typedef deque_iterator<Item> iterator; // A typedef to simplify the use of iterator class
        
        deque(size_type init_bp_array_size = BLOCKPOINTER_ARRAY_SIZE, size_type initi_block_size = BLOCK_SIZE);
        deque(const deque& source);
        ~deque();
        
        bool isEmpty();
        value_type front();
        value_type back();
        
        iterator begin();
        iterator end();
        
        void operator=(const deque& source);
        void clear();
        void reserve();
        void push_front(const value_type& entry);
        void push_back(const value_type& entry);
        void pop_back();
        void pop_front();
        
        
    private:
        
        value_type** block_pointers;      // A pointer to the array of block pointers
        value_type**  block_pointers_end; // A pointer to the final entry in the array of block pointers
        
        value_type**  first_bp;  // A pointer to the entry of the array of block pointers which points to the first data block
        value_type**  last_bp;   // A pointer to the entry of the array of block pointers which points to the last data block
        
        value_type* front_ptr;   // A pointer to the front element of the deque
        value_type* back_ptr;    // A pointer to the back element of the deque
        
        size_type bp_array_size; // Number of entries in the array of block pointers
        size_type block_size;    // Number of entries in each data block
    };
    
    template <class Item>
    deque<Item>::deque (size_type init_bp_array_size, size_type init_block_size) {
        
        bp_array_size = init_bp_array_size;
        block_size = init_block_size;
        
        block_pointers = new value_type* [bp_array_size];
        
        for (size_type index = 0; index < bp_array_size; ++index)
        {
            block_pointers[index] = NULL;
        }
        
        block_pointers_end = block_pointers + (bp_array_size - 1);
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }
    
    
    template <class Item>
    deque<Item>::deque (const deque<Item>& source) {
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
        block_pointers = block_pointers_end = NULL;
 
        bp_array_size = 0;
 
        *this = source;
    }
    
    
    template <class Item>
    void deque<Item>::operator=(const deque<Item>& source) {
        
        clear();
        
        delete [] block_pointers;
        block_pointers = NULL;
        block_pointers_end = NULL;
        
        bp_array_size = source.bp_array_size;
        block_size = source.block_size;
        
        block_pointers = new value_type*[bp_array_size];
        
        
        for (size_type bp_array_index = 0; bp_array_index < source.bp_array_size; ++bp_array_index)
        {
            if (source.block_pointers[bp_array_index] == NULL)
            {
                block_pointers[bp_array_index] = NULL;
            }
            else
            {
                if (*(source.first_bp) == source.block_pointers[bp_array_index]) {
                    first_bp = block_pointers + bp_array_index;
                }
                
                if (*(source.last_bp) == source.block_pointers[bp_array_index]) {
                    last_bp = block_pointers + bp_array_index;
                }
                
                block_pointers[bp_array_index] = new value_type [block_size];
                
                
                for (size_type block_item_index = 0; block_item_index < block_size; ++block_item_index)
                {
                    if (source.block_pointers[bp_array_index] + block_item_index == source.front_ptr) {
                        front_ptr = block_pointers[bp_array_index] + block_item_index;
                    }
                    if (source.block_pointers[bp_array_index] + block_item_index == source.back_ptr) {
                        back_ptr = block_pointers[bp_array_index] + block_item_index;
                    }
                    *(block_pointers[bp_array_index] + block_item_index) = *(source.block_pointers[bp_array_index] + block_item_index);
                }
            }
        }
    }
    
    
    template <class Item>
    deque<Item>::~deque () {
        
        clear();
        
        delete []block_pointers;
        
        first_bp = last_bp = block_pointers_end = block_pointers = NULL;
        front_ptr = back_ptr = NULL;
    }
    
    
    template <class Item>
    void deque<Item>::clear () {
        
        for (size_type i = 0; i < bp_array_size; i++) {
            if (block_pointers[i] != NULL) {
                delete []block_pointers[i];
                block_pointers[i] = NULL;
            }
        }
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }
    
    
    
    template <class Item>
    void deque<Item>::reserve()
    {
        size_type newSize = bp_array_size + 20;
        
        value_type** new_block_pointers = new value_type* [newSize];
        
        for (size_type index = 0; index < newSize; ++index)
        {
            new_block_pointers[index] = NULL;
        }
        
        size_type offsett_first_bp = first_bp - block_pointers;
        size_type offsett_last_bp = last_bp - block_pointers;
        
        
        std::copy(first_bp, last_bp + 1, new_block_pointers + 10 + offsett_first_bp);
        
        
        delete [] block_pointers;
        
        block_pointers = new_block_pointers;
        bp_array_size = newSize;
        block_pointers_end = block_pointers + bp_array_size - 1;
        first_bp = block_pointers + offsett_first_bp + 10;
        last_bp = block_pointers + offsett_last_bp + 10;
    }
    
    
    template <class Item>
    void deque<Item>::push_front(const value_type& entry)
    {
        if (first_bp == NULL)
        {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
            
            last_bp = first_bp = block_pointers + bp_mid - 1;
            
            *first_bp = new value_type[block_size];

            front_ptr = *first_bp;
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
        else if (front_ptr != *first_bp)
        {
            --front_ptr;
            *front_ptr = entry;
        }
        
        else if ((*first_bp == front_ptr) && (first_bp != block_pointers))
        {
            --first_bp;
            *first_bp = new value_type[block_size];
            front_ptr = ((*first_bp) +(block_size - 1));
            *front_ptr = entry;

        }
        
        else if ((*first_bp == front_ptr) && (first_bp == block_pointers))
        {
            reserve();
            --first_bp;
            *first_bp = new value_type[block_size];
            front_ptr = ((*first_bp) + (block_size - 1));
            *front_ptr = entry;

        }
    }
    
    
    template <class Item>
    void deque<Item>::push_back(const value_type& entry)
    {
        if (last_bp == NULL)
        {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
            
            last_bp = first_bp = block_pointers + bp_mid  - 1;

            *first_bp = new value_type[block_size];
            front_ptr = *first_bp;
            back_ptr = *last_bp;
            *back_ptr = entry;

        }
        
        else if (back_ptr != ((*last_bp) + (block_size - 1)))
        {
            ++back_ptr;
            *back_ptr = entry;

        }
        
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp != block_pointers_end))
        {
            ++last_bp;
            *last_bp = new value_type[block_size];
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
        
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp == block_pointers_end))
        {
            reserve();
            ++last_bp;
            *last_bp = new value_type[block_size];
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
    }
    
    
    template <class Item>
    void deque<Item>::pop_front()
    {
        assert(!isEmpty());
        
        if (back_ptr == front_ptr)
        {
            clear();

        }
        else if (front_ptr == ((*first_bp) + block_size - 1))
        {
            delete []*first_bp;
            *first_bp = NULL;
            ++first_bp;
            front_ptr = *first_bp;

        }
        else
        {
            ++front_ptr;

        }
    }
    
    
    template <class Item>
    void deque<Item>::pop_back()
    {
        assert(!isEmpty());
        
        if (back_ptr == front_ptr)
        {
            clear( );
        }
        else if (back_ptr == *last_bp)
        {
            delete []back_ptr;
            *last_bp = NULL;
            --last_bp;
            back_ptr = *last_bp + block_size - 1;

        }
        else
        {
            --back_ptr;
        }
    }
    
    template <class Item>
    bool deque<Item>::isEmpty()
    {
        if (front_ptr == NULL)
            return true;
        
        return false;
    }
    
    template <class Item>
    typename deque<Item>::value_type deque<Item>::back()
    {
        assert(!isEmpty());
        return *back_ptr;
    }
    
    template <class Item>
    typename deque<Item>::value_type deque<Item>::front()
    {
        assert(!isEmpty());
        return *front_ptr;
    }
    
    
    template <class Item>
    typename deque<Item>::iterator deque<Item>::begin()
    {
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        
        if (front_ptr != NULL)
        {
            tmp_cursor = front_ptr;
            tmp_current_block_pointer = first_bp;
            tmp_current_boundary = (*first_bp) + (block_size - 1);
        }
        
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                        front_ptr, back_ptr,
                        bp_array_size, block_size,
                        tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
    
    
    template <class Item>
    typename deque<Item>::iterator deque<Item>::end()
    {
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                        front_ptr, back_ptr,
                        bp_array_size, block_size,
                        tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
    
}

#endif /* deque_hpp */

