#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "readprocess.h"
#include "tokenizer.h"
#include "sorted-list.h"

	static char* charptr[999][999];
	static int i = 0;
	
	int exist(char *filename)
	{
		struct stat   buffer;   
		return (stat (filename, &buffer) == 0);
	}
	
void subDirectory(char*, char*, SortedListPtr list);	
//int readprocess(char*, SortedListPtr list);					
								 //target      output file	               path
int main(int argc, char **argv)  //index <inverted-index file name> <directory or file name>
{
  
	char *outputFile = argv[1];  //input 2 before space after ./main use quotes to make argv1 including spaces
	char *pathName = argv[2];	 //given a folder path....directory
	

	
	struct stat status;
	struct dirent *pDirent;
	//struct dirent *ini;
	DIR* dir;


	if(argc != 3)
	{
		printf("Incorrect amount of arguments");
		return 0;
	}
	char ans[0];
	char strp[999];
/*	if(exist(pathName) == 0)
	{
		printf ("This OutputFile exists, Would you like to Overwrite?\n ONLY Type Y for yes N for no\n");
		scanf("%c", ans);
		if(ans[0] == 'Y')
		{	
			printf("File will be overwritten\n");
			
		}
		else if( ans[0] == 'N')
		{
			printf("Please enter fileName : ");
			scanf("%s", &strp);
			
			outputFile = strp;
			printf(">>>>inside N  %s", strp);
		}	
	}
*/ 
	//printf("new output file is: %s \n", outputFile);
	//Creates the outputFIle
	FILE *ofp;
	ofp = fopen(outputFile, "w");
	if(!ofp)
	{
		perror("Cannot open output file");
		//exit(0);
		exit(EXIT_FAILURE);
	}
	//MAKE SURE TO CLOSE THIS FILE WHEN UR DONE WRITING TO IT!!!!!!!!!!!!!!!!!!!!!!!!!!!	
	//try and open this folder 
	
	//Creates only 1 List
	SortedListPtr list = SLCreate(compareStrings);	
			

	int st;
	st = stat(pathName,&status);
	if(st != 0)
	{
		printf("Error");
		return 1;
	}	
	if(S_ISREG(status.st_mode))
	{	
		
		readprocess(pathName, list);
		outputAll(list, ofp, pathName);
		fclose(ofp);						
		return 1;
	}
	//-------------------------------------------------------------------
	//now that i checked if the INITIAL current path is an error, fileName, or directory 

	dir = opendir(pathName); //Parent Directory has been open, now read the two files? RETURNS POINTER TO STREAM	
	
	if(dir == NULL)
		printf("Could not open directory: %s\n", pathName);
	else
		printf("\nWe are inside:  %s \n", pathName);
		
	//currentPath = realpath(pathName, getcwd(current,max)); //everytime i want to concatonate use REALPATH(short, LONG)
	
	char *currentPath = malloc(strlen(pathName)+1);	
	currentPath = pathName;
	
	printf("LETS SEE %s \n", currentPath);		


	//pDirent = readdir(dir);  //--------> '.'
	pDirent = readdir(dir);
	 
	while(pDirent != NULL)
	{	
		printf("loop %s\n", pDirent->d_name);
		//possible casses with the . and ..
		if(pDirent->d_type == DT_REG)
		{
//XXXX			printf("FILE:  %s\n", pDirent->d_name);
			//CALL THE PROCESSING FUNCTION
			
			char thePath[9999];
			strcpy(thePath, currentPath);
			strcat(strcat(thePath,"/"),pDirent->d_name);
			//printf("before process:%s\n",thePath);
			
			char *sv = thePath; 
			strcpy(charptr[i], sv);
			//printf("................... %s\n", charptr[i]);
			readprocess(charptr[i], list);			
			i++;
							
			//strcpy(thePath, currentPath);		
			//strcpy(currentPath, thePath);	
			
		}
		if(pDirent->d_type == DT_DIR && strcmp(pDirent->d_name, ".") != 0  && strcmp(pDirent->d_name, "..") != 0 )
		{															  
			//printf("directory\n");
			//char tp[9999];
			//strcpy(tp, currentPath);
			//strcat(strcat(tp,"/"),pDirent->d_name);			
			printf("%s\n\n", pDirent->d_name);
;																
			subDirectory(pDirent->d_name, currentPath, list);
	
		}
		//possible other cases?
		pDirent = readdir(dir);	
	}
	//now that we have seen all the files lets go back.
	closedir(dir);
//XXXX	printf("WE CLOSED Parent Directory\n"); 
	
	
//-=-=-=-=--=-==-=-=-==-THIS WILL OUTPUT TO FILE-=-=--=-==-=-=-==-==--=-=	

	
	
	
	//we will pass the list and print it 
	outputAll(list, ofp, pathName);
	fclose(ofp);
	
//-=-=-=-=-=-=--=-==-=-=-=-=-=-=--=-==-=-=-==-==--=-=-===-==-=-=-=-==-=-=-	
	return 0;
}

