#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50


int main(void) 
{
    Database db; // Declare the database variable
    initialize_database(&db); // Initialize the database

    char input[1000];
    char command;
    char *student_number = malloc(MAX_NAME_LENGTH * sizeof(char));;
    char *first_name = malloc(MAX_NAME_LENGTH * sizeof(char));
    char *surname = malloc(MAX_NAME_LENGTH * sizeof(char));
    int exercise, points;
    char *filename = malloc(100 * sizeof(char)); // Dynamic allocation

    if (!filename) 
    { 
        // Check if memory allocation failed
        printf("Error: Memory allocation failed.\n");
        return 1; // Exit with error
    }

    while (1) 
    {
        // Read the entire line of input
        fgets(input, sizeof(input), stdin);
        
        // Parse the command from the input
        sscanf(input, " %c", &command);

        switch (command) 
        {
            case 'A':
                if (sscanf(input, "%*c %49s %49s %49s", student_number, surname, first_name) != 3) 
                {
                    // Input format is incorrect
                    printf("A should be followed by exactly 3 arguments.\n");
                } 
                
                else 
                {
                    // Inputs are valid, proceed with adding student
                    add_student(&db, student_number, first_name, surname);
                }

                break;

            case 'U':
                if (sscanf(input, "%*c %49s %d %d", student_number, &exercise, &points) != 3) 
                {
                    // Input format is incorrect
                    printf("Exercise round and points must be numeric.\n");
                } 
                
                else 
                {
                    // Inputs are valid, proceed with updating points
                    update_points(&db, student_number, exercise, points);
                }

                break;

            case 'L':
                print_database(&db);
                break;

            case 'W':
                if (sscanf(input, "%*c %99s", filename) != 1) 
                {
                    // Input format is incorrect
                    printf("Error: Invalid input format for writing\n");
                } 
                
                else 
                {
                    // Inputs are valid, proceed with writing
                    save_to_file(&db, filename);
                }

                break;

            case 'O':
                if (sscanf(input, "%*c %99s", filename) != 1) 
                {
                    // Input format is incorrect
                    printf("Error: Invalid input format for loading\n");
                } 
                
                else
                {
                    // Inputs are valid, proceed with loading
                    load_from_file(&db, filename);
                }

                break;

            case 'Q':
                free_database(&db);
                free(filename); // Free dynamically allocated memory
                free(student_number);
                free(first_name);
                free(surname);
                return 0; // Exit the program

            default:
                printf("Invalid command ");
        }
    }

    // Free dynamically allocated memory before exiting (this should not be reached)
    free(filename);

    return 0;
}

// Initialize an empty database
void initialize_database(Database *db) 
{
    db->students = NULL;
    db->num_students = 0;
    db->capacity = 0;
}

// Free memory allocated for database
void free_database(Database *db) 
{
    for (int i = 0; i < db->num_students; i++) 
    {
        free(db->students[i].student_number);
        free(db->students[i].first_name);
        free(db->students[i].surname);
    }

    free(db->students);
    db->capacity = 0;
    db->num_students = 0;

    printf("SUCCESS\n");
}

// Add a student to the database
void add_student(Database *db, const char *student_number, const char *first_name, const char *surname)
{
    // Check if student number is valid
    if (strlen(student_number) > 6) 
    {
        printf("Student number %s cannot be more than 6 digits.\n", student_number);
        return;
    }

    // Check if there's already a student with the same number
    for (int i = 0; i < db->num_students; i++) 
    {
        if (strcmp(db->students[i].student_number, student_number) == 0) 
        {
            printf("Student %s is already in the database.\n", student_number);
            return;
        }
    }

    // Resize students array if necessary
    if (db->num_students >= db->capacity) 
    {
        db->capacity += 1;
        db->students = realloc(db->students, db->capacity * sizeof(Student));

        if (!db->students) 
        {
            printf("Error: Memory allocation failed.\n");
            return;
        }
    }

    //Allocate memory for student number, surname, and name and copy it
    db->students[db->num_students].student_number = malloc(strlen(student_number) + 1);
    db->students[db->num_students].surname = malloc(strlen(surname) + 1);
    db->students[db->num_students].first_name = malloc(strlen(first_name) + 1);

    if (!db->students[db->num_students].student_number || !db->students[db->num_students].first_name || !db->students[db->num_students].surname) 
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    strcpy(db->students[db->num_students].student_number, student_number);
    strcpy(db->students[db->num_students].first_name, first_name);
    strcpy(db->students[db->num_students].surname, surname);

    for (int i = 0; i < 6; i++) 
    {
        db->students[db->num_students].exercises[i] = 0;
    }   

    db->students[db->num_students].total_points = 0;

    db->num_students++;

    printf("SUCCESS\n");
}

