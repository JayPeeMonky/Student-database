#ifndef _PROJECT__H_
#define _PROJECT__H_
#include <stdio.h>

#endif //! _PROJECT__H_

typedef struct {
    char *student_number;  
    char *first_name;       
    char *surname;
    int exercises[6];
    int total_points;
} Student;

typedef struct {
    Student *students;  // Pointer to dynamically allocated array of students
    int num_students;          // Current number of students in the database
    int capacity;              // Capacity of the students array
} Database;

void initialize_database(Database *db);
void free_database(Database *db);
void add_student(Database *db, const char *student_number, const char *first_name, const char *surname);
void add_silent(Database *db, const char *student_number, const char *first_name, const char *surname);
void print_database(const Database *db);
void update_points(Database *db, const char *student_number, int exercise, int points);
void update_silent(Database *db, const char *student_number, int exercise, int points);
void save_to_file(const Database *db, const char *filename);
void load_from_file(Database *db, const char *filename);