#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "system.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"
//处理导入文件等问题

const static char* student_on_path="student_on_data.txt";
const static char* student_off_path="student_off_data.txt";
const static char* teacher_on_path="teacher_on_data.txt";
const static char* teacher_off_path="teacher_off_data.txt";
const static char* admin_path="admin_data.txt";


void load_stu_on(void)
{
	FILE* frp1=fopen(student_on_path,"r");
	if(frp1==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载在校学生个数
	fscanf(frp1,"%d",&Student_on_len);
	fgetc(frp1);
	for(int i=0;i<Student_on_len;i++)
	{
		fscanf(frp1,"%s %c %d %s %lf %lf %lf %d ",G_student[i].name,&G_student[i].sex,&G_student[i].id,G_student[i].secret,\
		&G_student[i].score[0],&G_student[i].score[1],&G_student[i].score[2],&G_student[i].flag);
	}
	fclose(frp1);
}

void load_stu_off(void)
{
	FILE* frp2=fopen(student_off_path,"r");
	if(frp2==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载离校学生个数
	fscanf(frp2,"%d",&Student_off_len);
	fgetc(frp2);
	for(int i=0;i<Student_off_len;i++)
	{
		fscanf(frp2,"%s %c %d %s %lf %lf %lf %d ",G_student_off[i].name,&G_student_off[i].sex,&G_student_off[i].id,G_student_off[i].secret,\
		&G_student_off[i].score[0],&G_student_off[i].score[1],&G_student_off[i].score[2],&G_student_off[i].flag);
	}
	fclose(frp2);
}
void load_teaher_on(void)
{
	FILE* frp3=fopen(teacher_on_path,"r");
	if(frp3==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载在校教师个数
	fscanf(frp3,"%d",&G_teacher_on_len);
	//fgetc(frp3);
	for(int i=0;i<G_teacher_on_len;i++)
	{
		fscanf(frp3,"%s %c %d %s %d ",G_teacher_on[i].name,&G_teacher_on[i].sex,&G_teacher_on[i].id,G_teacher_on[i].secret,&G_teacher_on[i].flag);
	}
	fclose(frp3);
}
void load_teaher_off(void)
{
	FILE* frp4=fopen(teacher_off_path,"r");
	if(frp4==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载离校教师个数
	fscanf(frp4,"%d ",&G_teacher_off_len);
	fgetc(frp4);
	for(int i=0;i<G_teacher_off_len;i++)
	{
		fscanf(frp4,"%s %c %d %s %d ",G_teacher_off[i].name,&G_teacher_off[i].sex,&G_teacher_off[i].id,G_teacher_off[i].secret,\
		&G_teacher_off[i].flag);
	}
	fclose(frp4);
}
void load_pri(void)
{
	FILE* frp5=fopen(admin_path,"r");
	if(frp5==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载校长密码
	fscanf(frp5,"%s",G_pri_sec);
	fclose(frp5);
}
void load_data(void)
{
	load_stu_on();
	load_stu_off();
	load_teaher_on();
	load_teaher_off();
	load_pri();
}

void write_stu_on()
{
	FILE* fwp1=fopen(student_on_path,"w");
	if(fwp1==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//写入在校学生个数
	fprintf(fwp1,"%d\n",Student_on_len);
	int cnt=Student_on_len;
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id !=0)
		{
			cnt--;
			fprintf(fwp1,"%s %c %d %s %lf %lf %lf %d\n",G_student[i].name,G_student[i].sex,G_student[i].id,G_student[i].secret,\
		G_student[i].score[0],G_student[i].score[1],G_student[i].score[2],G_student[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp1);
}
void write_stu_off()
{
	FILE* fwp2=fopen(student_off_path,"w");
	if(fwp2==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//写入离校学生个数
	fprintf(fwp2,"%d\n",Student_off_len);
	int cnt=Student_off_len;
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id !=0)
		{
			cnt--;
			fprintf(fwp2,"%s %c %d %s %lf %lf %lf %d\n",G_student_off[i].name,G_student_off[i].sex,G_student_off[i].id,G_student_off[i].secret,\
		G_student_off[i].score[0],G_student_off[i].score[1],G_student_off[i].score[2],G_student_off[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp2);
}
void write_teacher_on()
{
	FILE* fwp3=fopen(teacher_on_path,"w");
	if(fwp3==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	
	//写入在校教师个数
	fprintf(fwp3,"%d\n",G_teacher_on_len);
	int cnt=G_teacher_on_len;
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id !=0)
		{
			cnt--;
			fprintf(fwp3,"%s %c %d %s %d\n",G_teacher_on[i].name,G_teacher_on[i].sex,G_teacher_on[i].id,G_student[i].secret,\
		G_teacher_on[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp3);
}
void write_teacher_off()
{
	FILE* fwp4=fopen(teacher_off_path,"w");
	if(fwp4==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//写入离校教师个数
	fprintf(fwp4,"%d\n",G_teacher_off_len);
	int cnt=G_teacher_off_len;
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_teacher_off[i].id !=0)
		{
			cnt--;
			fprintf(fwp4,"%s %c %d %s %d\n",G_teacher_off[i].name,G_teacher_off[i].sex,G_teacher_off[i].id,G_teacher_off[i].secret,\
		G_teacher_off[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp4);
}
void write_pri()
{
	FILE* fwp5=fopen(admin_path,"w");
	if(fwp5==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//写入校长密码
	fprintf(fwp5,"%s",G_pri_sec);
	fclose(fwp5);
}

void write_data(void)
{
	write_stu_on();
	write_stu_off();
	write_teacher_on();
	write_teacher_off();
	write_pri();
	debug("文件写入成功\n");
}

void sys_init(void)
{
	G_student = (Student*)calloc(sizeof(Student),STU_ON_MAX);	//在校学生缓存区
	G_student_off = (Student*)calloc(sizeof(Student),STU_OFF_MAX);//离校学生
	G_teacher_on = (Teacher*)calloc(sizeof(Teacher),TEACHER_ON_MAX);	//在校学生缓存区
	G_teacher_off = (Teacher*)calloc(sizeof(Teacher),TEACHER_OFF_MAX);//离校学生
	
	load_data();
	

#if 0
	Student s1={"wangxin",'M',19061333,"123",97,94,87,0};
	Student s2={"ypj",'M',19064853,"123",65,21,66,0};
	
	Teacher t1={"zhang",'w',90014545,"123",0};
	Teacher t2={"wang",'m',90004545,"123",0};
	
	memcpy(&G_student[0],&s1,sizeof(Student));
	memcpy(&G_student[1],&s1,sizeof(Student));
	memcpy(&G_student_off[0],&s2,sizeof(Student));
	memcpy(&G_teacher_on[0],&t1,sizeof(Student));
	memcpy(&G_teacher_off[0],&t2,sizeof(Student));
	write_data();
#endif

}

void sys_release(void)
{
	free(G_student);
	free(G_student_off);
	free(G_teacher_on);
	free(G_teacher_off);
	
	G_student = NULL;
	G_student_off = NULL;
	G_teacher_on = NULL;
	G_teacher_off = NULL;
}
//文件读取测试

/*
int main()
{
	G_student = malloc(sizeof(Student)*Student_on_len);
	strcpy(G_student[0].name,"ypj");
	G_student[0].sex='m';
	G_student[0].id=19061335;
	strcpy(G_student[0].secret,"piop454879");
	G_student[0].score[0]=85;
	G_student[0].score[1]=83;
	G_student[0].score[2]=82;
	G_student_off = malloc(sizeof(Student)*Student_off_len);
	memcpy(G_student_off,G_student,sizeof(Student));
	write_data();
	open_data();
	for(int i=0;i<Student_on_len;i++)
	{
		printf("%s %c %d %s %lf %lf %lf\n",G_student[i].name,G_student[i].sex,G_student[i].id,G_student[i].secret,\
		G_student[i].score[0],G_student[i].score[1],G_student[i].score[2]);
			
	}
}
*/