void add_silent(Database *db, const char *student_number, const char *first_name, const char *surname) // Same as add_student but omits the "SUCCESS\n"
{
    // Check if student number is valid
    if (strlen(student_number) > 6) 
    {
        printf("Student number %s cannot be more than 6 digits.\n", student_number);
        return;
    }

    // Check if there's already a student with the same number
    for (int i = 0; i < db->num_students; i++) 
    {
        if (strcmp(db->students[i].student_number, student_number) == 0) 
        {
            printf("Student %s is already in the database.\n", student_number);
            return;
        }
    }

    // Resize students array if necessary
    if (db->num_students >= db->capacity) 
    {
        db->capacity += 1;
        db->students = realloc(db->students, db->capacity * sizeof(Student));

        if (!db->students) 
        {
            printf("Error: Memory allocation failed.\n");
            return;
        }
    }

    //Allocate memory for student number, surname, and name and copy it
    db->students[db->num_students].student_number = malloc(strlen(student_number) + 1);
    db->students[db->num_students].surname = malloc(strlen(surname) + 1);
    db->students[db->num_students].first_name = malloc(strlen(first_name) + 1);

    if (!db->students[db->num_students].student_number || !db->students[db->num_students].first_name || !db->students[db->num_students].surname) 
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    strcpy(db->students[db->num_students].student_number, student_number);
    strcpy(db->students[db->num_students].first_name, first_name);
    strcpy(db->students[db->num_students].surname, surname);

    for (int i = 0; i < 6; i++) 
    {
        db->students[db->num_students].exercises[i] = 0;
    }   

    db->students[db->num_students].total_points = 0;

    db->num_students++;

}

// Print the student database
void print_database(const Database *db) 
{
    // Sort students based on total points
    for (int i = 0; i < db->num_students - 1; i++) 
    {
        for (int j = 0; j < db->num_students - i - 1; j++) 
        {
            if (db->students[j].total_points < db->students[j + 1].total_points) 
            {
                Student temp = db->students[j];
                db->students[j] = db->students[j + 1];
                db->students[j + 1] = temp;
            }
        }
    }

    // Print students
    for (int i = 0; i < db->num_students; i++) 
    {
        printf("%s %s %s", db->students[i].student_number, 
                           db->students[i].surname, 
                           db->students[i].first_name);

        for (int j = 0; j < 6; j++) 
        {
            printf(" %d", db->students[i].exercises[j]);
        }

        printf(" %d\n", db->students[i].total_points);
    }

    printf("SUCCESS\n");
}

// Update points for a student
void update_points(Database *db, const char *student_number, int exercise, int points)
{

    for (int i = 0; i < db->num_students; i++) 
    {
        if (strcmp(db->students[i].student_number, student_number) == 0) 
        {
            db->students[i].total_points -= db->students[i].exercises[exercise - 1];
            db->students[i].exercises[exercise - 1] = points;
            db->students[i].total_points += points;
            printf("SUCCESS\n");
            return;
        }
    }

    printf("Student %s is not in the database.\n", student_number);
}

void update_silent(Database *db, const char *student_number, int exercise, int points) // Same as update_points but omits the "SUCCESS\n"
{

    for (int i = 0; i < db->num_students; i++) 
    {
        if (strcmp(db->students[i].student_number, student_number) == 0) 
        {
            db->students[i].total_points -= db->students[i].exercises[exercise - 1];
            db->students[i].exercises[exercise - 1] = points;
            db->students[i].total_points += points;
            return;
        }
    }

    printf("Student %s is not in the database.\n", student_number);
}

// Save the database to a file
void save_to_file(const Database *db, const char *filename) 
{
    FILE *file = fopen(filename, "w");

    if (!file) 
    {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < db->num_students; i++) 
    {
        fprintf(file, "%s %s %s", db->students[i].student_number, 
                                 db->students[i].surname, 
                                 db->students[i].first_name);

        for (int j = 0; j < 6; j++) 
        {
            fprintf(file, " %d", db->students[i].exercises[j]);
        }

        fprintf(file, " %d\n", db->students[i].total_points);
    }

    fclose(file);
    printf("SUCCESS\n");
}

// Load the database from a file
void load_from_file(Database *db, const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (!file) 
    {
        printf("Cannot open file %s for reading.\n", filename);
        return;
    }

    // Clear existing database
    for (int i = 0; i < db->num_students; i++) 
    {
        free(db->students[i].student_number);
        free(db->students[i].first_name);
        free(db->students[i].surname);
    }

    free(db->students);
    db->capacity = 0;
    db->num_students = 0;

    initialize_database(db);

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        char student_number[MAX_NAME_LENGTH];
        char first_name[MAX_NAME_LENGTH];
        char surname[MAX_NAME_LENGTH];
        int exercises[6];
        int total_points;
        
        sscanf(buffer, "%s %s %s %d %d %d %d %d %d %d", 
                   student_number, surname, first_name, 
                   &exercises[0], &exercises[1], &exercises[2], 
                   &exercises[3], &exercises[4], &exercises[5], 
                   &total_points);

        // Add student to database
        add_silent(db, student_number, first_name, surname);

        // Update points for the student
        update_silent(db, student_number, 1, exercises[0]);
        update_silent(db, student_number, 2, exercises[1]);
        update_silent(db, student_number, 3, exercises[2]);
        update_silent(db, student_number, 4, exercises[3]);
        update_silent(db, student_number, 5, exercises[4]);
        update_silent(db, student_number, 6, exercises[5]);
    }

    fclose(file);
    printf("SUCCESS\n");
}
