/*  Hvor mange peaks skal man gemme i listen. Hvad fylder de,
 *  hvor langt bagud bør man søge før det antages at patienten er død
 */

#include <stdio.h>
#include <stdlib.h>
#define MINSAMPLES 8 // Minimum number of samples before updating variables

struct PEAK {
    int clock;          // If older than buffer size cannot be reevaluated
    int type;           // -1 noise, 0 peak, 1 R-peak, 2 regular R-peak
    int value;          // speaks for itself
    struct PEAK *next;
};


struct PEAK *head = NULL;
struct PEAK *curr = NULL;


int RR_AVERAGE1 = 250;
int RR_AVERAGE2 = 250;
int RR_LOW = 100;
int RR_HIGH = 200;
int RR_MISS = 400;

int SPKF = 0;
int NPKF = 0;
int THRESHOLD1 = 2000;
int THRESHOLD2 = 0;


// Initiating first element of linked list
struct PEAK* create_peakList(int clock, int val, int type) {
    struct PEAK *ptr = (struct PEAK*)malloc(sizeof(struct PEAK));
    if(NULL == ptr) {
        return NULL;
    }
    ptr->clock = clock;
    ptr->type = type;
    ptr->value = val;

    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}


// Adding node to beginning of list
struct PEAK* add_to_peaks(int clock, int val, int type) {

    if(NULL == head) {
        return (create_peakList(clock, val, type));
    }

    struct PEAK *ptr = (struct PEAK*)malloc(sizeof(struct PEAK));

    ptr->value = val;
    ptr->clock = clock;
    ptr->type = type;
    ptr->next = NULL;

    ptr->next = head;
    head = ptr;

    return ptr;
}









int peak_clock_by_type(int type)
{
    struct PEAK *ptr = head;
    ptr = ptr->next; // Skipping current element
    if (NULL != ptr) {
        while (NULL != ptr){
            if (ptr->type == type) {
                return ptr->clock;
            };
            ptr = ptr->next;
        }
    }
    return 0;
}



int peak_numOfType(int type)
{
    struct PEAK *ptr = head;
    int count = 0;
    while (NULL != ptr){
        if (ptr->type >= type) {
            count++;
        };
        ptr = ptr->next;
    }
    return count;
}



struct PEAK* peak_searchback()
{
    struct PEAK *ptr = head;

    while (NULL != ptr){
        if (ptr->type <= 0) {
            if (ptr->value > THRESHOLD2) {
                ptr->type = 1;
                return ptr;
            }
        };
        ptr = ptr->next;
    }
    return ptr;
}



int peak_average_interval(int type, int amount)
{

    struct PEAK *ptr = head;
    if (NULL != ptr) {
        int clock = ptr->clock;
        printf("first clock: %i\n", clock);

        int clockSum = 0;
        int i = 0;
        ptr = ptr->next;
        while (NULL != ptr){
           if (ptr->type >= type) {
               printf("Peak value: %i\n", ptr->value);
               int newClock = ptr->clock;
               int tempDiff = clock - newClock;
               printf("newClock: %i\noldClock: %i\ntempDiff: %i\n", newClock, clock, tempDiff);
               clockSum += tempDiff; // Summing value of found peaks
               clock = newClock;
               i++;
           };
           if (amount == i) break;
           ptr = ptr->next;
        }
        if (i) {
            int avg = clockSum/i;
            printf("Average of lastest %i peak(s) of type %i: %i\n", i, type, avg);
            return avg;
        }
    }
    return 0;
}






