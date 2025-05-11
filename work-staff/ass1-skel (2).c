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


/**********************************************************************/

/* put your function prototypes here */

/* plus two free gifts if you want them, to help with the sorting
*/



void	int_swap(int *p1, int *p2);
void	dbl_swap(double *p1, double *p2);


typedef struct {
    int apartment_number;
    int room_type;
    int room_num;
    double xsize;
    double ysize;
    double area;
} Room;

/**********************************************************************/


char* get_room_type_name(int room_type) {
    switch (room_type) {
        case 1: return "HALLWAY";
        case 2: return "BEDROOM";
        case 3: return "LIVING";
        case 4: return "BATHROOM";
        case 5: return "KITCHEN";
        case 6: return "LAUNDRY";
        case 7: return "STORAGE";
        case 8: return "GARAGE";
        case 9: return "VALCONY";
        default: return "ERROR";
    }
}

double get_total_area(Room rooms[], int count) {
    double total_area = 0;
    for (int i = 0; i < count; i++) {
        total_area += rooms[i].area;
    }
    return total_area;
}


int main(int argc, char *argv[]) {
    Room rooms[MAX_ROOMS];
    int count;

    // Stage 1: 处理第一个公寓
    process_first_apartment(rooms, &count);
    print_stage1(rooms, count);

    // Stage 2: 处理所有公寓
    process_all_apartments(rooms, &count);
    insertion_sort(rooms, count);
    print_stage2(rooms, count);

    // Stage 3: 输出最终统计表
    print_stage3(rooms, count);

    return EXIT_SUCCESS;
}


/**********************************************************************/

/* add all your functions here, one function per major (or minor!)
   task
*/


// Stage 1
void insertion_sort(Room rooms[], int count) {
    for (int i = 1; i < count; i++) {
        Room key = rooms[i];
        int j = i - 1;
        while (j >= 0 && (rooms[j].room_type > key.room_type || 
            (rooms[j].room_type == key.room_type && rooms[j].room_num > key.room_num))) {
            rooms[j + 1] = rooms[j];
            j--;
        }
        rooms[j + 1] = key;
    }
}

// Stage 1: 处理第一个公寓
void process_first_apartment(Room rooms[], int *count) {
    *count = 0;
    while (scanf("%d", &rooms[*count].apartment_number) && rooms[*count].apartment_number != -1) {
        scanf("%d %d %lf %lf", &rooms[*count].room_type, &rooms[*count].room_num, 
              &rooms[*count].xsize, &rooms[*count].ysize);
        rooms[*count].area = rooms[*count].xsize * rooms[*count].ysize;
        (*count)++;
    }
}

// Stage 2: 处理所有公寓
void process_all_apartments(Room rooms[], int *count) {
    *count = 0;
    while (scanf("%d", &rooms[*count].apartment_number) && rooms[*count].apartment_number != -1) {
        scanf("%d %d %lf %lf", &rooms[*count].room_type, &rooms[*count].room_num, 
              &rooms[*count].xsize, &rooms[*count].ysize);
        rooms[*count].area = rooms[*count].xsize * rooms[*count].ysize;
        (*count)++;
    }
}

// Stage 1 输出
void print_stage1(Room rooms[], int count) {
    printf("Apartment %d\n", rooms[0].apartment_number);
    printf("-------------\n");
    for (int i = 0; i < count; i++) {
        if (i > 0 && rooms[i].room_type == rooms[i - 1].room_type && rooms[i].room_num == rooms[i - 1].room_num) {
            rooms[i - 1].area += rooms[i].area;
            continue;
        }
        printf("%s %d %.2f x %.2f %.2f\n", get_room_type_name(rooms[i].room_type), 
               rooms[i].room_num, rooms[i].xsize, rooms[i].ysize, rooms[i].area);
    }
    printf("Total area %.2f meters^2\n", get_total_area(rooms, count));
}

// Stage 2 输出
void print_stage2(Room rooms[], int count) {
    for (int i = 0; i < count; i++) {
        if (i == 0 || rooms[i].apartment_number != rooms[i - 1].apartment_number) {
            printf("\nApartment %d\n", rooms[i].apartment_number);
            printf("-------------\n");
        }
        printf("%s %d %.2f x %.2f %.2f\n", get_room_type_name(rooms[i].room_type), 
               rooms[i].room_num, rooms[i].xsize, rooms[i].ysize, rooms[i].area);
    }
}

// Stage 3 输出
void print_stage3(Room rooms[], int count) {
    int current_apartment = rooms[0].apartment_number;
    double dry_area = 0, wet_area = 0, utility_area = 0, total_area = 0;

    for (int i = 0; i < count; i++) {
        if (rooms[i].apartment_number != current_apartment) {
            printf("%d %.2f %.2f%% %.2f %.2f%% %.2f %.2f%%\n", current_apartment, 
                   dry_area, (dry_area / total_area) * 100, 
                   wet_area, (wet_area / total_area) * 100, 
                   utility_area, (utility_area / total_area) * 100);
            current_apartment = rooms[i].apartment_number;
            dry_area = wet_area = utility_area = total_area = 0;
        }
        total_area += rooms[i].area;
        switch (room_categories[rooms[i].room_type]) {
            case DRY: dry_area += rooms[i].area; break;
            case WET: wet_area += rooms[i].area; break;
            case UTILITY: utility_area += rooms[i].area; break;
        }
    }
    // 输出最后一个公寓的统计信息
    printf("%d %.2f %.2f%% %.2f %.2f%% %.2f %.2f%%\n", current_apartment, 
           dry_area, (dry_area / total_area) * 100, 
           wet_area, (wet_area / total_area) * 100, 
           utility_area, (utility_area / total_area) * 100);
}






/**********************************************************************/

/* this one taken directly from the textbook, and is here if you want it
*/

void
int_swap(int *p1, int *p2) {
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/**********************************************************************/

/* and this one is also provided as a "free gift", use it if you want
*/

void
dbl_swap(double *p1, double *p2) {
	double tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/**********************************************************************/
