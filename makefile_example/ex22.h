/*
Simple Linked List
*/

#ifndef LIST_H
#define LIST_H

typedef int itemType;

struct node
{
 itemType item;
 node* next;
};

class List
{
 public:

   List();
   /* 
   use:  copies a list
   pre:  lst is a pointer to an existing list
   post: the current list (self) is a copy of what lst points to
   */  
   List(List* lst);
   ~List();

   /*
   use: reports on the empty status of a list 
   pre: an instance of lists exists
   post: returns true if list is empty, false otherwise
   */ 
   bool IsEmpty();

   /*
   use: reports the length of a list
   pre: an instance of list exists
   post: returns length of the list 
   */
   int GetLength();

   /*
   use: adds an item to the head of the list
   pre: an instance of list exists
   post: newItem is at the head of the list 
   */
   void PutItemH(itemType newItem);

   /*
   use: reports the contents of the head of the list 
   pre: an instance of list exists and is not empty
   post: Returns the contents of the head of the list. 
   */
   itemType GetItemH();

   /*
   use: deletes the head of the list 
   pre: an instance of list exists and is not empty
   post: head of the list is deleted 
   */
   void DeleteItemH();

   /*
   use: displays the contents of the list on the screen 
   pre: an instance of list exists and is not empty
   post: contents of list nodes are displayed on subsequent lines 
   */
   void Print();
  

 private:
   int length; //length of the list
   node* head;   //point to the first node on the list 
};
#endif

