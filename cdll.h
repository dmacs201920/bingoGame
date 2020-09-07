/*
 * This is and implementaion of Generalized Circular Double Linked List.
 * This was written by Sai Aravind S.V.
 * The data is taken to be the address of the actual data.
 * The user is supposed to implement ways of comparing, copying, displaying.
 */
#include<stdlib.h>
#include<stdio.h>
struct node
{
    void *d;
    struct node *n,*p;
};
		/*
		 * d for data
		 * n for next node
		 * p for previous node
		 */
typedef struct node node;
typedef struct
{
    node *h;
    int size;
    int (*cmp)(void* data1,void* data2);
    void (*disp)(void* data);
    void (*cpy)(void* Destination,void* Source);
}cdll;		// Circular Double Linked List
		/*
		 * h	- Head
		 * size	- Size of the data in bytes
		 * cmp	- Compare function for data
		 * disp	- Display function for data
		 * cpy	- Copy function for data
		 */

void init(cdll* LIST,int size_of_data,int(*compare)(void*,void*),void(*display)(void*),void(*cpy)(void*,void*));	
// Initializes the list.
void display(cdll List,char *inbetween);	// Puts inbetween string after every data's display.
node* createnode(void *data,void(*cpy)(void* Destinaiotn,void* Source),int size);
int insertl(cdll* list,void *data,int pos);
		/*
		 * pos<0 => insert at end
		 * pos=0 => insert at begining
		 * pos>	length of list => insert at end
		 * pos>0 but < length of the list => insert before pos
		 * position, position is counted from 0.
		 */
void delnode(cdll* LIST,int POSITION);	//Counting starts from 0.
void freecdll(cdll list);	// Destroys the list
void* pop(cdll *LIST);
void* topvalue(cdll LIST);
void* frontvalue(cdll LIST);
void* deq(cdll *LIST);
int insorder(cdll *LIST,void* data,char order);
	/*
	 * order='a' or 'A' => Ascending order
	 * order='d' or 'D' => desending order
	 */
void rotatecdll(cdll *LIST,int DIRECTION_AND_MAGNITUDE);
	/*The second argument:
	 * if >0 the rotation will be in clock-wise
	 * direction.
	 * if <0 the rotaion will be in anti-clock-wise
	 * direction.
	 * the list rotates by magnitude number of times.
	 */
#define push(l,data) insert(l,data,0)
#define enq(l,data) insert(l,data,0)
