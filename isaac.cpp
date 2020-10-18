#include "largeint.h"
#include <string>
#include <cstdlib>
#include <sstream>

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is the constructor for the LargeInt class. It can either take an
* unsigned value or set the LargeInt value to zero, but will create the 
* framework for a LargeInt. It will first change the unsigned value into 
* LargeInt format and then add 10000 nodes after it to create an available space
* list. A marker is then set at the end of the LargeInt as -1, to mark the end 
* of the used space. Tailptr is set just before it on the last used node. The 
* available space list is doubly linked and has nullptr as either end.
*
* @param[in] value - An unsigned integer value that the list can be input by the
* user to initialize the LargeInt
* 
* @returns none
*******************************************************************************/
Polynomial::Polynomial( unsigned value )
{
	//Declaring variables
    int remainder = 0;
    int power = 0;
    int i = 0;
    ListNode *curr;
    ListNode *previous;


    //Initialize all pointers (curr, previous, head) to a new node
    curr = previous = head = new ( nothrow ) struct ListNode;
    head -> prev = nullptr;

    //Put each digit in the input value into 
    while(( remainder == 0 ) && ( value != 0 ))
    {
    remainder = value % 10;
    value = value / 10;
    	if( remainder != 0 )
    	{
    	curr -> coeff = remainder;
    	curr -> power = power;
		}	
	power++;
	}
	//Put each digit of the input value into separate nodes
    while( value != 0 )
    {
    	remainder = value % 10;
    	value = value / 10;

    	//Only create a new node if the digit isn't zero
    	if( remainder != 0 )
    	{
    		curr = new ( nothrow ) struct ListNode;	
	    	previous -> next = curr;
    		curr -> coeff = remainder;
    		curr -> power = power;
	    	curr -> prev = previous;
			previous = curr;
			}

	//Increase the power of each node after every digit
    power++;
    }
	
	//When done, set tail to the end of the current node set
	tail = curr;

	//Create an available space list of 1000 nodes beyond the input number
	for( i=0 ; i<10000 ; i++ )
    {
    	curr = new ( nothrow ) struct ListNode;
    	curr -> coeff = 0;
    	previous -> next = curr;
    	curr -> prev = previous;
    	previous = curr;
    }
    //Make sure the end of the ASL points to nullptr
    curr -> next = nullptr;
    //Set the node after tailptr's coeff to -1 to mark the end of the LargeInt
    tail -> next -> coeff = -1;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the << operator. It takes in both an ostream 
* and a LargeInt and outputs another ostream to be used by the operator. The 
* function itself puts the LargeInt, digit by digit, into a stringstream. The 
* function adds zeroes in where they would normally be because they are not 
* stored in the LargeInt. It then takes stringstream and output it into a string
* and then outputs the string into the returned ostream. 
*
* @param[in] out - A reference to an ostream that will later be used for output
*
* @param[in] a - an input LargeInt that is meant to be output into ostream out
* 
* @returns ostream - A reference to an ostream that the overloaded operator will
* use in order to output the LargeInt
*******************************************************************************/
ostream & operator<<( ostream& out, const LargeInt& a )
{
	//Declare Variables
	ListNode * curr;
	ListNode * previous;
	int zeroes = 0;
	int i = 0;
	int counter = 0;
	ostringstream output;

	//Set curr and previous to tailptr of the input LargeInt
	curr = previous = a.tail;

	//Put first coeff into the output stringstream
	output << curr->coeff;
	
	//Put the digits of the LargeInt into the output stringstream
	while( (  curr->prev ) != nullptr )
	{
		curr = curr-> prev;

		//Check if any zeroes need to be inserted into the output stringstream
		zeroes = ( previous -> power - curr -> power ) - 1;
		while( zeroes > 0 )
		{	
			output << 0;
			zeroes--;
			counter++;
		}
		//Output current coeffient into output stringstream, iterate previous
		i = curr -> coeff;
		output << i;
		previous = curr;
	}

	//If the lowest digit of the LargeInt is not to the power of 0, insert all
	//needed zeroes at the end of the output stringstream
	if((a.head -> power) > 0 )
	{
		for( i=0 ; i<( a.head->power ) ; i++ )
		{
			output << 0;
		}
	}

	//Put the stringstream into a string and then into the ostream and return
	out << output.str();
	return out;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the == operator. It takes in two LargeInts to 
* be compared. It creates two pointers and sets them to the head of each 
* LargeInt. It then iterates through each, checking if they are equal at every
* step. It returns false if they are not equal and true if they are.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - true if the LargeInts are equal and false if they are not
*******************************************************************************/
bool operator==( const LargeInt& a, const LargeInt& b )
{
	//Declare Variables
	ListNode *curra;
	ListNode *currb;

	//Set pointers to tailptr
	curra = a.tail;
	currb = b.tail;

	//Iterate to the end of each LargeInt checking if the powers and coeff match
	while(( curra -> prev != nullptr ) && ( currb -> prev != nullptr ))
	{
		//If powers don't match, return false
		if( curra -> power != currb -> power )
		{
			return false;
		}
		//If coeffs don't match, return false
		if( curra -> coeff != currb -> coeff )
		{
			return false;
		}
		//iterate pointers
		curra = curra -> prev;
		currb = currb -> prev;
	}
	//Return true if no discrepancies are found
	return true;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the != operator. It uses the opposite output 
* of the == operator defined earlier in the program.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - false if the LargeInts are equal and true if they are not
*******************************************************************************/
bool operator!=( const LargeInt& a, const LargeInt& b )
{
	//Use the opposite output of the == operator
	if( a == b )
	{
		return false;
	}
	return true;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the < operator. It initially sets two pointers
* to tail and then iterates through them checking to see if a is less than b.
* It then returns a boolean as to whether or not that is true.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - true if a is less than b, false if it is not
*******************************************************************************/
bool operator<( const LargeInt& a, const LargeInt& b )
{
	//Declare variables
	ListNode *curra;
	ListNode *currb;

	//Set pointers to tailptr of each LargeInt
	curra = a.tail;
	currb = b.tail;

	//Iterate through both LargeInts and check coeff and powers
	while(( curra -> prev != nullptr ) && ( currb -> prev != nullptr ))
	{
		if( curra -> power < currb -> power )
		{
		return true;
		}
		if( curra -> coeff < currb -> coeff )
		{
		return true;
		}
	//Iterate pointers
	curra = curra->prev;
	currb = currb->prev;
	}
	return false;

}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the > operator. It initially sets two pointers
* to tail and then iterates through them checking to see if a is greater than b.
* It then returns a boolean as to whether or not that is true.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - true if a is greater than b, false if it is not
*******************************************************************************/
bool operator>( const LargeInt& a, const LargeInt& b )
{
	//User the opposite of both the == and < operators
	if( a == b )
	{
		return false;
	}
	if( a < b )
	{
		return false;
	}
	return true;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the <= operator. It initially sets two 
* pointers to tail and then iterates through them checking to see if a is less 
* than or equal to b. It then returns a boolean as to whether or not that is 
* true.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - true if a is less than or equal to b, false if it is not
*******************************************************************************/
bool operator<=( const LargeInt& a, const LargeInt& b )
{
	//Use the opposite of the  > operator
	if( a > b )
	{
	return false;
	}
	return true;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the >= operator. It initially sets two 
* pointers to tail and then iterates through them checking to see if a is 
* greater than or equal to b. It then returns a boolean as to whether or not 
* that is true.
*
* @param[in] a - an input LargeInt to be compared
*
* @param[in] b - an input LargeInt to be compared
* 
* @returns bool - true if a is greater than or equal to b, false if it is not
*******************************************************************************/
bool operator>=( const LargeInt& a, const LargeInt& b )
{
	//Use the opposite of the < operator
	if( a < b )
	{
		return false;
	}
	return true;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the + operator. It initially copies a into the
* output LargeInt, c. It then iterates through b, adding each digit to c. It 
* will directly add if c already has a node of the same power or it will create 
* a new node if c doesn't have one of that power. It then carries all of the 
* results over 9 into the next power up and returns the final result. 
*
* @param[in] a - an input LargeInt to be added
*
* @param[in] b - an input LargeInt to be added
* 
* @returns LargeInt - The result of the addition of a and b inside LargeInt c
*******************************************************************************/
const LargeInt& operator+( const LargeInt& a, const LargeInt& b )
{
	//Declare pointers and create LargeInt for return
	ListNode *curra;
	ListNode *currb;
	LargeInt *c = new ( nothrow ) LargeInt;
	ListNode *current;	
	ListNode *previous;
	ListNode *newnode;
	bool bwaslarger = false;
	
	//Set pointers to head
	curra = a.head;
	currb = b.head;

	//Initial
	curra = a.head;
	current = c -> head;

	//Make c the same as a
	while( curra -> coeff != -1 )
	{
		current -> coeff = curra -> coeff;
		current -> power = curra -> power;
		curra = curra -> next;
		current = current -> next;
	}
	c -> tail = current -> prev;
	current -> coeff = -1;

	//ser current and previous to head of c
	current = c -> head;
	previous = c -> head;

	//Traverse through b and add to c
	while( currb -> coeff != -1 )
	{
		//Make sure that current is at a larger or equiavlent power to b
		while(( current -> power < currb -> power ) && 
			  ( current -> coeff != -1 ))
		{
			current = current -> next;
		}			
		
		//If the powers are equal, it is simple addition
		if( current -> power == currb -> power )
		{
			current -> coeff = current -> coeff + currb -> coeff;
		}
		//If current is larger than b, create a new node in c and fill it with b
		if( current -> power > currb -> power )
		{
			newnode = new (nothrow) ListNode;
			current -> prev -> next = newnode;
			newnode -> prev = current -> prev;
			current -> prev = newnode;
			newnode -> next = current;
			newnode -> power = currb -> power;
			newnode -> coeff = currb -> coeff;
		}
		//If we have hit the end of c, fill all nodes after the end of c with b
		while(( current -> next -> coeff == -1 ) && ( currb -> coeff != -1 ))
		{
			current = current -> next;
			current -> power = currb -> power;
			current -> coeff = currb -> coeff;
			current -> next -> coeff = -1;
			c -> tail = current;
			bwaslarger = true;
			currb = currb -> next;
		}
		//Iterate to the next digit of b
		if( bwaslarger == false )
		{
			currb = currb -> next;
		}
	}
	//If the original numbers were equal, get rid of extra b digit copy
	if( a.tail -> power == b.tail -> power )
	{
		c -> tail -> coeff = -1;
		c -> tail = c -> tail -> prev;
	}


	//Take all digits above 9 and carry their extra 1 to the next power up
	//Set current to the head of c
	current = c -> head;
	//Iterate through c while we haven't hit the end
	while(( current -> coeff != -1 ) && ( current -> coeff != 0 ))
	{
		//If the digit is greater than 9, perform the carry operation
		if( current -> coeff > 9 )
		{
			//Take the modulus fo the current coeff and replace it
			current -> coeff = current -> coeff % 10;
			//If there is already a node for the next digit directly next, carry
			if(( current -> next -> power = current -> power + 1 ) || 
			   ( current -> next -> coeff == -1 ))
			{
				//If carrying to the marker node, use it and mark next node
				if( current -> next -> coeff == -1 )
				{
					current -> next -> power = current -> power + 1;
					current -> next -> next -> coeff = -1;
					c->tail = current -> next;
					current -> next -> coeff = current -> next -> coeff + 1;
				}
				//Add one to the next node
				current -> next -> coeff = current -> next -> coeff + 1;
				
			}
			//If the next power is more than one greater, create a new node
			if( current -> next -> power > current -> power + 1 )
			{
			newnode = new ( nothrow ) ListNode;
			current -> next -> prev = newnode;
			newnode -> next = current -> next;
			current -> next = newnode;
			newnode -> prev = current;
			newnode -> power = current -> power + 1;
			newnode -> coeff = 1;
			}

		}
		//Iterate to the next digit
		current = current -> next;
	}

	return *c;
}

/***************************************************************************//**
* @author Isaac Egermier
*
* @par Description:
* This function is an overload of the += operator. It takes in a LargeInt b and 
* adds it to *this and places the result into *this. It uses the both the 
* overloaded = operator and overloaded + operator.
*
* @param[in] b - an input LargeInt to be added
* 
* @returns LargeInt - The result of the addition of b and *this.
*******************************************************************************/
const LargeInt& LargeInt::operator+=( const LargeInt& b )
{
	//Use equality and addition operators
	*this = *this + b;
	return *this;
}
