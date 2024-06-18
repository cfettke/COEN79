#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>


namespace coen79_lab7
{
    class node {
        
    public:
        node(const std::string& itemName = "", const float& newPrice = -1, node* nextNode = NULL);
        
        void setName(const std::string& product_name);
        void setPrice(const float& newPrice);
        void setLink(node* newLink);
        
        const node *getLink() const;
        node *getLink();
        std::string getName() const;
        float getPrice() const;
        
    private:
        std::string name; // Name of the product
        float price; // Price of the product
        node *link; // Link to the next product
    };
    
    
    void list_clear(node*& head_ptr);
    void list_init(node*& head_ptr, node*& tail_ptr, const std::string& newName, const float& newPrice);
    void list_tail_insert(node*& tail_ptr, const std::string& newName, const float& newPrice);
    void list_copy(const node* old_head, node*& new_head, node*& new_tail);
    void list_print(node* head_ptr);
    bool list_contains_item(node* head_ptr, const std::string& name);
    void list_head_remove(node*& head_ptr);
    node* list_search(node* head_ptr, const std::string& name);
    const node* list_search (const node* head_ptr, const std::string& name);

}

#endif

