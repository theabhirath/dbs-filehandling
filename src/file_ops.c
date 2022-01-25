#include "helper.h"

/* make array of all filenames in the grades directory */
int make_file_array(char files[][MAXCHAR], int* nfiles){
    DIR* dir;
    struct dirent* ent;
    if((dir = opendir("../grades")) == NULL){
        printf("Error: could not open directory\n");
        return 1;
    }
    int i = 0;
    while((ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
            strcpy(files[i], "../grades/");
            strcat(files[i], ent->d_name);
            i++;
        }
    }
    *nfiles = i;
    closedir(dir);
    return 0;
}

/* read a CSV file with course information */
bool read_csv(char *filename, char course_numbers[][MAXCHAR], char course_names[][MAXCHAR], 
                int credits[], char grades[][MAXCHAR], int *nlines) {
    FILE *fp;
    char line[MAXCHAR];
    int i = 0;
    char *token;
    char *saveptr;
    char *course_number;
    char *course_name;
    char *credits_str;
    char *grade;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return false;
    }

    while (fgets(line, MAXCHAR, fp) != NULL) {
        /* trim whitespace from the start and end of the line */
        trimwhitespace(line);

        /* skip blank lines */
        if (strlen(line) == 0) {
            continue;
        }

        /* split the line into tokens */
        token = strtok_r(line, ",", &saveptr);
        course_number = trimwhitespace(token);
        token = strtok_r(NULL, ",", &saveptr);
        course_name = trimwhitespace(token);
        token = strtok_r(NULL, ",", &saveptr);
        credits_str = trimwhitespace(token);
        token = strtok_r(NULL, ",", &saveptr);
        grade = trimwhitespace(token);

        /* store the tokens in the arrays */
        strcpy(course_numbers[i], course_number);
        strcpy(course_names[i], course_name);
        credits[i] = atoi(credits_str);
        strcpy(grades[i], grade);

        /* increment the line counter */
        i++;
    }

    /* set the number of lines read */
    *nlines = i;

    fclose(fp);
    return true;
}
