#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "node.h"
#include "company.h"
#include <cassert>
#include <cmath>

#define COMPANY_NOT_FOUND  (-1)

namespace coen79_lab7
{
    class database {
        
    public:
        typedef std::size_t size_type;
        
        database(const size_type& initial_capacity = 2);
        database(const database &src);
        ~database();
        
        void reserve(size_type new_capacity);
        bool insert_company(const std::string& company_name);
        bool erase_company(const std::string& company_name);
        
        bool insert_item(const std::string &company_name, const std::string& product_name, const float& price);
        bool erase_item(const std::string &company_name, const std::string& product_name);
        
        
        void print_companies();
        bool print_items_by_company(const std::string& company_name);
        
        database& operator=(const database &rhs);
        
    private:
        company *company_array; // A pointer to a dynamic array of company objects
        size_type aloc_slots; // Number of slots in the stindex_array array
        size_type used_slots; // Number of used slots in the stindex_array array
        
        size_type search_company(const std::string& company_name);
    };
}
#endif
