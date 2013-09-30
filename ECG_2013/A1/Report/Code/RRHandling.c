#include <stdio.h>
#include <stdlib.h>

#define MINSAMPLES 3 // Minimum number of samples before updating variables
#define VERBOSE 1

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

int missed_peaks = 0;



// Adding node to beginning of list
struct PEAK* add_to_peaks(int clock, int val, int type) {

    struct PEAK *ptr = (struct PEAK*)malloc(sizeof(struct PEAK));

    ptr->value = val;
    ptr->clock = clock;
    ptr->type = type;
    ptr->next = NULL;

    if(NULL == head) head = curr = ptr;
    else {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}









int peak_prev_clock(int type)
{
    struct PEAK *ptr = head;
    ptr = ptr->next; // Skipping current element
    while (NULL != ptr){
        if (ptr->type == type) {
            return ptr->clock;
        };
        ptr = ptr->next;
    }
    return 0;
}





int peak_sumOfType(int type)
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


    int i = 0;

    while (NULL != ptr){
        i++;
        if (ptr->type >= 0) {
            if (ptr->value > THRESHOLD2) {
                ptr->type = 2;
                printf("Searchback'ed %i levels deep\n", i);
                return ptr;
            }
        };

        ptr = ptr->next;
    }
    return NULL;
}



int peak_average_interval(int type, int amount)
{

    struct PEAK *ptr = head;
    if (NULL != ptr) {
        int clock = ptr->clock;

        int clockSum = 0;
        int i = 0;
        ptr = ptr->next;
        while (NULL != ptr){
           if (ptr->type >= type) {
               int newClock = ptr->clock;
               int tempDiff = clock - newClock;

               clockSum += tempDiff; // Summing value of found peaks
               clock = newClock;
               i++;
           };
           if (amount == i) break;
           ptr = ptr->next;
        }
        if (i) {
            int avg = clockSum/i;
            return avg;
        }
    }
    return 0;
}






void update_RpeakVariables(struct PEAK* ptr) {
    // get latest 8 RR-intervals
    if (NULL != ptr) {
        int peakVal = ptr->value;
        SPKF = 0.125 * peakVal + 0.875 * NPKF;
        RR_AVERAGE2 = peak_average_interval(2, 8);
        RR_AVERAGE1 = peak_average_interval(1, 8);
        RR_LOW = 0.92 * RR_AVERAGE2;
        RR_HIGH = 1.16 * RR_AVERAGE2;
        RR_MISS = 1.66 * RR_AVERAGE2;
        THRESHOLD1 = NPKF + 0.25 * (SPKF-NPKF);

        if (VERBOSE > 1){
            printf("SPKF: %i\nRR_AVERAGE2: %i\nRR_AVERAGE1: %i\nRR_LOW: %i\nRR_HIGH: %i\nRR_MISS: %i\nTHRESHOLD1: %i\n",
                   SPKF,
                   RR_AVERAGE2,
                   RR_AVERAGE1,
                   RR_LOW,
                   RR_HIGH,
                   RR_MISS,
                   THRESHOLD1);
        }
    }
    else printf("ERROR:update_RpeakVariables::input ptr == NULL\n");

    return;
}


void update_searchbackVariables(struct PEAK* ptr) {
    // get latest 8 RR-intervals
    if (NULL != ptr) {
        int peakVal = ptr->value;
        SPKF = 0.25 * peakVal + 0.75 * SPKF;
        RR_AVERAGE1 = peak_average_interval(1, 8);
        RR_LOW = 0.92 * RR_AVERAGE1;
        RR_HIGH = 1.16 * RR_AVERAGE1;
        RR_MISS = 1.66 * RR_AVERAGE1;

        THRESHOLD1 = NPKF + 0.25 * (SPKF-NPKF);
        THRESHOLD2 = 0.5 * THRESHOLD1;

        if (VERBOSE > 1){
            printf("\nUpdate_searchbackVariables:\nSPKF: %i\nRR_AVERAGE1: %i\nRR_AVERAGE2: %i\nRR_LOW: %i\nRR_HIGH: %i\nRR_MISS: %i\nTHRESHOLD1: %i\nTHRESHOLD2: %i\n",
                   SPKF,
                   RR_AVERAGE1,
                   RR_AVERAGE2,
                   RR_LOW,
                   RR_HIGH,
                   RR_MISS,
                   THRESHOLD1,
                   THRESHOLD2);
        }
    }
    else {
        printf("ERROR:update_searchbackVariables::input ptr == NULL\n");
    }
    return;
}



