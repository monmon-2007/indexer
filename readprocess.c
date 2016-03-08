#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include "readprocess.h"

int readprocess(char *rawr,SortedListPtr list)
{
	
	printf("Inside readprocess: %s\n\n", rawr);//prints twice with different path names 



//-=-=-=-=--=-=-=-READS ENTIRE FILE CONTENTS-=-=-=-=--=-=-=-=-=-=-=--=-
	FILE *myFile = fopen(rawr, "r");
	
   	if(myFile == NULL)
   {
        printf("File Doesn't Exist: ");
   
   }
   	
   fseek(myFile, 0, SEEK_END);
   long fsize = ftell(myFile);
   fseek(myFile, 0, SEEK_SET);

   char *string = malloc(fsize + 1);
   fread(string, fsize, 1, myFile);
 
						
   string[fsize] = 0;
 	
//-=-=-=-=--=-DUMPS CONTENTS INTO LIST=-=--=-=-=--=-=-=-=--==-=-=--=-=-=-=--=-

	//SortedListPtr list = SLCreate(compareStrings);
	
	TokenizerT *tk = TKCreate(string);	
	
	fclose(myFile);   
	free(string);
	
	char *tempToken;
		
	tempToken = TKGetNextToken(tk);
	
	if(tempToken == NULL)
	{	
		printf("BAD!!!!!!");
		exit(0);
	}
	while(tempToken != NULL)
	{	
		char* word = malloc(strlen(tempToken)+1);
		strcpy(word, tempToken);
		
				
		if(SLCheck(list, word, rawr) == 0)
		{	//add word
			SLInsert(list,word,rawr);
		}
		//else word has been found	
		
		tempToken = TKGetNextToken(tk);			
	}					
	resetFileCounter();
	//printf("Finishedprocessing file %s\n\n", rawr);
//>>>>>>>>>>>>>>>>>*************RESET STATIC STRARRY COUNTER AND READ MORE******************<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			
			
			
//=-=-=-=--=-=-=--=-=-=-=--=-=-=-=-=-=-=PRINTS WHATS INSIDE THE LIST=-=-=--=-=-=--=-=-=-=--=-=-=-=-=-=-=--=-=-=-=-=--=-=-=--=-=-=-=--=-=
/*		Token *current = list->bigHead;
		PathOccurance *sideNode;
		

		

		while(current != NULL)
		{
			printf("\n\"%s\":[\n",current->data); 
			sideNode = current->littleHead;
			while(sideNode != NULL)
			{
				printf("\t{\"%s\" : %d}\n",sideNode->filePathName, sideNode->count);
				sideNode = sideNode->next;
			}			
			printf("]}");
			
			current = current->next;
		}
		printf("\n");
		//IF THERE IS A SPACE IN MY FILE AFTER THE LAST NODE THEN IT LINES UP GOOD OTHER WISE... EXTRA LINE....just odd format NOT A BIG DEAL

//*/ //<<------------------------------------------------------------		
		return 0;
}

int outputAll(SortedListPtr list, FILE *ofp, char* pathName)
{
		Token *current = list->bigHead;
		PathOccurance *sideNode;
		
		fprintf(ofp, "{%s\n\t", pathName);
		while(current != NULL)
		{
			fprintf(ofp,"\t\n\"%s\":[\n",current->data); 
			sideNode = current->littleHead;
			
			while(sideNode != NULL)
			{
				fprintf(ofp,"\t{\"%s\" : %d}\n",sideNode->filePathName, sideNode->count);
				sideNode = sideNode->next;
			}			
			fprintf(ofp,"]}");
			
			current = current->next;
		}
		fprintf(ofp, "\n}");
		printf("\n");
		
		return 1;
		//IF THERE IS A SPACE IN MY FILE AFTER THE LAST NODE THEN IT LINES UP GOOD OTHER WISE... EXTRA LINE....just odd format NOT A BIG DEAL
}


