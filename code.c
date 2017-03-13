#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getString(FILE* fp);
void flush();
char *getSide (char *sideNumber);
char *decideTriangle(char *a, char *b, char *c);
/*Main*/
int main(void)
{

	char *a,*b,*c;
	
	//getting all three side lengths as strings
	a = getSide("first");
	b = getSide("second");
	c = getSide("third");
	
	printf("\nThe triangle is %s",decideTriangle(a,b,c));
	
	free(a); free(b); free(c);
	return 0;
}

/*Recognizing the type of the triangle based on the input side lengths */
char *decideTriangle(char *a, char *b, char *c)
{

if( !strcmp(a,b) && !strcmp(b,c) )			// all sides equal
	return"an equilateral triangle\n";
else if(!strcmp(a,b) || !strcmp(a,c) || !strcmp(b,c))       // at least 2 sides equal
	return "an isosceles triangle\n";
else                                // no sides equal
	return "a scalene triangle\n";
}

/* A function that removes prefix and suffix zeroes from an input string, returning a pointer to an allocated space the size of the truncated string*/
char *removeZeroes (char *input)
{
	char* output;
	int prefix=0, suffix, counter=0, dot=0;
	suffix=strlen(input)-1;
	while (input[dot] != '.' && dot < strlen(input)) {dot++;} //find the dot if its there
	if (input[dot] == '.') //remove both prefix and suffix 0s as there is a dot
	{
		while (input[prefix] == '0' ) {prefix++;}
		while (input[suffix] == '0' ) {suffix--; counter++; }
		if(input[suffix]=='.') {suffix--; counter++; }//remove the dot if no decimal part
		output = calloc((strlen(input)-counter-prefix+1),sizeof(char));
		output = strncpy(output, input+sizeof(char)*prefix, strlen(input)-prefix-counter);
	}
	else //remove only prefix 0s if no decimal part
	{
		while (input[prefix] == '0' ) {prefix++;}
		output = calloc((strlen(input)-prefix+1),sizeof(char));
		output = strncpy(output, input+sizeof(char)*prefix, strlen(input)-prefix);
	}
	return output;
}

/*Getting single side lenght as input from the user. The argument carries a string indicating the number of the requested side length in text used for displaying.*/
char *getSide(char *sideNumber)
{
	double retval;
	char *sideLength, *sideLengthTruncated, *endptr;
	do {
		printf("\nInsert the length of the %s side: \n", sideNumber);	
		sideLength = getString(stdin); //using a custom function for reading unpredictably long input
		if(sideLength==NULL) 
		{
			printf("Error. Failed to allocate memory. Exiting."); 
			free(sideLength); 
			exit(EXIT_FAILURE);
		}	
		retval = strtold(sideLength,&endptr); //converting the string to a double
		
		if (*endptr == ',') //ensuring a proper use of the decimal separator
		{
			printf ("Error. Please use the dot as decimal separator. \n");
			retval=0.0f;
		}
		else if (*endptr != 0) //checking if the input was completely a number
		{
			printf ("Error. The input is not a decimal, dot separated number. \n");
			retval=0.0f;
		}
		else if (retval == 0 && strcmp(sideLength,"")) printf ("Error. The length cannot be 0\n");
		if (!strcmp(sideLength,"")) //checking for empty input
		{
			printf ("Error. Empty input. \n");
			retval=0.0f;
		}
		else if (retval < 0) //checking if the number is non-negative
		{
			printf ("Error. The length has to be positive. \n");
			retval=0.0f;
		}
		if(retval==0.0f) free (sideLength);
		}while(!retval);
	
	sideLengthTruncated = removeZeroes(sideLength);
	free(sideLength);
	return sideLengthTruncated;
}
/*Function for processing unpredictably long input*/
char *getString(FILE* fp){
	
	char *str;
	int ch;
	size_t size = 16; //initial size
	size_t len = 0;
	str = calloc(size, sizeof(char));
	if(!str) return str; //returning in case of failing to allocate mem
	while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
		str[len++]=ch;
		if(len==size){
			str = realloc(str, sizeof(char)*(size+=16));//allocating more mem for longer input
			if(!str) return str;
		}
	}
	str = realloc(str, sizeof(char)*(len+1));//reallocating space for the string and the terminating \0
	if(!str) return str;
	str[len++]='\0';

	return str;
}