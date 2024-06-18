#ifndef COEN79_BINTREE_H
#define COEN79_BINTREE_H

#include <cstdlib>  // Provides NULL and size_t
#include <cassert>
#include <iomanip>
#include <vector>

namespace coen79_lab9
{
    template <class Item>
    class binary_tree_node
    {
    public:
        
        typedef Item value_type;
        
        binary_tree_node( const Item& init_data = Item( ),
                          binary_tree_node* init_left = NULL,
                          binary_tree_node* init_right = NULL )
        {
            data_field = init_data;
            left_field = init_left;
            right_field = init_right;
        }
        
        Item& data( ) { return data_field; }
        binary_tree_node*& left( ) { return left_field; }
        binary_tree_node*& right( ) { return right_field; }
        void set_data(const Item& new_data) { data_field = new_data; }
        void set_left(binary_tree_node* new_left) { left_field = new_left; }
        void set_right(binary_tree_node* new_right) { right_field = new_right; }
        
        const Item& data( ) const { return data_field; }
        const binary_tree_node* left( ) const { return left_field; }
        const binary_tree_node* right( ) const { return right_field; }
        bool is_leaf( ) const { return (left_field == NULL) && (right_field == NULL); }
        
    private:
        Item data_field; // data field of a node
        binary_tree_node *left_field;  // pointer to the left sub-tree
        binary_tree_node *right_field; // pointer to the right sub-tree
    };
    
    
#pragma mark - Non-member Function Declarations
    
    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr);
    
    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr);
    
    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr);
    
    template <class Item, class SizeType>
    void print(binary_tree_node<Item>* node_ptr, SizeType depth);
    
    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr);
    
    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr);
    
    template <class Item>
    std::size_t tree_size(const binary_tree_node<Item>* node_ptr);
}



#pragma mark - Implementation

namespace coen79_lab9
{
    
    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            inorder(f, node_ptr->left());
            f(node_ptr->data());
            inorder(f, node_ptr->right());
            
        }
    }
    
    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr)
    {
        postorder(f, node_ptr->left());
        postorder(f, node_ptr->right());
        f(node_ptr->data());
    }
    
    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr)
    {
        f(node_ptr->data());
        preorder(f,node_ptr->left());
        preorder(f,node_ptr->right());
    }
    
    template <class Item, class SizeType>
    void print(binary_tree_node<Item>* node_ptr, SizeType depth)
    {
        if (node_ptr != NULL)
        {
            print(node_ptr->right( ), depth+1);
            std::cout << std::setw(4*depth) << ""; // Indent 4*depth spaces.
            std::cout << node_ptr->data( ) << std::endl;
            print(node_ptr->left( ),  depth+1);
        }
    }
    
    
    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr)
    {
        binary_tree_node<Item>* child;
        if (root_ptr != NULL)
        {
            child = root_ptr->left( );
            tree_clear( child );
            delete root_ptr;
            root_ptr = NULL;
        }
    }
    
    
    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
    {
        binary_tree_node<Item> *l_ptr;
        binary_tree_node<Item> *r_ptr;
        
        if (root_ptr == NULL)
            return NULL;
        else
        {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return new binary_tree_node <Item> (root_ptr->data(), l_ptr, r_ptr);
        }
    }
    
    
    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* node_ptr)
    {
        if (node_ptr == NULL)
            return 0;
        else
            return tree_size(node_ptr->left()) + tree_size(node_ptr->right()) + 1;
    }
}

#endif