void update_RpeakVariables(struct PEAK* ptr) {
    // get latest 8 RR-intervals
    int peakVal = ptr->value;
    SPKF = 0.125 * peakVal + 0.875 * NPKF;
    RR_AVERAGE2 = peak_average_interval(2, 8);
    RR_AVERAGE1 = peak_average_interval(1, 8);
    RR_LOW = 0.92 * RR_AVERAGE2;
    RR_HIGH = 1.16 * RR_AVERAGE2;
    RR_MISS = 1.66 * RR_AVERAGE2;
    THRESHOLD1 = NPKF + 0.25 * (SPKF-NPKF);

    printf("SPKF: %i\nRR_AVERAGE2: %i\nRR_AVERAGE1: %i\nRR_LOW: %i\nRR_HIGH: %i\nRR_MISS: %i\nTHRESHOLD1: %i\n",
           SPKF,
           RR_AVERAGE2,
           RR_AVERAGE1,
           RR_LOW,
           RR_HIGH,
           RR_MISS,
           THRESHOLD1);


    return;
}


void update_searchbackVariables(struct PEAK* ptr) {
    printf("Setting searchback variables...\n");
    // get latest 8 RR-intervals
    int peakVal = ptr->value;
    SPKF = 0.25 * peakVal + 0.75 * SPKF;
    RR_AVERAGE1 = peak_average_interval(1, 8);
    RR_LOW = 0.92 * RR_AVERAGE1;
    RR_HIGH = 1.16 * RR_AVERAGE1;
    RR_MISS = 1.66 * RR_AVERAGE1;
    THRESHOLD1 = NPKF + 0.25 * (SPKF-NPKF);
    THRESHOLD2 = 0.5 * THRESHOLD1;

    printf("SPKF: %i\nRR_AVERAGE1: %i\nRR_LOW: %i\nRR_HIGH: %i\nRR_MISS: %i\nTHRESHOLD1: %i\nTHRESHOLD2: %i\n",
           SPKF,
           RR_AVERAGE1,
           RR_LOW,
           RR_HIGH,
           RR_MISS,
           THRESHOLD1,
           THRESHOLD2);
    return;
}



void update_peakThreshold( struct PEAK* ptr ) {
    int peakVal = ptr->value;
    NPKF = 0.125 * peakVal + 0.875 * NPKF;
    THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
    THRESHOLD2 = 0.5 * THRESHOLD1;

    return;
}






int RRcalculate(int x0, int x1, int x2, int clock)
{

    struct PEAK *ptr = NULL;

    // Checks for peak
    if (x0 < x1 && x1 > x2) {
        ptr = add_to_peaks(clock-1, x1, 0); // Point is a peak. Save in list, type 0
        printf("peak0 - value: %i, clock: %i\n", x1, clock-1);
        /*
        if (ptr->value > THRESHOLD1) {
            ptr->type = 1; // Classifying as R-peak


            int lastClock = peak_clock_by_type(2);
            int timediff = clock - lastClock;

            if (RR_LOW < timediff && timediff < RR_HIGH ) {
                ptr->type = 2; // Classify as regular R-peak
                // Only updating variables if more than MINSAMPLES are available
                int numOfTypes = peak_numOfType(2);
                if (numOfTypes >= MINSAMPLES) {
                    update_RpeakVariables( ptr );
                }
            }
            else if (timediff > RR_MISS){
                // searchback
                struct PEAK* searchbackPeak = peak_searchback();
                if (NULL != searchbackPeak) update_searchbackVariables(searchbackPeak);
                else printf("No match on searchback\n");

            }
            else printf("Timediff didn't match anything. Timediff: %i\n", timediff);
        }
        else {
            update_peakThreshold( ptr );
        }
        */
    }
    else printf("NonPeak value: %i\n", x1);
    return 0;
}












/******* Mainly for testing purposes *********/
void print_list(void)
{
    struct PEAK *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
        printf("\ntime: %i, Value: %d \n",ptr->clock, ptr->value);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}



int RRsearchback(void)
{
    printf("No peaks in sight!.. I guess I should look closer\n");
    return 0;
}


void print_latest(int backwards)
/*
 * Prints the latest [backwards] number of peaks in list
 * Latest first
 */
{
    struct PEAK *ptr = head;

    int i;
    for (i=0; i<backwards; i++){
        if(NULL == ptr) {
            break;
        }
        printf("\ntime: %i, Value: %d, type: %i \n",ptr->clock, ptr->value, ptr->type);
        ptr = ptr->next;
    }
    return;
}

