/* Program to compute floor areas and categories for apartments.

   Skeleton written by Alistair Moffat, ammoffat@unimelb.edu.au,
   April 2025, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by AI tools such as CharGPT, or that was
   developed in collaboration with other students or non-students, constitutes
   Academic Misconduct, and may be penalized by mark deductions, or by other
   penalties determined via the University of Melbourne Academic Honesty
   Policy, as described at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Chi Zhang
   Dated:     10/04/2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**********************************************************************/

/* some helpful constants, as a hint to get you started */

/* the number of different room types, plus one for simplicity */

#define NUMROOMTYPES 10

/* the numbers associated with the nine room types, these are not
   actually explicitly used in the program, but just for completeness */

#define UNUSED   0
#define HALLWAY  1
#define BEDROOM  2
#define LIVING   3
#define BATHROOM 4
#define KITCHEN  5
#define LAUNDRY  6
#define STORAGE  7
#define GARAGE   8
#define BALCONY  9

/* overall room categories, and mapping from room types to categories */

#define NUMCATEGORIES 3
#define DRY     0
#define WET     1
#define UTILITY 2

/* fixed global arrays with initializers are permitted as a form of
   contants, can you see how you are intended to use this array?
*/

int roomcategories[NUMROOMTYPES] =
	{UNUSED, DRY, DRY, DRY, WET, WET, WET, UTILITY, UTILITY, UTILITY};

/* and now add your own constants here */
#define MAX_ROOMS 200
#define MAX_APARTMENTS 100


/**********************************************************************/


typedef struct {
    int apartment_number;
    int room_type;
    int room_num;
    double xsize;
    double ysize;
    double area;
} Room_t;

typedef struct {
    int apartment_number;
    double dry_area;
    double wet_area;
    double utility_area;
    double total_area;
} Apartment_t;

void int_swap(int *p1, int *p2);
void dbl_swap(double *p1, double *p2);
char* get_room_type_name(int room_type);
void insertion_sort(Room_t rooms[], int count);
void process_apartments(Room_t rooms[], int *count);
void print_apartment(Room_t rooms[], int start, int end);
double get_total_area(Room_t rooms[], int start, int end);
void print_stage3(Room_t rooms[], int count);
void calculate_apartment_stats(Room_t rooms[], 
    int count, Apartment_t apartments[], int *apt_count);

/**********************************************************************/

/* Function to get the name of a room type based on its code */
char* get_room_type_name(int room_type) {
    switch (room_type) {
        case 1: return "Hallway";
        case 2: return "Bedroom";
        case 3: return "Living";
        case 4: return "Bathroom";
        case 5: return "Kitchen";
        case 6: return "Laundry";
        case 7: return "Storage";
        case 8: return "Garage";
        case 9: return "Balcony";
        default: return "Error";
    }
}

/* Main function */
int main(int argc, char *argv[]) {
    Room_t rooms[MAX_ROOMS];
    int count = 0;
    
    /* Process all apartments in the input */
    process_apartments(rooms, &count);
    
    /* Print Stage 3 */
    print_stage3(rooms, count);
    
    /* Print tadaa */
    printf("\ntadaa!\n");
    
    return EXIT_SUCCESS;
}

/* Function - process all apartments from input text */
void process_apartments(Room_t rooms[], int *count) {
    int apt_number, room_type, room_num;
    double xsize, ysize;
    int apartment_start = 0;
    
    *count = 0;
    
    /* Read the first apartment unit */
    while (scanf("%d", &apt_number) == 1 && apt_number != -1) {
        /* Store the apartment unit */
        rooms[*count].apartment_number = apt_number;
        
        /* Process all rooms in this apartment */
        while (1) {
            /* Read room details */
            if (scanf("%d", &room_type) != 1) {
                break;
            }
            
            /* Check for sentinel value */
            if (room_type == -1) {
                break;
            }
            
            /* Read remaining room data */
            scanf("%d %lf %lf", &room_num, &xsize, &ysize);
            
            /* Store room data */
            rooms[*count].room_type = room_type;
            rooms[*count].room_num = room_num;
            rooms[*count].xsize = xsize;
            rooms[*count].ysize = ysize;
            rooms[*count].area = xsize * ysize;
            
            /* Move to next room */
            (*count)++;
            
            /* Keep the apartment number the same for this room */
            rooms[*count].apartment_number = apt_number;
        }
        
        /* Sort the rooms of this apartment by room type and room number */
        insertion_sort(rooms + apartment_start, *count - apartment_start);
        
        /* Print out this apartment's details */    
        print_apartment(rooms, apartment_start, *count);
        
        /* Set the start index for the next apartment */
        apartment_start = *count;
    }
}

/* Function - sort rooms using insertion sort */
void insertion_sort(Room_t rooms[], int count) {
    int i, j;
    Room_t key;
    
    for (i = 1; i < count; i++) {
        key = rooms[i];
        j = i - 1;
        
        /* Move elements that are greater than key to one position ahead */
        while (j >= 0 && (rooms[j].room_type > key.room_type || 
               (rooms[j].room_type == key.room_type &&
                 rooms[j].room_num > key.room_num))) {
            rooms[j + 1] = rooms[j];
            j--;
        }
        rooms[j + 1] = key;
    }
}

