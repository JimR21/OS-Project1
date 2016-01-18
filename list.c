#include "list.h"



int InsertL(MyRecord r, pnode *hashtable, int htsize, pnode_town start_town)
{
    int n = BKDRHash(r.phone)%htsize;
    pnode temp;
    temp = malloc(sizeof(node));
    RecSetVal(&temp->data, r);
    if(hashtable[n] == NULL)
    {
        temp->next = NULL;
        temp->previous = NULL;
        hashtable[n] = temp;
    }
    else
    {
        hashtable[n]->previous = temp;
        temp->next = hashtable[n];
        temp->previous = NULL;
        hashtable[n] = temp;
    }
    InsertI(start_town, temp);
    printf("Phone number %s added successfully.\n", r.phone);
    return 1;
}

void WriteL(pnode p)
{
    WriteValue(p->data);
}

int SearchL(char* num, pnode* hashtable, int htsize, MyRecord* rec)
{
    int n = BKDRHash(num)%htsize;
    if(hashtable[n] == NULL)
        return 0;
    if(CompareValue(hashtable[n]->data, num) == 1)
    {
        //WriteValue(hashtable[n]->data);
        RecSetVal(rec, hashtable[n]->data);
        return 1;
    }
    pnode temp = hashtable[n];
    while(temp->next != NULL)
    {
        temp = temp->next;
        if(CompareValue(temp->data, num) == 1)
        {
            //WriteValue(temp->data);
            RecSetVal(rec, temp->data);
            return 1;
        }
    }
    return 0;
}

int DeleteL(char* num, pnode *hashtable, int htsize, pnode_town start_town)
{
    pnode temp;
    int n = BKDRHash(num)%htsize;
    if(hashtable[n] == NULL)
    {
        printf("Phone number %s not found.\n", num);
        return 0;
    }
    else
    {
        if(CompareValue(hashtable[n]->data, num) == 1)
        {
            DeleteI(hashtable[n]->data, start_town);
            if(hashtable[n]->next == NULL)
            {
                free(hashtable[n]);
                hashtable[n] = NULL;
                printf("Phone number %s deleted successfully.\n", num);
                return 1;
            }
            temp = hashtable[n];
            hashtable[n] = temp->next;
            hashtable[n]->previous = NULL;
            free(temp);
            printf("Phone number %s deleted successfully.\n", num);
            return 1;
        }
        temp = hashtable[n];
        while(temp->next != NULL)
        {
            temp = temp->next;
            if(CompareValue(temp->data, num) == 1)
            {
                if(temp->next == NULL)
                {
                    temp->previous->next = NULL;
                }
                else
                {
                    (temp->next)->previous = temp->previous;
                    (temp->previous)->next = temp->next;
                }
                DeleteI(temp->data, start_town);
                free(temp);
                printf("Phone number %s deleted successfully.\n", num);
                return 1;
            }
        }
    }
    printf("Phone number %s not found.\n", num);
    return 0;
}

int InitializeI(pnode_town *start_town)
{
    *start_town = malloc(sizeof(struct index_town));
    strcpy((*start_town)->name, "Start");
    (*start_town)->start = NULL;
    (*start_town)->next = NULL;
    (*start_town)->previous = NULL;
    return 1;
}

int InsertI(pnode_town start_town, pnode node)
{
    pnode_town temp_town, new_town;
    index_pnode inode;
    inode = malloc(sizeof(struct index_komvos));
    inode->record = node;
    temp_town = start_town;
    while(temp_town->next != NULL)
    {
        temp_town = temp_town->next;
        if(strcmp(temp_town->name, node->data.Town) == 0)
        {
            temp_town->start->previous = inode;
            inode->next = temp_town->start;
            temp_town->start = inode;
            inode->previous = NULL;
            temp_town->pop++;
            temp_town->sum += node->data.invoice;
            if(temp_town->ts_invoice < node->data.invoice)
            {
                temp_town->ts_invoice = node->data.invoice;
                strcpy(temp_town->top_spender, node->data.phone);
            }
            return 1;
        }
    }
    new_town= malloc(sizeof(struct index_town));
    strcpy(new_town->name, node->data.Town);
    temp_town->next = new_town;
    inode->previous = NULL;
    inode->next = NULL;
    new_town->start = inode;
    new_town->pop = 1;
    new_town->sum = node->data.invoice;
    strcpy(new_town->top_spender, node->data.phone);
    new_town->ts_invoice = node->data.invoice;
    new_town->previous = temp_town;
    new_town->next = NULL;
    return 1;
}

