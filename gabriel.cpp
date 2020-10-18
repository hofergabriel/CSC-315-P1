#include "largeint.h"
#include <string>
#include <iostream>
using namespace std;



/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description:
* This function constructs a polynomial object which is a copy of the 
* object that is passed into the function. 
* 
* @param[in,out]    p - a polynomial object is passed by reference. 
* 
* @returns instance of a Polynomial object
*******************************************************************************/
Polynomial::Polynomial( const Polynomial& p ) 
{  
  copyPoly ( p );
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description: This destructor deletes all of the nodes in the list
*
*******************************************************************************/
Polynomial::~Polynomial () 
{
  // traverse the list and delete each node in the list
  freePoly();
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description: 
*  
* This function reads a string from the stream that was passed into the 
* function. We iterate through each character in the string, starting
* at the last character. We use a ListNode pointer to iterate through 
* the LargeInt object. At each node, we in the linked list, we 
* convert the value of the character in the string to a number
* and store it in the coefficeint field in the linked list node.
*
* @param[in,out]    in - an istream object
* @param[in,out]    num - the LargeInt object that we want to overwrite.
* 
* @returns the same istream object that was passed in
*
*******************************************************************************/
istream & operator >> ( istream & in, LargeInt & num ) 
{

  ListNode * v = num.head;
  ListNode * u = num.head;
  string str;
  int i, j;
  
  // read the string from the stream
  in >> str;
  
  // if the string that is entered is "0", do this
  if ( str == "0" ) 
  {		// 
    num.head -> coeff = 0;
    num.head -> power = 0;
    num.tail = num.head;
    num.head -> next -> coeff = -1;
    return in;
  }
  
  // if the string is not "0", then iterate through the list
  i = j = 0;
  while ( i < str.length () ) 
  {
    if ( str.at ( str.length () - i - 1 ) != '0' ) 
    {
      // type cast the character to a number
      u -> coeff = (int)(str.at ( str.length () - i - 1 ) - 48);
      u -> power = i;
      // we set the tail inside this loop so that
      // we can keep track of the last number in the list
      num.tail = u;
      u = u -> next;
    }
    // move to the next character in the string
    i += 1;
  }
  // set the end of the list
  u -> coeff = -1;
  return in;
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description: This function prints the Polynomial object. It is used
*   for debugging. 
*
*******************************************************************************/
void Polynomial::print() const 
{
  // we begin at head's next node in the list
  ListNode * u = head;

  // now we traverse the list, printing out elements
  while ( head != nullptr && u -> coeff != -1 ) 
  {
    cout << u-> power << ' ';
    cout << u->coeff << ' ' << endl;
    u = u -> next;
  }
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description: 
*
* This function uses two pointers to copy the data of one LargeInt object
* into another LargeInt object. 
* First, two pointers are set to the head of both lists. 
* These two pointers (a and b) are used to traverse the list.
* 
* Then, we synchronously move the two pointers to the next nodes in their 
* list, one node at a time. 
*
* At each step, we copy the coefficient and the power of current node 
* of the rhs (right hand side) LargeInt object into the
* coefficient and power of the *this object. 
* 
* @param[in,out]    num - a object of type LargeInt
* 
* @returns a reference to a LargeInt object
*******************************************************************************/
const LargeInt& LargeInt::operator=( const LargeInt & num ) 
{
  ListNode * a = num.head; // 
  ListNode * b = head;     // 
  while ( a -> coeff != -1 ) 
  {
    b -> coeff = a -> coeff;
    b -> power = a -> power;
    tail = b;
    a = a -> next;
    b = b -> next;
  }
  // mark the end of the list
  b -> coeff = -1;
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description:
*    This function multiplies two LargeInt objects. This algorithm is
*  O ( n ^ 3 ). 
*
* @param[in,out]    a - LargeInt object
* @param[in,out]    b - LargeInt object
* 
* @returns returns a reference to a LargeInt object which constains
*   the product of the two LargeInt parameters
*******************************************************************************/

const LargeInt& operator*( const LargeInt& a, const LargeInt& b) 
{

  // this is a pointer to the LargeInt object that we will return
  LargeInt * prod = new (nothrow) LargeInt;

  ListNode * lhs = a.head;
  ListNode * rhs = b.head;
  int i;

  // find the largest powers in both large integers;
  int degree_lhs, degree_rhs;

  // initialized degree of each Large Int to the power at the head
  degree_lhs = a.head -> power;
  degree_rhs = b.head -> power;

  // traverse both lists, searching for a coefficient of -1
  // When we find the position of -1 in one of the lists, we will know the 
  // size of the integer
  while ( lhs -> coeff != -1 ) 
  {
    degree_lhs = lhs -> power;
    lhs = lhs -> next;
  }
  while ( rhs -> coeff != -1 ) 
  {
    degree_rhs = rhs -> power;
    rhs = rhs -> next;
  }

  // calculate the maximum possible degree 
  // of the product of both integers
  int degree_product = degree_lhs + degree_rhs + 2; // change size to 1000, 

  // allocate an empty polynomial integer of 
  // with degree_product nodes or elements
  ListNode * prod_head = new (nothrow) struct ListNode;
  ListNode * current;
  ListNode * previous;
  current = previous = prod_head;

  prod_head -> coeff = 0;
  prod_head -> power = 0;


  // create about 1000 nodes of free space
  // mark the power fields of each node
  for ( i = 1; i < 1000 ; i += 1 ) 
  { 
    current = new (nothrow) struct ListNode;
    current -> next = nullptr;
    current -> prev = previous;
    current -> coeff = 0;
    current -> power = i;
    previous -> next = current;
    previous = current;
  }

  // initialize some pointers to head
  ListNode * lhs_curr;
  ListNode * lhs_prev;
  ListNode * rhs_curr;
  ListNode * rhs_prev;
  lhs_curr = lhs_prev = a.head;
  rhs_curr = rhs_prev = b.head;

  // 
  ListNode * prod_curr;
  ListNode * prod_prev;
  prod_curr = prod_prev = prod_head;
  
  while ( rhs_curr -> coeff != -1 ) 
  {

    lhs_curr = lhs_prev = a.head;
    while ( lhs_curr -> coeff != -1 ) 
    {

      int units_digit;
      int carry_digit;

      // always start at the head of the product list
      prod_curr = prod_prev = prod_head;

      // iterate to the place in the product list
      while ( prod_curr -> power != (rhs_curr -> power) + (lhs_curr -> power) ) 
      {
	prod_prev = prod_curr;
	prod_curr = prod_curr -> next;
      }

      // now we are in the right position 
      units_digit = ((lhs_curr -> coeff) * (rhs_curr -> coeff)) % 10;
      carry_digit = (((lhs_curr -> coeff) * (rhs_curr -> coeff)) / 10);

      // set the value of the coefficient in the product large integer
      prod_curr -> coeff += units_digit;

      carry_digit = (((lhs_curr -> coeff) * (rhs_curr -> coeff)) / 10) + (prod_curr -> coeff / 10);
      prod_curr -> coeff %= 10;

      // go to the next element in the product list
      prod_prev = prod_curr;
      prod_curr = prod_curr -> next;

      // carry the carry digit.
      // Also, break this loop if the carry value becomes zero
      while ( prod_curr != nullptr && (carry_digit != 0)) 
      {
	// add the carry digit to the coefficient 
	prod_curr -> coeff += carry_digit;
	carry_digit = prod_curr -> coeff / 10;
	prod_curr -> coeff %= 10;

	// iterate to the next node in the list
	prod_prev = prod_curr;
	prod_curr = prod_curr -> next;
      }
      
      lhs_prev = lhs_curr;
      lhs_curr = lhs_curr -> next;
    }

    rhs_prev = rhs_curr;
    rhs_curr = rhs_curr -> next;
  }

  prod -> tail = prod_prev;
  prod_curr -> coeff = -1;

  // count the number of nodes that are deleted
  // so that you can add to the end of the free space list
  // when you get to the end of the list. 
  current = prod_head -> next;
  previous = prod_head;
  int count_deleted = 0;
  while ( current-> coeff != -1 ) 
  {

    if ( current -> coeff == 0 ) 
    {
      previous -> next = current -> next;
      
      // delete the current node because it contains a zero
      delete current;
      
      current = previous -> next;
      current -> prev = previous;
      prod -> tail = current;

      // count the number of nodes that we delete from the list
      count_deleted += 1;
    }
    else 
    {
      prod -> tail = current;
      previous = current;
      current = current -> next;
    }
  }

  // 
  prod -> head = prod_head;
  
  // make sure that previous is the same for both branch statements. 
  // tail = previous;

  // iterate to the end of the list for the next 
  // step in this algorithm
  while ( current != nullptr ) 
  {
    previous = current;
    current = current -> next;
  }

  // add free space nodes to the list.
  // since we deleted the nodes with zero coefficient, we need to 
  // add nodes back into the list. 
  // we used the variable count_deleted to count the number of nodes
  // that we deleted. this is the number of nodes that we will 
  // add to the end of the list as free space. 
  while ( count_deleted > 0 ) 
  {
    current = new (nothrow) struct ListNode;
    current -> coeff = 0;
    current -> power = 0;
    current -> next = nullptr;
    current -> prev = previous;
    previous -> next = current;
    previous = current;
    current = current -> next;
    count_deleted -= 1;
  }


  // return the object
  return * prod;

}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description:
*    This function multiplies two LargeInt object and stores the result
*    in the *this object. It calls the * operator.
* 
* @param[in,out] - 
* 
* @returns 
*******************************************************************************/
const LargeInt& LargeInt::operator*=( const LargeInt& num ) 
{
  * this = (*this) * num;
  return * this;
}


/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description: 
* This function copies a polynomial object p and constructs a new object. 
* We iterate through Polynomial p, copying the data in each 
* node into the *this object.
* 
* @param[in,out]    p - a Polynomial object
* 
*******************************************************************************/
void Polynomial::copyPoly( const Polynomial& p  ) 
{


  int i = 0;
  ListNode * b;
  ListNode * c;
  ListNode * d;

  // create a list with 1000 nodes. 
  // first make the head node
  head = c = d = new (nothrow) ListNode;
  head -> coeff = 0;
  head -> power = 0;
  head -> next = nullptr;
  for ( i = 0; i < 1000; i += 1 ) 
  {
    d = new (nothrow) ListNode;
    c -> next = d;
    d -> prev = c;
    d -> coeff = 0;
    d -> power = 0;
    c = d;
  }

  // now copy the Polynomial object that was passed 
  b = p.head;
  c = d = head;
  while ( b -> coeff != -1 ) 
  {
    d -> coeff = b -> coeff;
    d -> power = b -> power;
    c = d;
    d = d -> next;
    b = b -> next;
  }

  // mark the end of the list
  d -> coeff = -1;
  tail = c;
 
}




/***************************************************************************//**
* @author Gabriel Hofer
*
* @par Description:
*    This function frees the polynomial object. We walk through 
* the list, deleting each node. 
*   
*******************************************************************************/
void Polynomial::freePoly() 
{

  ListNode * u = head;
  while ( head != nullptr ) 
  {
    u = head -> next;
    delete head;
    head = u;
  }
}












