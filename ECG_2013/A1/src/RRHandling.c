#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

struct PEAK {
    int atIndex;        // If older than buffer size cannot be reevaluated
    int type;           // 0 for any peak, 1 for R-peak
    int value;          // speaks for itself
    struct PEAK *next;
};

struct PEAK *head = NULL;
struct PEAK *curr = NULL;


int RR_AVERAGE1 = 0;
int RR_AVERAGE2 = 0;
int RR_LOW = 0;
int RR_HIGH = 0;
int RR_MISS = 0;

int SPKF = 0;
int NPKF = 0;
int THRESHOLD1 = 0;
int THRESHOLD2 = 0;


// Initiating first element of linked list
struct PEAK* create_peakList(int index, int val) {
    struct PEAK *ptr = (struct PEAK*)malloc(sizeof(struct PEAK));
    if(NULL == ptr) {
        return NULL;
    }
    ptr->atIndex = index;
    ptr->type = 0;
    ptr->value = val;

    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}


// Adding node to beginning of list
struct PEAK* add_to_list(int index, int val) {

    if(NULL == head) {
        return (create_peakList(index, val));
    }

    struct PEAK *ptr = (struct PEAK*)malloc(sizeof(struct PEAK));


    ptr->value = val;
    ptr->atIndex = index;
    ptr->next = NULL;

    ptr->next = head;
    head = ptr;

    return ptr;
}


void print_latest(int backwards)
{
    struct PEAK *ptr = head;

    int i;
    for (i=0; i<backwards; i++){
        if(NULL == ptr) {
            break;
        }
        printf("\ntime: %i, Value: %d \n",ptr->atIndex, ptr->value);
        ptr = ptr->next;
    }
    return;
}

int RRfind(BUFFER* inputData, int runCount)
{
    int x2 = readData(inputData, 2);
    int x1 = readData(inputData, 1);
    int x0 = readData(inputData, 0);

    // Checks for peak
    //printf("\nX0: %i\nX1: %i\nX2 %i\n\n", x0, x1, x2);
    if (x0 < x1 && x1 > x2) {          // Could be expanded to 5 evalpoints allowing for multiple equal val
        add_to_list(runCount-1, x1); // overflow vulnerable

        printf("Printing latest 3");
        print_latest(3);
        return 1;
    }
    return 0;
}



void print_list(void)
{
    struct PEAK *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
        printf("\ntime: %i, Value: %d \n",ptr->atIndex, ptr->value);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}




int RRdetermine(void)
{
    printf("Prove to me that you are indeed a peak!\n");
    return 0;
}

int RRsearchback(void)
{
    printf("No peaks in sight!.. I guess I should look closer\n");
    return 0;
}