int DeleteI(MyRecord rec, pnode_town start_town)
{
    pnode_town temp_town = start_town->next;
    index_pnode temp_node;
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return 1;
    }
    while(temp_town != NULL)
    {
        if(strcmp(temp_town->name, rec.Town) == 0)
        {
            temp_node = temp_town->start;
            while(temp_node != NULL)
            {
                if(strcmp(temp_node->record->data.phone, rec.phone) == 0)
                {
                    if(temp_town->pop == 1)
                    {
                        if(temp_town->next == NULL)
                        {
                            temp_town->previous->next = NULL;
                        }
                        else if(temp_town->previous == NULL)
                        {
                            temp_town->next->previous = NULL;
                            start_town->next = temp_town->next;
                        }
                        else
                        {
                            temp_town->next->previous = temp_town->previous;
                            temp_town->previous->next = temp_town->next;
                        }
                        free(temp_town);
                    }
                    else if(temp_node->next == NULL)
                    {
                        temp_node->previous->next = NULL;
                        temp_town->pop--;
                        temp_town->sum -= temp_node->record->data.invoice;
                        if(strcmp(temp_town->top_spender, temp_node->record->data.phone) == 0)
                        {
                            temp_town->ts_invoice = 0;
                        }
                    }
                    else if(temp_node->previous == NULL)
                    {
                        temp_node->next->previous = NULL;
                        temp_town->start = temp_node->next;
                        temp_town->pop--;
                        temp_town->sum -= temp_node->record->data.invoice;
                        if(strcmp(temp_town->top_spender, temp_node->record->data.phone) == 0)
                        {
                            temp_town->ts_invoice = 0;
                        }
                    }
                    else
                    {
                        temp_node->next->previous = temp_node->previous;
                        temp_node->previous->next = temp_node->next;
                        temp_town->pop--;
                        temp_town->sum -= temp_node->record->data.invoice;
                        if(strcmp(temp_town->top_spender, temp_node->record->data.phone) == 0)
                        {
                            temp_town->ts_invoice = 0;
                        }
                    }
                    free(temp_node);
                    //printf("Deleted successfully from inverted index\n");
                    return 1;
                }
                temp_node = temp_node->next;
            }
        }
        temp_town = temp_town->next;
    }
    return 0;
}

int PopulationI(pnode_town start_town, char* town)
{
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return -1;
    }
    pnode_town temp = start_town;
    while(temp->next != NULL)
    {
        temp = temp->next;
        if(strcmp(temp->name, town) == 0)
            return temp->pop;
    }
    return -1;
}

int SummaryI(pnode_town start_town, char* town)
{
    pnode_town temp = start_town;
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return -1;
    }
    while(temp->next != NULL)
    {
        temp = temp->next;
        if(strcmp(temp->name, town) == 0)
            return temp->sum;
    }
    return -1;
}

int Top(pnode_town start_town, int k)
{
    int tops[k];
    char towns[k][20];
    int i, j;
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return -1;
    }
    for(i = 0; i < k; i++)
    {
        tops[i] = 0;
    }
    pnode_town temp = start_town;
    while(temp->next != NULL)
    {
        temp = temp->next;
        for(i = 0; i < k; i++)
        {
            if(tops[i] == 0)
            {
                tops[i] = temp->pop;
                strcpy(towns[i], temp->name);
                break;
            }
            else
            {
                if(temp->pop > tops[i])
                {

                    for(j = k-1; j > i; j--)
                    {
			if(tops[j-1] != 0)
			{
                            tops[j] = tops[j-1];
                            strcpy(towns[j], towns[j-1]);
			}
                    }
                    tops[i] = temp->pop;
                    strcpy(towns[i], temp->name);
                    break;
                }
            }
        }
    }
    for(i = 0; i < k; i++)
    {
        if(tops[i] == 0)
            break;
        printf("%s: %d\n", towns[i], tops[i]);
    }
    return 1;
}