void subDirectory(char* sub, char* fullPath, SortedListPtr list)
{
	char subdirectory[999];
	char current[999];
	
	struct dirent* pD;
	DIR* dir2;
	
	strcpy(subdirectory, sub);
	strcpy(current, fullPath);
	strcat((strcat(current,"/")),subdirectory); 

//XXXX	printf("INSDIE SUBDIRECTORY: %s\n", current);

	
	dir2 = opendir(current);

	if(dir2 == NULL)
		printf("*****\n\nCould not open directory:   \n%s\n", current);
//XXXX	else
//XXXX		printf("We are inside:  %s \n", current);

	pD = readdir(dir2);
	
	while(pD != NULL)
	{
		//printf(">>%s\n",pD->d_name);
		
		if(pD->d_type == DT_REG)
		{
//XXXX			printf("FILE:  %s\n", pD->d_name);//append name to send
//XXXX			printf("INSIDE HERE\n");
			//save current dir into string as temp
			//concat current with "/" and pD->d_name
			//printf("Inside subDirectory()-> at FIle loop\n");
			
		//	char filepath[999];
		//	strcpy(filepath, current);
		//	strcat(strcat(filepath,"/"), pD->d_name);
		//	//printf("Lets Open:  %s\n", filepath);
			
		//	printf("In Main: %s\n", filepath);	
						
//,,,,,,

			char fn2[9999];	
			strcpy(fn2, current);
			strcat(strcat(fn2,"/"),pD->d_name);		
	
			
			char *sv = fn2; 
			strcpy(charptr[i], sv);
			printf("I am INSIDE about to open file: %s\n\n",charptr[i]);				
			readprocess(charptr[i], list);			
			i++;			
			//char keep[999][999];
			//char fn2[9999];
			//strcpy(fn2, current);
			//strcat(strcat(fn2,"/"),pD->d_name);
			//printf("before process:%s\n",fn2);
			
			//char *sv = fn2; 
			//strcpy(keep[0], sv);
			//readprocess(keep[0], list);			
			//i++;
//,,,,,,



			//SEND out filepath

			//Once you come back delete the name u appended-!!WORKS!!
			//when you come back use the strng u saved as temp
			
			//send the file name....
			//MUST APPEND FILES  TO CURRENT DIRECTORY 
			//WE WILL PASS THE NAME OF THE WHOLE DIRECTORY
			//AS THE PATH WILL BE USED TO OPEN THE FILE & USED FOR LIST
		}
	    if(pD->d_type == DT_DIR && strcmp(pD->d_name, ".") != 0  && strcmp(pD->d_name, "..") != 0 )
		{														  												
//XXXX			printf("DIRECTORY: %s\n", pD->d_name);               
			subDirectory(pD->d_name, current, list);
			
		}
		
		
		//if . or ..skip and go next   //possible other cases?
		pD = readdir(dir2);	
	}
//XXXX	printf("We are Leaving %s\n", current);
	closedir(dir2);
	
	return;
	
}
