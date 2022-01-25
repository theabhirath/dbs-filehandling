#include "helper.h"

/* calculate the GPA for a semester by taking the weighted average of the grades. */
int calculate_grade_points(int credits[], char grades[][MAXCHAR], int nlines, 
                            int* total_credits){
    int total_grade_points = 0;
    int grade_points;
    int credits_per_course;
    for(int i = 0; i < nlines; i++){
        /* convert the letter grade to a grade point */
        if(strcmp(grades[i], "A") == 0){
            grade_points = 10;
        } else if(strcmp(grades[i], "A-") == 0){
            grade_points = 9;
        } else if(strcmp(grades[i], "B") == 0){
            grade_points = 8;
        } else if(strcmp(grades[i], "B-") == 0){
            grade_points = 7;
        } else if(strcmp(grades[i], "C") == 0){
            grade_points = 6;
        } else if(strcmp(grades[i], "C-") == 0){
            grade_points = 5;
        } else if(strcmp(grades[i], "D") == 0){
            grade_points = 4;
        } else if(strcmp(grades[i], "E") == 0){
            grade_points = 2;
        } else if(strcmp(grades[i], "CLR") == 0){
            grade_points = 0;
        } else if(strcmp(grades[i], "I") == 0){
            grade_points = 0;
        } else {
            printf("Error: invalid grade\n");
            return 1;
        }
        /* calculate the grade points for each course. If the grade is I/CLR, then the credits are 
        not counted in the GPA calculation */
        if(strcmp(grades[i], "I") != 0 && strcmp(grades[i], "CLR") != 0){
            credits_per_course = credits[i];
            total_grade_points += grade_points * credits_per_course;
            *total_credits += credits_per_course;
        }
    }
    return total_grade_points;
}

/* calculate the GPA for a given semester */
double calculate_sgpa(int credits[], char grades[][MAXCHAR], int nlines){
    int total_credits = 0;
    int total_grade_points = calculate_grade_points(credits, grades, nlines, &total_credits);
    double semester_gpa = (double)total_grade_points / total_credits;
    return semester_gpa;
}

/* calculate the cumulative GPA */
double calculate_cgpa(char files[][MAXCHAR], int nfiles){
    char course_numbers[MAXN][MAXCHAR];
    char course_names[MAXN][MAXCHAR];
    int credits[MAXN];
    char grades[MAXN][MAXCHAR];
    int nlines = 0;
    int total_credits = 0;
    int total_grade_points = 0;
    for(int i = 0; i < nfiles; i++){
        if(read_csv(files[i], course_numbers, course_names, credits, grades, &nlines)){
            total_grade_points += calculate_grade_points(credits, grades, nlines, &total_credits);
        } else {
            printf("Error reading CSV file\n");
            return 1;
        }
    }
    return (double)total_grade_points / total_credits;
}

/* return the grade for a given course number */
int search_course(char course_search[MAXCHAR], char files[][MAXCHAR], int nfiles){
    char course_numbers[MAXN][MAXCHAR];
    char course_names[MAXN][MAXCHAR];
    int credits[MAXN];
    char grades[MAXN][MAXCHAR];
    int nlines = 0;
    for(int i = 0; i < nfiles; i++){
        if(read_csv(files[i], course_numbers, course_names, credits, grades, &nlines)){
            // print the grade for the course if the course is found
            for (int j = 0; j < nlines; j++){
                if(strcmp(course_search, course_numbers[j]) == 0){
                    struct table_t* table = table_init(stdout, course_names[j], 1);
                    table_row(table, "%s%s%s%s", "Course Number", "Course Name", "Credits", "Grade");
                    table_separator(table);
                    table_row(table, "%s%d%s", course_numbers[j], credits[j], grades[j]);
                    table_commit(table);
                    printf("\n");
                    return 0;
                }
            }
        } else {
            printf("Error reading CSV file\n");
            return 1;
        }
    }
}