int TopKSpenders(pnode_town start_town, char *town, int k)
{
    int tops[k];
    char numbers[k][20];
    int i, j;
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return -1;
    }
    for(i = 0; i < k; i++)
    {
        tops[i] = 0;
    }
    pnode_town temp_town = start_town;
    index_pnode temp;
    while(temp_town->next != NULL)
    {
        temp_town = temp_town->next;
        if(strcmp(temp_town->name, town) == 0)
            break;
    }
    temp = temp_town->start;
    while(temp != NULL)
    {
        for(i = 0; i < k; i++)
        {
            if(tops[i] == 0)
            {
                tops[i] = temp->record->data.invoice;
                strcpy(numbers[i], temp->record->data.phone);
                break;
            }
            else
            {
                if(temp->record->data.invoice > tops[i])
                {
                    for(j = k-1; j > i; j--)
                    {
			if(tops[j-1] != 0)
			{
                             tops[j] = tops[j-1];
                             strcpy(numbers[j], numbers[j-1]);
			}
                    }
                    tops[i] = temp->record->data.invoice;
                    strcpy(numbers[i], temp->record->data.phone);
                    break;
                }
            }
        }
        temp = temp->next;
    }
    for(i = 0; i < k; i++)
    {
        if(tops[i] == 0)
            break;
        printf("%s: %d\n", numbers[i], tops[i]);
    }
    return 1;
}

int TopTownSpenders(pnode_town start_town)
{
    pnode_town temp_town;
    if(start_town->next == NULL)
    {
        printf("No towns found\n");
        return -1;
    }
    temp_town = start_town->next;
    index_pnode node;
    while(temp_town != NULL)
    {
        if(temp_town->ts_invoice > 0)
        {
            printf("%s: %s %d\n", temp_town->name, temp_town->top_spender, temp_town->ts_invoice);
        }
        else
        {
            node = temp_town->start;
            while(node != NULL)
            {
                if(node->record->data.invoice > temp_town->ts_invoice)
                {
                    temp_town->ts_invoice = node->record->data.invoice;
                    strcpy(temp_town->top_spender, node->record->data.phone);
                }
                node = node->next;
            }
            printf("%s: %s %d\n", temp_town->name, temp_town->top_spender, temp_town->ts_invoice);
        }
        temp_town = temp_town->next;
    }
    return 1;
}

int CompareMax(char *phone1, char *phone2)
{
    long long p1, p2;
    phone1 += 2;
    phone2 += 2;
    p1 = atoll(phone1);
    p2 = atoll(phone2);
    if(p1 > p2)
        return 1;
    else
        return 2;
}

int CompareMin(char *phone1, char *phone2)
{
    long long p1, p2;
    phone1 += 2;
    phone2 += 2;
    p1 = atoll(phone1);
    p2 = atoll(phone2);
    if(p1 < p2)
        return 1;
    else
        return 2;
}

int Max(pnode_town start_town)
{
    pnode_town temp_town;
    if(start_town->next == NULL)
    {
        printf("No records found\n");
        return -1;
    }
    temp_town = start_town->next;
    index_pnode node;
    char max[20];
    strcpy(max, "0000000000");
    while(temp_town != NULL)
    {
        node = temp_town->start;
        while(node != NULL)
        {
            if(CompareMax(node->record->data.phone, max) == 1)
                strcpy(max, node->record->data.phone);
            node = node->next;
        }
        temp_town = temp_town->next;
    }
    printf("%s\n", max);
    return 1;
}

int Min(pnode_town start_town)
{
    pnode_town temp_town;
    if(start_town->next == NULL)
    {
        printf("No records found\n");
        return -1;
    }
    temp_town = start_town->next;
    index_pnode node;
    char min[20];
    strcpy(min, "9999999999");
    while(temp_town != NULL)
    {
        node = temp_town->start;
        while(node != NULL)
        {
            if(CompareMin(node->record->data.phone, min) == 1)
                strcpy(min, node->record->data.phone);
            node = node->next;
        }
        temp_town = temp_town->next;
    }
    printf("%s\n", min);
    return 1;
}

int FreeIndex(pnode_town start_town)
{
    pnode_town town1, town2;
    if(start_town->next == NULL)
    {
        return 1;
    }
    town1 = start_town->next;
    town2 = start_town->next;
    index_pnode node1, node2;
    while(town1 != NULL)
    {
        node1 = town1->start;
        node2 = town1->start;
        while(node1 != NULL)
        {
            free(node1->record);
            node1 = node2->next;
            free(node2);
            node2 = node1;
        }
        town1 = town2->next;
        free(town2);
        town2 = town1;
    }
    return 1;
}























