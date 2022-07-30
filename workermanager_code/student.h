#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
	char name[20];
	char sex;
	int id;
	char secret[12];
	double score[3];
	int flag;
}Student;

extern Student* G_student;
extern Student* G_student_off;
extern int Student_on_len;
extern int Student_off_len;

void main_student(int id);

#endif
