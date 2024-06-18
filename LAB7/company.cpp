#include <cassert>
#include "company.h"
#include "node.h"


#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        this -> company_name = company_name;
        this -> head_ptr = NULL;
        this -> tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        list_copy(src.head_ptr, head_ptr, tail_ptr);
        company_name = src.company_name;
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        if (this == &src) return *this;
        list_clear(this -> head_ptr);
        list_copy(src.head_ptr, this -> head_ptr, this -> tail_ptr);
        company_name = src.company_name;
        return *this;

    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            head_ptr = new node(product_name, price, NULL);
            tail_ptr = head_ptr;
        }
        else {
            node* cursor = head_ptr;
            while (cursor != NULL) {
                if(cursor -> getName() == product_name) {
                    return false;
                }
                cursor = cursor -> getLink();
            }
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }
    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        node* cursor = list_search(head_ptr, product_name);
        if(cursor != NULL) {
            cursor ->setName(head_ptr -> getName());
            cursor ->setPrice(head_ptr -> getPrice());
            list_head_remove(head_ptr);
            return true;
        }
        return false;
    }
    
    
}
