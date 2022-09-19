#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"


/*
Create a student array
*/
Student* create_students(int ids[], int remaining_credits[], char* names[], int student_count){
    Student* students = malloc(sizeof(Student)*student_count);
    int i;
    for(i=0; i<student_count; i++){
        students[i].id = ids[i];
        students[i].name = names[i];
        students[i].remaining_credit = remaining_credits[i];
    }
    return students;
}

/*
Create a course array
*/
Course* create_courses(int ids[], int capacities[], int course_count){
    Course* courses = malloc(sizeof(Course)*course_count);
    int i;
    for(i=0; i<course_count; i++){
        courses[i].id = ids[i];
        courses[i].capacity = capacities[i];
    }
    return courses;
}

/*
Appends a bid to a linked list of bids ordered by bids descendingly.
*/
void append(Request** requests, Student* student, int bid){
    if(*requests==NULL){
        *requests = malloc(sizeof(Request));
        (*requests)->student = student;
        (*requests)->bid = bid;
        (*requests)->next = NULL;
    }
    else{
        Request *curr=*requests, *prev=NULL;
        while(curr->next!=NULL && curr->next->bid>=bid){
            prev = curr;
            curr = curr->next;
        }
        if(prev){
            prev->next = malloc(sizeof(Request));
            prev->next->student = student;
            prev->next->bid = bid;
            prev->next->next = curr;
        }
        else{
            if(bid>curr->bid){
                *requests = malloc(sizeof(Request));
                (*requests)->student = student;
                (*requests)->bid = bid;
                (*requests)->next = curr;
            }
            else{
                curr->next = malloc(sizeof(Request));
                curr->next->student = student;
                curr->next->bid = bid;
                curr->next->next = NULL;
            }
        }
    }
}

/*
Add news bid to the course. If student do not have enough bid, do not update course candidate student list.
*/
void new_request(char* student_name, int course_id, int bid, Student* students, Course* courses, int student_count, int course_count){
    int i;
    Request *request;
    for(i=0; strcmp(students[i].name, student_name); i++);
    students = students + i;
    for(i=0; courses[i].id!=course_id; i++);
    courses = courses + i;
    request = courses->requests;
    if(request){
        if(request->student==students){
            students->remaining_credit+=request->bid;
            courses->requests = request->next;
        }
        else{
            for(; request->next!=NULL; request=request->next){
                if(request->next->student==students){
                    students->remaining_credit+=request->next->bid;
                    request->next = request->next->next;
                    break;
                }
            }
        }
    }
    if(bid>students->remaining_credit){
        printf("%s does not have enough credit to enroll Course %d.\n", student_name, course_id);
        return;
    }
    append(&courses->requests, students, bid);
    students->remaining_credit -= bid;
    printf("%s is added to enrollment list of Course %d. Remaining credit: %d\n", student_name, course_id, students->remaining_credit);
}

/*
Prints accepted student list for the course.
*/
void print_course_requests(Course* courses, int course_count, int stop_at_capacity){
    int i;
    for(i=0; i<course_count; i++){
        int j;
        Request* request = courses[i].requests;
        printf("Course: %d\nStudent List:", courses[i].id);
        for(j=0; request!=NULL; request=request->next, j++){
            if(stop_at_capacity && j>=courses[i].capacity){
                break;
            }
            printf(" %s(%d)", request->student->name, request->bid);
        }
        if(j==0){
            printf("No students");
        }
        printf("\n");
    }
}