/* Function - print details of an apartment */
void print_apartment(Room_t rooms[], int start, int end) {
    int i;
    int current_type = -1;
    int current_num = -1;
    double room_area = 0.0;
    
    /* Print apartment unit */
    printf("Apartment %d\n", rooms[start].apartment_number);
    printf("-------------");
    
    for (i = start; i < end; i++) {
        /* If this is a new room with different unit */
        if (current_type != rooms[i].room_type || 
            current_num != rooms[i].room_num) {
            /* If not the last room, print the previous room's total area */
            if (current_type != -1) {
                printf("%5.2f", room_area);
            }
            
            /* Start a new room */
            current_type = rooms[i].room_type;
            current_num = rooms[i].room_num;
            room_area = rooms[i].area;
            
            /* Print room details */
            printf("\n%-8s %d    %.2f  x  %.2f   ", 
                   get_room_type_name(rooms[i].room_type),
                   rooms[i].room_num,
                   rooms[i].xsize,
                   rooms[i].ysize);
        } else {
            /* Add area to the current room's total area */
            room_area += rooms[i].area;
            
            /* Print "---" for same room bt not the last rectangle */
            printf(" ---\n%-8s %d    %.2f  x  %.2f   ", 
                   get_room_type_name(rooms[i].room_type),
                   rooms[i].room_num,
                   rooms[i].xsize,
                   rooms[i].ysize);
            continue;
        }
    }
    
    /* Print the last room's area*/
    if (current_type != -1) {
        printf("%5.2f\n", room_area);
    }
    
    /* Print total apartment area */
    printf("Total area                   %6.2f meters^2\n\n",
         get_total_area(rooms, start, end));
}

/* Function - calculate total area of an apartment */
double get_total_area(Room_t rooms[], int start, int end) {
    double total = 0.0;
    int i;
    
    for (i = start; i < end; i++) {
        total += rooms[i].area;
    }
    
    return total;
}

/* Function - calculate percentage of 3 types of area for each apartment */
void calculate_apartment_stats(Room_t rooms[], 
    int count, Apartment_t apartments[], int *apt_count) {
    int i;
    int current_apt = -1;
    
    *apt_count = 0;
    
    for (i = 0; i < count; i++) {
        /* If this is a new apartment */
        if (rooms[i].apartment_number != current_apt) {
            /* Start tracking a new apartment */
            current_apt = rooms[i].apartment_number;
            apartments[*apt_count].apartment_number = current_apt;
            apartments[*apt_count].dry_area = 0.0;
            apartments[*apt_count].wet_area = 0.0;
            apartments[*apt_count].utility_area = 0.0;
            apartments[*apt_count].total_area = 0.0;
            
            (*apt_count)++;
        }
        
        /* Add room area to appropriate category */
        apartments[*apt_count - 1].total_area += rooms[i].area;
        
        if (roomcategories[rooms[i].room_type] == DRY) {
            apartments[*apt_count - 1].dry_area += rooms[i].area;
        } else if (roomcategories[rooms[i].room_type] == WET) {
            apartments[*apt_count - 1].wet_area += rooms[i].area;
        } else if (roomcategories[rooms[i].room_type] == UTILITY) {
            apartments[*apt_count - 1].utility_area += rooms[i].area;
        }
    }
}

/* Function - print the summary table */
void print_stage3(Room_t rooms[], int count) {
    Apartment_t apartments[MAX_APARTMENTS];
    int apt_count;
    int i;
    
    /* Calculate Percentage for each apartment */
    calculate_apartment_stats(rooms, count, apartments, &apt_count);
    
    /* Print table header and lines */
    printf("+-------+----------------+----------------+----------------+\n");
    printf("| Apart |    Dry areas   |    Wet areas   |  Utility areas |\n");
    printf("+-------+----------------+----------------+----------------+\n");
    
    /* Print table rows */
    for (i = 0; i < apt_count; i++) {
        printf("|  %3d  | %6.2f %5.1f%%  | %6.2f %5.1f%%  | %6.2f %5.1f%%  |\n",
               apartments[i].apartment_number,
               apartments[i].dry_area,
               (apartments[i].dry_area / apartments[i].total_area) * 100.0,
               apartments[i].wet_area,
               (apartments[i].wet_area / apartments[i].total_area) * 100.0,
               apartments[i].utility_area,
               (apartments[i].utility_area / apartments[i].total_area) * 100.0);
    }
    
    /* Print table lines*/
    printf("+-------+----------------+----------------+----------------+\n");
}

/**********************************************************************/

/* this one taken directly from the textbook, and is here if you want it*/

void
int_swap(int *p1, int *p2) {
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/**********************************************************************/

/* and this one is also provided as a "free gift", use it if you want*/

void
dbl_swap(double *p1, double *p2) {
	double tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/**********************************************************************/
// Programming is fun!