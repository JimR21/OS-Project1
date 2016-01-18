#ifndef myrecordd
#define myrecordd

#define SIZEofBUFF 20
#define HS 100003

#include <stdio.h>
#include <string.h>

typedef struct{
	char  	phone[SIZEofBUFF];
	char 	FirstName[SIZEofBUFF];
	char 	LastName[SIZEofBUFF];
	char	Town[SIZEofBUFF];
	float  	invoice;
} MyRecord;


void RecSetVal(MyRecord* target, MyRecord source);

void WriteValue(MyRecord source);

int CompareValue(MyRecord source, char* num);

void ReadValue(MyRecord* target);


#endif
