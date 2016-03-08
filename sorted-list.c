#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sorted-list.h"
#include <string.h>
#include "tokenizer.h"
#include "readprocess.h"



int compareStrings(void *p1, void *p2)
 {
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int compareInts(void *a, void *b)
{
	int i = *(int*)a;
	int j = *(int*)b;
	
	return i - j;
}


SortedListPtr SLCreate(CompareFuncT cf)
{       
        SortedListPtr sl = malloc(sizeof(struct SortedList));
        
        sl->compare = cf;
        
        sl->bigHead = NULL;

        return sl;         
} 
//*-**==*=--=-*----=*-*=--*-*-=-*-=-*-*=--*-=-*=--*-=-*-=-=-*-*=--*-=-*-=-*-=-*-*=--*-=-=-=-=-=-=-=-=-=-*-=--*-=-

/*
void SLDestroy(SortedListPtr list)
{
    Node* nextPtr;
    if(list != NULL)
    {
        list->curr = list->head;
        
        while(list->curr != NULL)
        {
            nextPtr = list->curr->next;
            
            if(list->destroy)
            {
                list->destroy(list->curr->data);
            }
            
            free(list->curr);
            list->curr = nextPtr;
        }
        free(list);
    }
}
*/

//*-**==*=--=-*----=*-*=--*-*-=-*-=-*-*=--*-=-*=--*-=-*-=-=-*-*=--*-=-*-=-*-=-*-*=--*-=-=-=-=-=-=-=-=-=-*-=--*-=-
int SLCheck(SortedListPtr list,char* word, char* pathName)
{	
	
	Token* bigNode = list->bigHead;
	
	if(bigNode == NULL)	//list is empty no comparisons
		return 0;			
		
	
	while(bigNode !=  NULL)
	{
		//IF Words MATCH AND PATH--Increments counter 
		if( strcmp(bigNode->data,word) == 0 &&  strcmp(bigNode->littleHead->filePathName,pathName) == 0) //(bigNode->data == word) && (bigNode->littleHead->filePathName == pathName)) 
		{	
			bigNode->littleHead->count++;
			return 1;
		}
		//if words are the same but filePaths different..
		
		//char* path = malloc(strlen(pathName)+1);
		//strcpy(path, pathName);			
		
		//int x = strcmp(bigNode->data,word);
		//int y = strcmp(bigNode->littleHead->filePathName,pathName);
		
		//printf("%s\n", bigNode->littleHead->filePathName);
		//printf("%s\n",pathName);

		if( (strcmp(bigNode->data,word) == 0) &&  (strcmp(bigNode->littleHead->filePathName,pathName) != 0) )
		{
			//printf("\n\nthese should not match\n");
			//printf("%s\t", bigNode->littleHead->filePathName);
			//printf("%s\n\n",path);
			
			PathOccurance* sideNode = malloc(sizeof(struct PathOccurance));	
			PathOccurance* tinyCurrent = bigNode->littleHead;
			
			while(tinyCurrent->next != NULL)
			{	
				tinyCurrent = tinyCurrent->next;
			}

			tinyCurrent->next = sideNode;
			sideNode->prev = tinyCurrent;	
			
			sideNode->filePathName = pathName;
			sideNode->count = 1;
			sideNode->next = NULL;
			return 1;
		}
		//add words? what if the words are not the same
		
		if(strcmp(bigNode->data,word) != 0) //if the words dont match keep going
			bigNode = bigNode->next;
	}
	
	return 0;
}


int SLInsert(SortedListPtr list, void *newObj,char* nameOfPath)
{
	
    if(list == NULL)
    {
        printf("NUll List Cannot ADD ELEMENTS!");    
        return 0;
    }
     	
	Token* tokenNode = malloc(sizeof(struct Token));				//creates token node
	
	PathOccurance* link = malloc(sizeof(struct PathOccurance));		//creates sidechick Node
	
	tokenNode->data = newObj;
	tokenNode->next = NULL;
	tokenNode->prev = NULL;
		
	link->filePathName = NULL;
	link->count = 0;
	link->next = NULL;
	link->prev = NULL;
	
	tokenNode->littleHead = link;  //now the tokenNode->littleHead 
	PathOccurance* node = tokenNode->littleHead;
	
    if(list->bigHead == NULL)			//TestCase 1
    {
		tokenNode->next = NULL;
		list->bigHead = tokenNode;
		tokenNode->prev = list->bigHead;
		
		//added the first side node and initialize it	
		node->count = 1;
		node->filePathName = nameOfPath;
		node->next = NULL;		
		//call function to pass current Node inorder to build off of it...filepathname count for now;
		//int initialize = 0;
		

	//SLInsertSideNode(tinyHead, link, 1, nameOfPath);
		
		// pass tokenNode->littleHead(head of list),
/*<-----------------------------------------------------------------------------------
		tokenNode->littleHead->count = 234;
		tokenNode->littleHead->filePathName = "iniiii";
		tokenNode->littleHead->next = NULL;
		tokenNode->littleHead->prev = tokenNode->littleHead;
		//sets first node
							
		PathOccurance*temp = tokenNode->littleHead;
		PathOccurance* link = malloc(sizeof(struct PathOccurance));
		link->count = 1;
		link->filePathName = "rawr";
		
		temp->next = link;
		link->prev = temp;
		link->next = NULL;
				
		PathOccurance* temp2 = tokenNode->littleHead;		
		while(temp2 != NULL)
		{
			printf("%s\t%d\n", temp2->filePathName, temp2->count);
			
			
			temp2 = temp2->next;
		}
		printf("-----------------");
*///<--------------------------------------------------------------------------------		
	}
	else
	{	
		
		Token* current = list->bigHead;

		if( strcmp(tokenNode->data, current->data) < 0) //Adds at HEAD
		{
			list->bigHead = tokenNode;
			tokenNode->prev = list->bigHead;
			tokenNode->next = current;
			current->prev = tokenNode;
			
		//,-------------------------------	
			tokenNode->littleHead->count = 1;
			tokenNode->littleHead->filePathName = nameOfPath;
			tokenNode->littleHead->next = NULL;			
		//--------------------------------							
		}
		else
		{
			
			Token* temp = current;
			while(current->next != NULL && (strcmp(tokenNode->data ,current->data) > 0 ||  strcmp(tokenNode->data ,current->data) < 0))
			{
				
				if(strcmp(tokenNode->data ,current->data) < 0)
					break;
				else
				{		
					temp->prev = current; //follows alog a prev pointer to add in the middle
					current = current->next;
				}
			}
				
				if(strcmp(tokenNode->data ,current->data) > 0)
				{	
					if(current->next == NULL)//ADDS at END/NULL
					{
						current->next = tokenNode;
						tokenNode->prev = current;
						tokenNode->next = NULL;
						
		//,-------------------------------	
			tokenNode->littleHead->count = 1;
			tokenNode->littleHead->filePathName = nameOfPath;
			tokenNode->littleHead->next = NULL;							
		//--------------------------------							
							
					}
					else
					{
						temp->next = tokenNode;
						tokenNode->prev = temp;
				
						tokenNode->next = current;
						current->prev = tokenNode;
				//,-------------------------------	
			tokenNode->littleHead->count = 1;
			tokenNode->littleHead->filePathName = nameOfPath;
			tokenNode->littleHead->next = NULL;							
		//--------------------------------					
							
					}
				}
				if(strcmp(tokenNode->data ,current->data) < 0)
				{
					Token *temp2 = current->prev; 
					temp2->next = tokenNode;
					tokenNode->prev = temp2;
					tokenNode->next = current;
					current->prev = tokenNode;
					//,-------------------------------	
			tokenNode->littleHead->count = 1;
			tokenNode->littleHead->filePathName = nameOfPath;
			tokenNode->littleHead->next = NULL;							
		//--------------------------------			
												
				}
		}	
	}
    return 0;   
}

//*-**==*=--=-*----=*-*=--*-*-=-*-=-*-*=--*-=-*=--*-=-*-=-=-*-*=--*-=-*-=-*-=-*-*=--*-=-=-=-=-=-=-=-=-=-*-=--*-=-

						//tokeNode->littlehead = link
int SLInsertSideNode(PathOccurance* head, int count, char *pathName)
{	//******************DESCENDING ORDER**********

	
	
//	node->count = count;
//	node->filePathName = pathName;
/*	
	if(node == NULL)
	{	
		node->count = count;
		node->filePathName = pathName;
		node->next = NULL;
	}
	PathOccurance* temp = node;
	
	
	
	while(temp != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
	node->prev = node;
*/
	

	return 0;
}

//possible seperate function to increment count only !!!!










/*
int SLRemove(SortedListPtr list, void *newObj)
{
   //checks if it is in head
   if(list->head->data   ==    newObj  )
   {
          list->head=list->head->next;          
   }              
   
   list->curr=list->head;

    while(list->curr != NULL)
        {
            if(list->curr->data    ==    newObj      )
               {
                     list->curr = list->curr->next; 
                     list->prev->next=list->curr;
                     return 0;
                }                                                           
            list->prev = list->curr;
            list->curr= list->curr->next;  
        }       
        list->numItems--;
        return 0;
}





// ********************WONT BE USING PAST THIS LINE ....NOT NECESSARY************************
 
SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	SortedListIteratorPtr mptr= malloc(sizeof(struct SortedListIterator));
	
	if(list == NULL)
    {
        printf("NUll List Cannot ADD ELEMENTS!");    
        return NULL;
    }
	
	mptr->ptr = list->head;
	mptr->count = list->numItems;
	mptr->tracker=0;
	return mptr;
}


void SLDestroyIterator(SortedListIteratorPtr iter)
{
	
	free(iter);	

	
}

void* SLNextItem(SortedListIteratorPtr iter)
{
	if(iter->tracker== iter->count)
	{
		printf("Warrning: End Of The List");
		return iter->ptr;
	}
		
	iter->ptr=iter->ptr->next;
	iter->tracker++;
	return 	iter->ptr;
}

void* SLGetItem(SortedListIteratorPtr iter)
{	

	if(iter->tracker == iter->count)
		return iter->ptr;
	else if(iter->tracker > iter->count)
		return NULL;
	else
		return iter->ptr;
}

*/
