#ifndef COEN_79_SEQUENCE_H
#define COEN_79_SEQUENCE_H
#include <cstdlib> // Provides size_t
#include "node.h" // Provides node class
namespace coen79_lab6
{
class sequence
{
public:
// TYPEDEFS and MEMBER CONSTANTS
 typedef double value_type;
 typedef std::size_t size_type;
// // CONSTRUCTORS and DESTRUCTOR
 sequence( );
 sequence(const sequence& source);
 ~sequence( );
 // MODIFICATION MEMBER FUNCTIONS
 void start( );
 void end();
 void advance( );
 void insert(const value_type& entry);
 void attach(const value_type& entry);
 void operator =(const sequence& source);
 void remove_current( );
 // CONSTANT MEMBER FUNCTIONS
 size_type size( ) const;
 bool is_item( ) const;
 value_type current( ) const;
 private:
 node *head_ptr;
 node *tail_ptr;
 node *cursor;
 node *precursor;
 size_type many_nodes;
 void init();
 };
 }
 #endif

