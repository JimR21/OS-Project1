#include "myRecordDef.h"



void RecSetVal(MyRecord* target, MyRecord source)
{
    *target = source;
}

void WriteValue(MyRecord source)
{
    printf("%s %s %s %s %5.2f\n", source.phone, source.FirstName, source.LastName, source.Town, source.invoice);
}

int CompareValue(MyRecord source, char* num)
{
    if(strcmp(source.phone, num) == 0)
        return 1;
    return 0;
}

void ReadValue(MyRecord* target)
{
    char phoneno[SIZEofBUFF], lastname[SIZEofBUFF], firstname[SIZEofBUFF], town[SIZEofBUFF];
    float amount;
    scanf("%s %s %s %s %f", phoneno, firstname, lastname, town, &amount);
    strcpy(target->phone, phoneno);
    strcpy(target->LastName, lastname);
    strcpy(target->FirstName, firstname);
    strcpy(target->Town, town);
    target->invoice = amount;
}