void update_thresholdVariables( struct PEAK* ptr ) {
    if (NULL != ptr) {
        int peakVal = ptr->value;
        NPKF = 0.125 * peakVal + 0.875 * NPKF;
        THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
        THRESHOLD2 = 0.5 * THRESHOLD1;
    }
    else printf("ERROR:update_thresholdVariables:: input ptr == NULL\n");

    return;
}


/***** Sampling 3 points on each side of test-point *****/
int checkPeak(int samples[]) {

    if ( samples[0] < samples[1] &&
         samples[1] < samples[2] &&
         samples[2] < samples[3] &&
         samples[3] > samples[4] &&
         samples[4] > samples[5] &&
         samples[5] > samples[6] ) return 1;

    /*
    if (
         samples[2] < samples[3] &&
         samples[3] > samples[4] ) return 1;*/
    return 0;
}






int RRcalculate(int x1, int samples[], int clock)
{

    struct PEAK *ptr = NULL;

    // Checks for peak
    if ( checkPeak(samples) ) {
        ptr = add_to_peaks(clock-1, x1, 0); // Point is a peak. Save in list, type 0

        if (ptr->value > THRESHOLD1) {
            ptr->type = 1; // Classifying as R-peak


            //printf("clock: %i, r-peak val: %i\n", clock-1, x1);
            int lastClock = peak_prev_clock(2);
            int timediff = clock - lastClock;


            /************ USER output *************/
            // For every R-peak print this:
            if (VERBOSE == 1) {
                printf("Heartrate: %3i bpm, Intencity: %4i, Last peak: %.3fs", (int) (1.0/RR_AVERAGE2*60.0*250.0), x1, timediff/250.0);
                //printf("Heartrate: %3i bpm, value: %4i, Since last peak: %i s", (RR_AVERAGE2*60)/250, x1, timediff);
                if (x1 < 2000) printf("   ## Heartintensity below minimum! ##");
                if (missed_peaks > 5) printf("   ## Missed more than 5 peaks. Dude, you're dying! ##");
                printf("\n");
            }
            else if (VERBOSE == 0) {
                FILE *file;
                file = fopen("output.txt","a+");
                fprintf(file,"Heartrate: %3i bpm, Intencity: %4i, Last peak: %.3fs", (int) (1.0/RR_AVERAGE2*60.0*250.0), x1, timediff/250.0);
                if (x1 < 2000) fprintf(file,", WARNING. Heartintensity below minimum!");
                fprintf(file,"\n");
                fclose(file);
            }
            /*************************************/


            if (RR_LOW < timediff && timediff < RR_HIGH ) {
                if (missed_peaks > 0) missed_peaks--;

                ptr->type = 2; // Classify as regular R-peak
                // Only updating variables if more than MINSAMPLES are available

                if (peak_sumOfType(2) >= MINSAMPLES) {
                    update_RpeakVariables( ptr );
                }
            }
            else if (RR_MISS < timediff){
                // searchback
                update_searchbackVariables( peak_searchback() );
            }
            else {
                if (missed_peaks < 10) missed_peaks++;
            }
        }
        else {
            update_thresholdVariables( ptr );
        }
    }
    return 0;
}




/* Function for determining size of PEAK array */
int sizeof_peaks() {
    struct PEAK *ptr = head;
    int size = 0;
    int i = 0;

    while(ptr != NULL)
    {
        size += sizeof(struct PEAK);
        ptr = ptr->next;
        i++;
    }
    printf("Size of stuff: %i\n", size);
    printf("elements in peak: %i\n", i);

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

