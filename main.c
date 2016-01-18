#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "primes.h"
#include "list.h"

#define DEFAULT_HASH_SIZE 100

int hashtsize = 0;      // Megethos tou hashtable
pnode *hashtable;       // Arxh tou hashtable
pnode_town start_town;  // Arxh tou indextable

/* Synarthsh gia thn periptwsh poy yparxei arxeio eggrafwn san orisma */

int Load_file(char* loadFile)
{
    FILE *fpb;
        MyRecord rec;
        long lSize;
        int numOfrecords, i;
        fpb = fopen (loadFile,"rb");
        if (fpb==NULL)
        {
            printf("Cannot open binary file\n");
            return 0;
        }

        // check number of records
        fseek (fpb , 0 , SEEK_END);
        lSize = ftell (fpb);
        rewind (fpb);
        numOfrecords = (int) lSize/sizeof(rec);
        if(hashtsize == 0)
        {
            hashtsize = primes(numOfrecords/2);
            hashtable = malloc(hashtsize*(sizeof(pnode)));
        }
        for(i = 0; i < hashtsize; i++)
        {
            hashtable[i] = NULL;
        }
        for (i=0; i<numOfrecords ; i++)
        {
            fread(&rec, sizeof(rec), 1, fpb);
            InsertL(rec, hashtable, hashtsize, start_town);
        }
        fclose(fpb);
        printf("Data file loaded succesfully.\n");
        return 1;
}


int main (int argc, char** argv)
{
    int a, pop, sum, k;
    int l, o, c;
    int fd, val;

    MyRecord temprec, r;
    char ch;
    char phoneno[20];
    char town[20];
    char min[20], max[20];
    char word[20];
    l = 0;
    o = 0;
    c = 0;
    char loadFile[20], opFile[20], configFile[20];

    /* Diabasma orismatwn */

    opterr = 0;

    while ((a = getopt (argc, argv, "l:o:c:")) != -1)
        switch (a)
        {
           case 'l':
             strcpy(loadFile, optarg);
             l = 1;
             break;
           case 'o':
             strcpy(opFile, optarg);
             o = 1;
             break;
           case 'c':
             strcpy(configFile, optarg);
             c = 1;
             break;
           case '?':
             if (optopt == 'p' || optopt == 'i' || optopt == 'd')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
        }

   InitializeI(&start_town);

   /* Xrhsh orismatwn */
    if(c == 1)
    {
        FILE* con;
        con = fopen(configFile,"r");
        if (con == NULL)
        {
            printf("Cannot open configuration file\n");
        }
        else
            while(!feof(con))
            {
                if(fscanf(con, "%s %d", word, &val) == 2)
                    if(strcmp(word, "Hash_Table_Size") == 0)
                    {
                        hashtsize = val;
                        hashtable = malloc(hashtsize*(sizeof(pnode)));
                    }
            }
    }
    if(l == 1)
    {
        Load_file(loadFile);
        l = 0;
    }
     if(o == 1)                     // An uparxei operation file tote to stdin anakateuthunetai sto arxeio ayto k diabazontai oi entoles kanonika mexri na teleiwsei
    {
        if(hashtsize == 0)
        {
            hashtsize = primes(DEFAULT_HASH_SIZE);
            hashtable = malloc(hashtsize*(sizeof(pnode)));
        }
        if( access(opFile, F_OK ) != -1 )
        {
            fd = dup(fileno(stdin));
            freopen(opFile, "r", stdin);
        }
        else
            printf("Cannot open operation file\n");

    }
    memset(max, '0', 20);
    memset(min, '0', 20);
    if(hashtsize == 0)
        {
            hashtsize = primes(DEFAULT_HASH_SIZE);
            hashtable = malloc(hashtsize*(sizeof(pnode)));
        }
    if(o == 0)
        printf("Give input\n");

    /* Epanalipsh gia thn eisagwgh entolwn. Diavasma prwtou xarakthra kai elegxos periptwsewn */
    while(1)
    {


        ch = getchar();
        if(ch == 'i')
        {
            ReadValue(&temprec);
            if(SearchL(temprec.phone, hashtable, hashtsize, &r) == 0)
                InsertL(temprec, hashtable, hashtsize, start_town);
            else
                printf("Number %s already exists. Cannot add the same number twice.\n", temprec.phone);
            //temp_town = start_town;
		}
		else if(ch == 'q')
		{
            scanf("%10s", phoneno);
            if(SearchL(phoneno, hashtable, hashtsize, &r) == 1)
                WriteValue(r);
            else
                printf("Number %s not found.\n", phoneno);
            memset(phoneno, '\0', 20);
		}
		else if(ch == 'd')
		{
            scanf("%10s", phoneno);
            DeleteL(phoneno, hashtable, hashtsize, start_town);
            memset(phoneno, '\0', 20);
		}
		else if(ch == 'l')
        {
            scanf("%s", loadFile);
            Load_file(loadFile);
        }
		else if(ch == 'e')
		{
            FreeIndex(start_town);
            free(start_town);
            free(hashtable);
            return 0;
		}
		else if(ch == 'p')
		{
            scanf("%s", town);
            pop = PopulationI(start_town, town);
            if(pop > 0)
                printf("%s: %d\n", town, pop);
            else
                printf("Town %s not found.\n", town);
            memset(town, '\0', 20);
		}
		else if(ch == 's')
		{
            scanf("%s", town);
            sum = SummaryI(start_town, town);
            if(sum > 0)
                printf("%s: %d\n", town, sum);
            else
                printf("Town %s not found.\n", town);
            memset(town, '\0', 20);
		}
		else if(ch == 't')
		{
            scanf("%d", &k);
            Top(start_town, k);
		}
		else if(ch == 'f')
		{
            ch = getchar();
            if(ch == 't')
            {
                ch = getchar();
                if(ch == ' ')
                {
                    scanf("%s %d", town, &k);
                    TopKSpenders(start_town, town, k);
                }
                else if(ch == 's')
                    TopTownSpenders(start_town);
            }
		}
		else if(ch == 'm')
		{
            ch = getchar();
            if(ch == 'a')
            {
                ch = getchar();
                if(ch == 'x')
                {
                    //if(max[0] == '0')
                        Max(start_town);
                }
            }
            else if(ch == 'i')
            {
                ch = getchar();
                if(ch == 'n')
                {
                   // if(min[0] == '0')
                        Min(start_town);
                }
            }
		}
		//scanf("%20s", junk);
		if(o == 1 && ch == EOF)     // An yparxei operation file san orisma kai exei teleiwsei h anagnwsh epanafora tou stdin.
        {
            fflush(stdin);
            dup2(fd, fileno(stdin));
            close(fd);
            clearerr(stdin);
            o = 0;
            printf("Operation file finished succesfully.\n");
        }
        fflush(stdin);
    }

    return 0;

    }
