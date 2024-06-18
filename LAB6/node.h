#ifndef COEN_79_NODE_H
#define COEN_79_NODE_H
#include <cstdlib> // Provides size_t and NULL
namespace coen79_lab6 {
class node {
	public:
	//typedef
      	typedef double value_type;
	//constructor
	node(const value_type &init_data = value_type(), node *init_link = NULL) {
                data_field = init_data;
                link_field = init_link;
        }
	//member function to set data and link feild
        void set_data(const value_type &new_data) { data_field = new_data; }
        void set_link(node *new_link) { link_field = new_link; }
        //retrieves data
	value_type data() const { return data_field; }
	//member function to retrieve link
        const node *link() const { return link_field; }
        node *link() { return link_field; }

        private:
        value_type data_field;
        node *link_field;
};
//functions for linked list toolkit
std::size_t list_length(const node *head_ptr);
void list_head_insert(node *&head_ptr, const node::value_type &entry);
void list_insert(node *previous_ptr, const node::value_type &entry);
node *list_search(node *head_ptr, const node::value_type &target);
const node *list_search(const node *head_ptr, const node::value_type &target);
node *list_locate(node *head_ptr, std::size_t position);
const node *list_locate(const node *head_ptr, std::size_t position);
void list_head_remove(node *&head_ptr);
void list_remove(node *previous_ptr);
void list_clear(node *&head_ptr);
void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr);
//implement
void list_piece(node *start_ptr, node *end_ptr, node *&head_ptr, node *&tail_ptr);
size_t list_occurrences(node *head_ptr, const node::value_type &target);
void list_insert_at(node *&head_ptr, const node::value_type &entry, size_t position);
node::value_type list_remove_at(node *&head_ptr, size_t position);
node *list_copy_segment(node *head_ptr, size_t start, size_t finish);
void list_print(const node *head_ptr);
void list_remove_dups(node *head_ptr);
node *list_detect_loop(node *head_ptr);
} // namespace coen79_lab6
#endif
