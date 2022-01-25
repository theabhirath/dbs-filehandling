#include "helper.h"

/* get semester name using semester number */
void get_semester_name(int semester, char semester_name[]){
    int length = snprintf(NULL, 0, "%d", semester);
    char* sem_num = malloc(length + 1);
    snprintf(sem_num, length + 1, "%d", semester);
    strcpy(semester_name, "Semester ");
    strcat(semester_name, sem_num);
    free(sem_num);
}

/* display the GPA for a given semester */
void display_sgpa(int semester, int credits[], char grades[][MAXCHAR], int nlines){
    char semester_name[MAXCHAR];
    get_semester_name(semester, semester_name);
    
    double semester_gpa = calculate_sgpa(credits, grades, nlines);
    printf("GPA for %s:\t", semester_name);
    if (isnan(semester_gpa)) {
        printf("CLR\n");
    } else {
        printf("%.2f\n", semester_gpa);
    }
}

/* calculate and display the cumulative GPA */
void display_cgpa(char files[][MAXCHAR], int nfiles){
    double cgpa = calculate_cgpa(files, nfiles);
    printf("Cumulative GPA: \t");
    if (cgpa == 0.0){
        printf("CLR\n");
    } else {
        printf("%.2f\n", cgpa);
    }
}

/* display the gradesheet of a particular semester */
void display_semester_gradesheet(int semester, char files[][MAXCHAR], 
                                int nfiles, char course_numbers[][MAXCHAR], 
                                char course_names[][MAXCHAR], int credits[], 
                                char grades[][MAXCHAR], int nlines)
{
    if(semester < 1 || semester > nfiles){
        printf("Error: invalid semester. Please try again.\n");
        return;
    }

    char semester_name[MAXCHAR];
    get_semester_name(semester, semester_name);

    /* store courses, credits and grades in a table */
    struct table_t* table = table_init(stdout, semester_name, 1);
    table_row(table, "%s%s%s%s", "Course Number", "Course Name", "Credits", "Grade");
    table_separator(table);
    for(int i = 0; i < nlines; i++){
        table_row(table, "%s%s%d%s", course_numbers[i], course_names[i], credits[i], grades[i]);
    }

    // print the table
    table_commit(table);
    printf("\n");

    /* print the gpa of the semester */
    display_sgpa(semester, credits, grades, nlines);
}