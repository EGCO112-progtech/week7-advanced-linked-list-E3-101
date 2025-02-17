
// self-referential structure
#include <string.h>
struct Node {
   struct Node *PPtr;
   int ID; // each listNode contains a character
   char Name[30];
   struct Node *nextPtr; // pointer to next node
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

int data=0;

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value, char []);
void printList( LLPtr currentPtr );
void printListRe( LLPtr currentPtr );
void instructions( void );
void clearall ( LLPtr *sPtr );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value, char Name[])
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->ID = value; // place value in node
      strcpy(newPtr->Name,Name);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->PPtr = NULL; // node does not link to another node

       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && value > currentPtr->ID ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
      
         *sPtr = newPtr;
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->PPtr = previousPtr;
          
         newPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->PPtr = newPtr;
         
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
   data+=1;
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->ID ) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr) (*sPtr)->PPtr==NULL;
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else {
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->ID != value ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         currentPtr=currentPtr->nextPtr;
         previousPtr->nextPtr = currentPtr;
         if (currentPtr) currentPtr->PPtr=previousPtr;
         
         free( tempPtr );
         return value;
      } // end if
   } // end else
   data-=1;
   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s -->", currentPtr->ID, currentPtr->Name);
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "%d %s -->NULL\n",currentPtr->ID, currentPtr->Name);
       

   } // end else
}

   void printListRe( LLPtr currentPtr )
   {
      int size=0;
      // if list is empty
      if ( isEmpty( currentPtr ) ) {
         puts( "List is empty.\n" );
      } // end if
      else {
         //puts( "The list in reverse order is:" );
   
         // while not the end of the list
         while ( currentPtr->nextPtr!= NULL ) {
            currentPtr = currentPtr->nextPtr;
            size++;
         } // end while
         
         while ( size>0 ) {
            printf( "%d %s -->", currentPtr->ID, currentPtr->Name );
            if (currentPtr->PPtr) currentPtr = currentPtr->PPtr;
            size--;
         }
         printf( "%d %s -->NULL",currentPtr->ID, currentPtr->Name );
         printf("\n");
      }
   
   } // end else

   void clearall( LLPtr *sPtr ){
      int i;
      for (i=0;i<data;i++) {
         LLPtr tempPtr=*sPtr;
         int item=tempPtr->ID;
      if (deletes(&tempPtr,item) ) { // remove item
         printf( "%d deleted.\n", item );
         if((*sPtr)->nextPtr) *sPtr = (*sPtr)->nextPtr;
         if(*sPtr) (*sPtr)->PPtr==NULL;
      }
   }

} // end function printList

