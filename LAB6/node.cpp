#include "node.h"
#include <iostream>
#include <cassert> // Provides assert
#include <cstdlib> // Provides NULL and size_t
using namespace std;
namespace coen79_lab6 {
        size_t list_length(const node *head_ptr) {
                const node *cursor;
                size_t answer;
                answer = 0;
                for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
                        ++answer;
                return answer;
        }
        void list_head_insert(node *&head_ptr, const node::value_type &entry) { head_ptr = new node(entry, head_ptr); }
        void list_insert(node *previous_ptr, const node::value_type &entry) {
                node *insert_ptr;
                insert_ptr = new node(entry, previous_ptr->link());
                previous_ptr->set_link(insert_ptr);
        }
        node *list_search(node *head_ptr, const node::value_type &target) {
                node *cursor;
                for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
                        if (target == cursor->data())
                                return cursor;
                return NULL;
        }
        const node *list_search(const node *head_ptr, const node::value_type &target) {
                const node *cursor;
                for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
                        if (target == cursor->data())
                                return cursor;
                return NULL;
        }
        node *list_locate(node *head_ptr, size_t position) {
                node *cursor;
                size_t i;
                assert(0 < position);
                cursor = head_ptr;
                for (i = 1; (i < position) && (cursor != NULL); i++)
                        cursor = cursor->link();
                return cursor;
        }
        const node *list_locate(const node *head_ptr, size_t position) {
                const node *cursor;
                size_t i;
                assert(0 < position);
                cursor = head_ptr;
                for (i = 1; (i < position) && (cursor != NULL); i++)
                        cursor = cursor->link();
                return cursor;
        }
        void list_head_remove(node *&head_ptr) {
                node *remove_ptr;
                remove_ptr = head_ptr;
                head_ptr = head_ptr->link();
                delete remove_ptr;
        }
        void list_remove(node *previous_ptr) {
                node *remove_ptr;
                remove_ptr = previous_ptr->link();
                previous_ptr->set_link(remove_ptr->link());
                delete remove_ptr;
        }
        void list_clear(node *&head_ptr) {
                while (head_ptr != NULL)
                        list_head_remove(head_ptr);
        }
        void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr) {
                head_ptr = NULL;
                tail_ptr = NULL;

                if (source_ptr == NULL)
                        return;
                list_head_insert(head_ptr, source_ptr->data());
                tail_ptr = head_ptr;
                source_ptr = source_ptr->link();
                while (source_ptr != NULL) {
                        list_insert(tail_ptr, source_ptr->data());
                        tail_ptr = tail_ptr->link();
                        source_ptr = source_ptr->link();
                }
        }





        void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		head_ptr = NULL;
		tail_ptr = NULL;
		
		if (start_ptr == end_ptr) return;
 		else if (start_ptr == NULL) return;
 		else {
 			list_head_insert(head_ptr, start_ptr->data());
			tail_ptr = head_ptr;
			
 			start_ptr = start_ptr->link();
			for (start_ptr; 
				start_ptr != NULL && start_ptr != end_ptr; 
				start_ptr=start_ptr->link()) {
				

				list_insert(tail_ptr, start_ptr->data());
				tail_ptr = tail_ptr->link();
			}
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		
		size_t total = 0;
		
 		const node* cursor;
		
		cursor = list_search(head_ptr, target);
		while (cursor != NULL) {
			cursor = list_search(cursor->link(), target);
			total++;
		}
		return total;
	}
    
	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
 				assert((position > 0) && (position <= list_length(head_ptr) + 1));
		if(position == 1)
		{
			node* addedNode = new node(entry, head_ptr);
			head_ptr = addedNode;
		}
		else
		{
			node* precursor = head_ptr;
			node* cursor = list_locate(head_ptr, position);
			while(precursor->link() != cursor)
			{
				precursor = precursor->link();
			}
			node* addedNode = new node(entry,cursor);
			precursor->set_link(addedNode);
		}
	}
    
	node::value_type list_remove_at(node*& head_ptr, size_t position) {
	
		if (position > 0 && position <= list_length(head_ptr)+1) {
			 return NULL;
		}
		if (position > 1) list_remove(list_locate(head_ptr, position-1));
		else list_head_remove(head_ptr);
		return head_ptr->data();
			
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
 		node* rethead = NULL;
		node* rettail = NULL;
		node* startnode = list_locate(head_ptr, start);
		node* finishnode = list_locate(head_ptr, finish+1);

		list_piece(startnode, finishnode, rethead, rettail);
		return rethead;

	}
    
	void list_print (const node* head_ptr) {
 		const node* cursor = head_ptr;
		while(cursor != NULL) {
			cout << cursor->data() << ", ";
			cursor = cursor->link();
		}
		cout << endl;
	}

    void list_remove_dups(node* head_ptr) {
		node* check;
		node* cursor;

		cursor = head_ptr;
		
		while (cursor != NULL && cursor->link() != NULL) {
			check = cursor;
			while (check->link() != NULL) {
				if(cursor->data() == check->link()->data()) list_remove(check);
				else check = check->link();
			}
			cursor = cursor->link();
		}
	}
    node* list_detect_loop (node* head_ptr) {
 		if (head_ptr == NULL) return NULL;	
		
		node* cursor = head_ptr;
		node* doubleMoveCursor = head_ptr;

		while (doubleMoveCursor != NULL && doubleMoveCursor->link() != NULL) {
			doubleMoveCursor = doubleMoveCursor->link()->link();
			cursor = cursor->link();

			if (doubleMoveCursor == cursor) break; // save position
		}
		
		if (doubleMoveCursor == NULL || doubleMoveCursor->link() == NULL) return NULL; // no loop found
		
		cursor = head_ptr;
		while (doubleMoveCursor != cursor) {
			doubleMoveCursor = doubleMoveCursor->link();
			cursor = cursor->link();
		}
		return cursor;
	}   
} 

