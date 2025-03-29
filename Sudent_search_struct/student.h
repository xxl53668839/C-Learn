#include <stdio.h>
#define NAME 50
#define CLASS 3

struct student //student裡面有三個東西
{
    char name[NAME];
    int ID;
    int grade[CLASS];
}; //記得這邊一定要分號;;;;;;;;;;;;;;;;;;

struct student student; //將struct改名為student.