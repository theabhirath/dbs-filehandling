#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <math.h>
#include <time.h>

#include "table.h"

#define MAXCHAR 1000
#define MAXN 50

/* file operations */
int make_file_array(char files[][MAXCHAR], int* nfiles);
bool read_csv(char *filename, char course_numbers[][MAXCHAR], char course_names[][MAXCHAR], 
                int credits[], char grades[][MAXCHAR], int *nlines);

/* grade operations */
int calculate_grade_points(int credits[], char grades[][MAXCHAR], int nlines, int* total_credits);
double calculate_sgpa(int credits[], char grades[][MAXCHAR], int nlines);
double calculate_cgpa(char files[][MAXCHAR], int nfiles);
int search_course(char course_search[MAXCHAR], char files[][MAXCHAR], int nfiles);

/* display functions */
void display_sgpa(int semester, int credits[], char grades[][MAXCHAR], int nlines);
void display_cgpa(char files[][MAXCHAR], int nfiles);
void display_semester_gradesheet(int semester, char files[][MAXCHAR], 
                                int nfiles, char course_numbers[][MAXCHAR], 
                                char course_names[][MAXCHAR], int credits[], 
                                char grades[][MAXCHAR], int nlines);

/* utility functions */
char *trimwhitespace(char *s);

#endif