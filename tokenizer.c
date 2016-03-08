#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include <ctype.h>



TokenizerT *TKCreate(char *ts ) 
{
	TokenizerT *tokenizer = malloc(sizeof(struct TokenizerT_));
	
	//tokenizer->sep = malloc(sizeof(char)*strlen(separators)+1);
	
	tokenizer->strArray = malloc(sizeof(char)*strlen(ts)+1);
	
	tokenizer->token = malloc(sizeof(char)*strlen(ts)+1);
	
	strcpy(tokenizer->strArray,ts);
	
	//strcpy(tokenizer->sep,separators);
	
	//tokenizer->count = 0;
	
  return tokenizer;
}


void TKDestroy( TokenizerT * tk ) 
{
	free (tk->token);
	free (tk->strArray);
	//free (tk->sep);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
 static int counter = 0; 
void resetFileCounter()
{
	counter = 0;
}
char *TKGetNextToken( TokenizerT * tk ) 
{
	//free(tk->token);
	//tk->token = malloc(sizeof(char)*strlen(tk->strArray)+1);
	//tk->token=calloc(200,10);

	
	//int i;
//	static int counter = 0;
	//int j=0;
	//int counter=0;
	//int size= strlen(tk->strArray);
	

	//printf("--------%c", tk->strArray[counter]);

	while(tk->strArray[counter] == ' ' || ispunct(tk->strArray[counter]) ) //skips initial white spaces
	{	
		counter++;
	}
	
	int tokenCount = 0;
	while(   (tk->strArray[counter] != ' ') && (tk->strArray[counter] != '\0') && (!ispunct(tk->strArray[counter]))  )//checks seperator and gets 1 token
	{

		
		
		
	/*	
		tk->token[tokenCount] = tk->strArray[counter];
		counter++;
		tokenCount++;		
		tk->token[tokenCount] = tk->strArray[counter];	
		counter++;
		tokenCount++;	
		tk->token[tokenCount] = tk->strArray[counter];
		
		tokenCount++;
*/
		
		//printf("%s\n", tk->token);
				
		//break;
		tk->token[tokenCount] = tk->strArray[counter];
		
		counter++;
		tokenCount++;
		
	/*	
		tk->token[1] = '\0';
		if(tk->token[1] == '\0')
			printf("hehe\n");
		*/
		
		
		
		//break;
	}
	//tokenCount--
	tk->token[tokenCount] = '\0';
	
//	if( isalpha(tk->token[tokenCount--]) == 0 || isalnum(tk->token[tokenCount--]) == 0)
//		return NULL;
//	else
	if(!(isalnum(tk->token[tokenCount = tokenCount-2])))
	{
			return NULL;
	}
	else
	{	
		
		
			//char* myPointer = "OH MY HOST";
			char* mine = tk->token;
			const int l = strlen(mine);
			char* low = (char*)malloc(l+1);
			low[l] = 0;
			//const int length = strlen( myPointer ); // get the length of the text
			//char* lower = ( char* )malloc( length + 1 ); // allocate 'length' bytes + 1 (for null terminator) and cast to char*
			//lower[ length ] = 0; // set the last byte to a null terminator

			// copy all character bytes to the new buffer using tolower
			int i;
			for(i = 0; i < l; i++ )
			{
				low[ i ] = tolower( mine[ i ] );
			}		
		tk->token = low;
		
		return tk->token;
	}
 
}


/*		
	if(isalpha(*(tk->strArray)))
	{
		while(isalnum(*(tk->strArray)))
		{
			*((tk->token)+inc)= *tk->strArray;
			*tk->strArray++;
			inc++;
		}	
			return tk->token;
	}	
*/	
//         [************************if you look down further it returns a token********************]
	
	
	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*	
	//checks for hex
	if(*tk->strArray=='0')
	{
		*((tk->token)+inc)= *tk->strArray;
		inc++;
		*tk->strArray++;
		
		if(*tk->strArray=='x'||*tk->strArray=='X')
		{
			*((tk->token)+inc)= *tk->strArray;
			inc++;
			*tk->strArray++;
			
			while(isdigit(*(tk->strArray)) || (  *(tk->strArray) >= 65 && *(tk->strArray) <=70 ) ||  (  *(tk->strArray) >= 97 && *(tk->strArray) <=102    ))
			{
				*((tk->token)+inc)= *tk->strArray;
				*tk->strArray++;
				inc++;
			}
		}
	//	printf("hi");
		if( (*tk->strArray) == '0'  || (*tk->strArray) == '1' || (*tk->strArray) == '2'  || (*tk->strArray) == '3' || (*tk->strArray) == '4'  || (*tk->strArray) == '5' || (*tk->strArray) == '6'  || (*tk->strArray) == '7')
		{
	//	printf("hi");			
			*((tk->token)+inc)= *tk->strArray;
			inc++;
			*tk->strArray++;
						
			while( (*tk->strArray) == '0'  || (*tk->strArray) == '1' || (*tk->strArray) == '2'  || (*tk->strArray) == '3' || (*tk->strArray) == '4'  || (*tk->strArray) == '5' || (*tk->strArray) == '6'  || (*tk->strArray) == '7')
			{
				*((tk->token)+inc)= *tk->strArray;
				*tk->strArray++;
				inc++;				
				
				
			}
			
			
			
		}
		
			return tk->token;
	}
 */	
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*
	// digit checker
	if(isdigit(*(tk->strArray)))
	{
		
		while(isdigit(*(tk->strArray)))
		{
			*((tk->token)+inc)= *tk->strArray;
			*tk->strArray++;
			inc++;
		}
		
		if( *(tk->strArray) == '.')
		{
			*((tk->token)+inc)= *tk->strArray;
			*tk->strArray++;
			inc++;			
			
			while(isdigit(*(tk->strArray))  )
			{
				*((tk->token)+inc)= *tk->strArray;
				*tk->strArray++;
				inc++;					
			}	
			if( *(tk->strArray) == 'e' || *(tk->strArray) == 'E')
			{
				*((tk->token)+inc)= *tk->strArray;
				*tk->strArray++;
				inc++;
				
				while(isdigit(*(tk->strArray))  )
				{
					*((tk->token)+inc)= *tk->strArray;
					*tk->strArray++;
					inc++;					
				}
				if( *(tk->strArray) == '-' || isdigit(*(tk->strArray)))
				{
				*((tk->token)+inc)= *tk->strArray;
				*tk->strArray++;
				inc++;
				while(isdigit(*(tk->strArray))  )
				{
					*((tk->token)+inc)= *tk->strArray;
					*tk->strArray++;
					inc++;					
				}					
					
				}
			}
			
			
			
			
		} 
			return tk->token;
	}
*/
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	

	//*((tk->token)+inc)= *tk->strArray;
	//inc++;
	//*tk->strArray++;
	
	//if(ispunct(*(tk->strArray)))
	//return tk->token;
//}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*
	while( ispunct(*tk->strArray) )
	{
		*((tk->token))= *tk->strArray;

		*tk->strArray++;
	
		return (tk->token); //returns to main
	}
*/
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
	//return tk->token;
	
//}




//=*=*=*=*=*=*=*=**=*=*=*=**=*=*=*=*=*=*=**=*=*=*=**=*=*=*=*=*=*=**=*=*==**=**=*=**=*=*=*=*=*=*=*=**=*=*=**=*=*=**==**=*=**=
/*
void decipher(char *p)
{
	if((int)*p == 33)
		printf("             Exclamation point %c", *p);
    if((int)*p == 34)
		printf("             Double quotes %c", *p);	
	if((int)*p == 35)
		printf("             Number  %c", *p);
    if((int)*p == 36)
		printf("             Dollar %c", *p);
	if((int)*p == 37)
		printf("             percent %c", *p);
    if((int)*p == 38)
		printf("             ampersand %c", *p);	
	if((int)*p == 39)
		printf("             single quote %c", *p);
    if((int)*p == 40)
		printf("             open parenthesis %c", *p);	
	if((int)*p == 41)
		printf("             closed parenthesis %c", *p);
    if((int)*p == 42)
		printf("             asterisk or multiply %c", *p);	
	if((int)*p == 43)
		printf("             plus %c", *p);
    if((int)*p == 44)
		printf("             comma %c", *p);	
	if((int)*p == 45)
		printf("             hyphen %c", *p);
    if((int)*p == 46)
		printf("             period %c", *p);	
	if((int)*p == 47)
		printf("             forward slash %c", *p);		
	if((int)*p == 58)
		printf("             colon %c", *p);	
	if((int)*p == 59)
		printf("             semicolon %c", *p);
    if((int)*p == 60)
		printf("             less than %c", *p);	
	if((int)*p == 61)
		printf("             equals %c", *p);
    if((int)*p == 62)
		printf("             greater than %c", *p);	
	if((int)*p == 63)
		printf("             question mark %c", *p);
    if((int)*p == 64)
		printf("             at symbol %c", *p);			
	if((int)*p == 91)
		printf("             open bracket %c", *p);		
	if((int)*p == 92)
		printf("             back slash %c", *p);	
	if((int)*p == 93)
		printf("             closing bracket %c", *p);
    if((int)*p == 94)
		printf("             caret %c", *p);	
	if((int)*p == 95)
		printf("             underscore %c", *p);
    if((int)*p == 96)
		printf("             grave accent %c", *p);	
	if((int)*p == 123)
		printf("             open brace %c", *p);
    if((int)*p == 124)
		printf("             vertical bar %c", *p);	
	if((int)*p == 125)
		printf("             close brace %c", *p);
    if((int)*p == 126)
		printf("             equivalency sign %c", *p);	

	//checks if its a float
	int isFloat =0;
	int isHex =0;
	
	if (strstr(p, ".") != NULL )
	{
		printf("\t\t[FLOAT]");
		isFloat = 1;
	}

	
	//checks if alphabetic word
	int counter;
	int flag;
	for(counter = 0; counter < strlen(p); counter++)
	{
		if(isalpha(*(p+counter) ))
		 flag = 1;
		else
		 flag = 0;
	}	
	if(flag == 1)
		printf("\t\t[ALPHABETIC WORD]");
			
	//checks if its hexidecimal
	if(*p == '0' && *(p+1) == 'x' || *(p+1) == 'X') 
	{
	  	printf("\t[HEXIDECIMAL]");
	  	isHex = 1;
	}
	
	//checks if its Octal
	int isOctal;	
	if(*p == '0' && ( isHex == 0 && isFloat == 0  ) )
	{
		isOctal=1;
		printf("\t\t[OCTAL]");
	}
	else if( ((*p >= '1' && *p<= '9' ) ||  *p == '0' ) &&  ( isHex == 0 && isFloat == 0 && isOctal ==0  ))	
		printf("\t\tINTEGER");
}



// * main will have a string argument (in argv[1]).
// * The string argument contains the tokens.
// * Print out the tokens in the second string in left-to-right order.
// * Each token should be printed on a separate line.

*/


