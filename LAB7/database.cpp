#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        this -> used_slots = src.used_slots;
        this -> aloc_slots = src.aloc_slots;
        this -> company_array = new company[aloc_slots];
        for (int i = 0; i < used_slots; i++) {
            this -> company_array[i] = src.company_array[i];
        }

    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        if (this == &rhs) {
            return *this;
        }
        delete [] company_array;
        this -> used_slots = rhs.used_slots;
        this -> aloc_slots = rhs.aloc_slots;
        this -> company_array = new company[aloc_slots];
        for (int i = 0; i < used_slots; i++) {
            this -> company_array[i] = rhs.company_array[i];
        }

        return *this;
    }
    
    
    database::~database() {
        delete [] company_array;
        used_slots = 0;
        aloc_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Can't allocate less than we are using.
        
        company *new_array = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, new_array);
        delete [] company_array;
        company_array = new_array;
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        company new_company(entry);
        if (used_slots < aloc_slots) {
            company_array[used_slots] = new_company;
            ++used_slots;
        } else {
            reserve(used_slots + 1);
            company_array[used_slots] = new_company;
            ++used_slots;
        }
        return true;

    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type company_index = search_company(company);
        if(company_index == COMPANY_NOT_FOUND){
            return false;
        }
        return(company_array[company_index].insert(product_name, price));
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        }
        for (int i = used_slots; i > company_index + 1; i--) {
            company_array[i-1] = company_array[i];
        }
        --used_slots;
        return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type company_index = search_company(cName);
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        } 
        return company_array[company_index].erase(pName);
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        for(int i = 0; i < used_slots; i++) {
            if(company_array[i].get_name() == company) {
                return i;
            }
        }
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
