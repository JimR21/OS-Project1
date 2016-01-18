#include "hashfunction.h"


unsigned int BKDRHash(char* str)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i;
   for(i = 2; i < 10; i++)
   {
      hash = (hash * seed) + (str[i]);
   }
   return hash;
}

