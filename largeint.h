/*
	***** largeint.h *****

Interface for a large integer class in C++.
Large integers are implemented using polynomials stored in linked lists.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms (PA#1)
Date:   Spring 2018

Note:
This file contains the class interfaces for a base Polynomial class and
an inherited LargeInt class. Do not change these class interfaces!
You must write the implementation, notably the Polynomial functions
copyPoly() and freePoly(), the LargeInt function compare(), and the
LargeInt operator functions +, *, >>, <<.
*/

//-----------------------------------------------------------------------------

// prevent multiple includes
#ifndef _LARGEINT_
#define _LARGEINT_

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------

// linked list node struct (fields are public by default)
struct ListNode
{
    int coeff, power;
    ListNode* next;
    ListNode* prev;     // for doubly-linked lists

    // constructor (makes node initialization easier)
    ListNode( int c = 0, int p = 0, ListNode* n = nullptr, ListNode* v = nullptr ) : coeff( c ), power( p ), next( n ), prev( v ) { }
};

//-----------------------------------------------------------------------------

// Polynomial class
class Polynomial
{
    protected:                 // private, except for inherited classes
        // data members
        ListNode* head = nullptr;               // pointer to start of list
        ListNode* tail = nullptr;               // pointer to end of list

        // member functions that are only called by other member functions
        void copyPoly( const Polynomial&  );
        void freePoly();

    public:                    // public class interface
        // constructor and destructor functions
        Polynomial( unsigned value = 0 );       // constructor: initialize Polynomial to int (default 0)
        Polynomial( const Polynomial&  );       // copy constructor: initialize Polynomial to Polynomial
        ~Polynomial();                          // destructor: deallocate linked list nodes

        // print() method (for debugging purposes)
        void print() const;
};

//-----------------------------------------------------------------------------

// inherit LargeInt class from Polynomial class
class LargeInt : public Polynomial
{
    private:                   // only accessible to member functions
        // compare function is called by relational operators
        int compare( const LargeInt& ) const;

    public:                    // class interface
        // constructors and destructors are inherited from Polynomial class,
        // but we need to pass arguments to Polynomial constructors:
        LargeInt( unsigned value = 0 ) : Polynomial( value ) { }
        LargeInt( const LargeInt& Q ) : Polynomial( Q ) { }

        // addition and multiplication operators: P + Q, P * Q
        // use friend functions to allow P + 43, 43 + P, etc.
        friend const LargeInt& operator+( const LargeInt&, const LargeInt& );
        friend const LargeInt& operator*( const LargeInt&, const LargeInt& );

        // assignment operators: P = Q, P += Q, P *= Q
        const LargeInt& operator=( const LargeInt& );
        const LargeInt& operator+=( const LargeInt& );
        const LargeInt& operator*=( const LargeInt& );

        // relational comparison operators: P == Q, P < Q, etc.
        // use friend functions to allow P == 43, 43 == P, etc.
        friend bool operator==( const LargeInt&, const LargeInt& );
        friend bool operator!=( const LargeInt&, const LargeInt& );
        friend bool operator<=( const LargeInt&, const LargeInt& );
        friend bool operator>=( const LargeInt&, const LargeInt& );
        friend bool operator<( const LargeInt&, const LargeInt& );
        friend bool operator>( const LargeInt&, const LargeInt& );

        // input/output operators: cin >> P, cout << P
        friend istream& operator>>( istream&, LargeInt& );
        friend ostream& operator<<( ostream&, const LargeInt& );
};

//-----------------------------------------------------------------------------

// end of the multiple includes preprocessor directive
#endif
