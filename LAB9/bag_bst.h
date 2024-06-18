
#ifndef COEN79_BST_BAG
#define COEN79_BST_BAG

#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions

namespace coen79_lab9
{
    template <class Item>
    class bag
    {
    public:
        typedef std::size_t size_type;
        typedef Item value_type;
        
        bag( ) { root_ptr = NULL; }
        bag(const bag& source);
        ~bag( );
        
        size_type erase(const Item& target);
        bool erase_one(const Item& target);
        void insert(const Item& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);
        
        size_type size( ) const;
        size_type count(const Item& target) const;
        void debug( ) const { print(root_ptr, 0); }
        
    private:
        binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
        void insert_all(binary_tree_node<Item>* addroot_ptr);
    };
    
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);
}

namespace coen79_lab9
{
    
#pragma mark - Toolkit Function Implementation
    
    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
  
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        assert(root_ptr != NULL);
        
        if (root_ptr->right( ) != NULL)
            bst_remove_max(root_ptr->right( ), removed);
        else
        {
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->left();
            removed = oldroot_ptr->data();
            delete oldroot_ptr;
            return;
        }
    }
    
    
    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
   
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return false;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            return bst_remove(root_ptr->left(), target);
            
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
             return bst_remove(root_ptr->right(), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return true;
        }
       
        bst_remove_max(root_ptr->left(),root_ptr->data());
        return true;
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bst_remove_all (binary_tree_node<Item>*& root_ptr, const Item& target)
   
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return 0;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            return bst_remove_all(root_ptr->left(), target);
            
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
             return bst_remove_all(root_ptr->right(), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can

            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return 1;
        }
        
        bst_remove_all(root_ptr->left(),root_ptr->data());
        return 1 + bst_remove_all(root_ptr, target);
    }
    
    
#pragma mark - Member Function Implementation

    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    {
        root_ptr = tree_copy(source.root_ptr);
    }
    
    

    template <class Item>
    bag<Item>::~bag( )
    {
        tree_clear(root_ptr);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    {
        return tree_size(root_ptr);
    }
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    {
        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;
        
        if (root_ptr == NULL)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }
        
        do
        {
            if (cursor->data( ) >= entry)
            {   // Go left
                
                if (cursor->left() == NULL){
                    cursor->set_left(new binary_tree_node<Item>(entry));
                    done = true;
                }
                else{
                    cursor = cursor->left();
                }
            }
            else
            {   // Go right
                if (cursor->right() == NULL){
                    cursor->set_right(new binary_tree_node<Item>(entry));
                    done = true;
                }
                else{
                    cursor = cursor->right();
                }
                
            }
        }   while (!done);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor = root_ptr;
        
        while (cursor != NULL)
        {
            if (cursor->data( ) < target)
                cursor = cursor->right();
            else
            {
                if(cursor->data() == target){
                    ++answer;
                }
                cursor = cursor->left();
            }
        }
        return answer;
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        return bst_remove_all(root_ptr, target);
    }
    
    
    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        return bst_remove(root_ptr, target);
    }
    
    
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    {
        if (this == &source){
            return;
        }
        tree_clear(root_ptr);
        root_ptr = tree_copy(source.root_ptr);
    }
    
    
    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        if (root_ptr == addend.root_ptr)
        {
            bag<Item> tmp = addend;
            insert_all(tmp.source_ptr);
            return;
        }
        else
            insert_all(addend.root_ptr);
    }
    
    
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        return (b1+=b2);
    }
    
    
    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    {
        if (addroot_ptr != NULL)
        {
            insert(addroot_ptr->data());
            insert_all(addroot_ptr->left());
            insert_all(addroot_ptr->right());
        }
    }

}

#endif

