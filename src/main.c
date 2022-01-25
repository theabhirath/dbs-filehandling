#include "helper.h"

int main(void){

    // index all files in the grades directory
    char files[MAXN][MAXCHAR];
    int nfiles;
    if(make_file_array(files, &nfiles)){
        printf("Error: could not make file array\n");
        return 1;
    }

    printf("Welcome to the GPA calculator!\n");
    // main menu
    int choice;
    do{
        printf("1. Calculate the GPA for a semester.\n");
        printf("2. Calculate the cumulative GPA.\n");
        printf("3. Display information for a particular course.\n");
        printf("4. Display the gradesheet of a semester.\n");
        printf("5. Exit.\n");
        printf("\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        printf("\n");

        // initialize variables
        char course_numbers[MAXN][MAXCHAR];
        char course_names[MAXN][MAXCHAR];
        int credits[MAXN];
        char grades[MAXN][MAXCHAR];
        int nlines;
        int semester;
        char filename[MAXCHAR];
        char course_search[MAXCHAR];

        switch(choice){
            case 1:
                printf("Enter the semester you want to calculate GPA for (1-%d): ", nfiles);
                scanf("%d", &semester);

                // decide which file to read from the grades folder  
                strcpy(filename, files[nfiles - semester]);

                /* read the CSV file */
                if(read_csv(filename, course_numbers, course_names, credits, grades, &nlines)){ 
                    printf("\n");
                    display_sgpa(semester, credits, grades, nlines);
                    break;
                } else{
                    printf("Error reading CSV file\n");
                    return 1;
                }
            case 2:
                // calculate and display the cumulative GPA
                display_cgpa(files, nfiles);
                break;
            case 3:
                // search for a course
                printf("Enter the course number you want to search for: ");
                scanf(" %[^\n]s", course_search);

                int result = search_course(course_search, files, nfiles);
                if (result == 1){
                    printf("Error: course not found\n");
                }
                break;
            case 4:
                printf("Enter the semester you want to display the gradesheet for (1-%d): ", nfiles);
                scanf("%d", &semester);

                // decide which file to read from the grades folder
                strcpy(filename, files[nfiles - semester]);

                /* read the CSV file */
                if(read_csv(filename, course_numbers, course_names, credits, grades, &nlines)){
                    printf("\n");
                    display_semester_gradesheet(semester, files, nfiles, course_numbers, course_names,
                                            credits, grades, nlines);
                } else{
                    printf("Error reading CSV file\n\n");
                    return 1;
                }
                break;
            case 5:
                printf("Exiting...\n\n");
                break;
            default:
                printf("Error: invalid choice. Please try again.\n\n");
                break;
        }
        // delay for user to read the output
        printf("Press enter to continue...");
        printf("\n");
        getchar();
        getchar();
    } while(choice != 5);
}