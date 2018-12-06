//Stack implemented using List and inheritance
#include <iostream>
using namespace std;

#include "ex24.h"

Stack::Stack() : List()
{}


Stack::Stack(Stack* stk): List(stk)
{}


void Stack::Push(itemType newItem)
{ 
 PutItemH(newItem);
}

void Stack::Pop()
{
 DeleteItemH();
}

itemType Stack::Peek()
{
 return GetItemH(); 
}


