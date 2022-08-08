#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "student.h"
#include "teacher.h"
#include "system.h"

int Student_on_len = 0;
int Student_off_len = 0;

Student* G_student = NULL;
Student* G_student_off = NULL;
static int code(int);
static double s_score[9];

int sort(double score, int k)
{
	int s = 1;
	for(int i = 0; i<Student_on_len+Student_off_len; i++)
	{
		if(G_student[i].score[k]>score && G_student[i].id)
		{
			s++;
		}
	}
	return s;
}
void score_s(void)
{
	double sum[3]={},max[3]= {},min[3]={200,200,200};
	int k = 0;
	for(int i=0;i<Student_on_len+Student_off_len;i++)
	{
		for(int j=0; j<3; j++)
		{
			if(G_student[i].score[j]>max[j] && G_student[i].id)
			{
				max[j] = G_student[i].score[j];
			}
			if(G_student[i].score[j]<min[j] && G_student[i].id)
			{
				min[j] = G_student[i].score[j];
			}
			sum[j] += G_student[i].score[j];
		}
		if(G_student[i].id) k++;
	}
	for(int i=0;i<3;i++)
	{
		sum[i] /= k;
	}
	s_score[0]=sum[0],s_score[1]=sum[1],s_score[2]=sum[2];
	s_score[3]=max[0],s_score[4]=max[1],s_score[5]=max[2];
	s_score[6]=min[0],s_score[7]=min[1],s_score[8]=min[2];
	FILE* fwp = fopen("sort_score","w");
	if(fwp == NULL)
	{
		printf("系统繁忙，请稍后..\n");
		return;
	}
	fprintf(fwp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",
	s_score[0],s_score[1],s_score[2],s_score[3],s_score[4],s_score[5],s_score[6],s_score[7],s_score[8]);
	fclose(fwp);
	fwp = NULL;
}
void show_score(int std_id)
{	
	system("clear");
	score_s();
	double stu_score[9] = {};
	FILE* frp = fopen("sort_score","r");
	if(frp == NULL)
	{
		printf("系统繁忙，请稍后..\n");
		return;
	}
	fscanf(frp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&stu_score[0],&stu_score[1],&stu_score[2],
	&stu_score[3],&stu_score[4],&stu_score[5],&stu_score[6],&stu_score[7],&stu_score[8]);

	printf("\t姓名：%s\t学号：%d\n",G_student[std_id].name,G_student[std_id].id);

	printf("语文：%.1lf 排名：%d 平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[0],sort(G_student[std_id].score[0],0),stu_score[0],
	stu_score[3],stu_score[6]);

	printf("数学：%.1lf 排名：%d 平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[1],sort(G_student[std_id].score[1],1),stu_score[1],
	stu_score[4],stu_score[7]);

	printf("英语：%.1lf 排名：%d 平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[2],sort(G_student[std_id].score[2],2),stu_score[2],
	stu_score[5],stu_score[8]);
	fclose(frp);
	frp = NULL;
}

void show_mes(int std_id)
{
	system("clear");
	printf("姓名: %s\n性别: %c\n学号：%d\n", 
	G_student[std_id].name,G_student[std_id].sex,G_student[std_id].id);	
}

void change_sec(int std_id)
{
	system("clear");
	printf("请输入新密码：");
	scanf("%s", G_student[std_id].secret);
	printf("修改成功！\n");
	
}


void main_student(int stu_id)
{
	system("clear");
	int std_id = find_student(stu_id);
	if(code(std_id))
	{
		return;
	}
	int choice = 0;
	while(1)
	{
		printf("1.查看个人信息 2.查看个人成绩 3.修改密码 0.退出系统\n");
		printf("请输入您要选择的功能：");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: 
				show_mes(std_id);	
				break;

			case 2:
				show_score(std_id);
				break;

			case 3:
				change_sec(std_id);
				break;
	
			case 0:
				return;

			default:
				printf("无效指令，请重新输入：\n");
		}
	}
}
static int code(int std_id)
{
	if(std_id == -1)
	{
		printf("没有此学生！\n");
		sleep(3);
		return 1;
	}
	int k = strcmp("123",G_student[std_id].secret);
	int frequency = 3;
	char sc_secret[12]={};
	char scc_secret[50]={};
	int num = 0;
	if(k==0)
	{
		while(k==0)
		{
			printf("请修改您的初始密码\n");
			printf("在此处输入您的新密码：");
			while(1)
			{
				scanf("%s", scc_secret);
				num = strlen(scc_secret);
				if(num>11 || num<3)
				{
					printf("请重新输入3-11位密码：\n");	
				}
				else
					break;
			}
			strcpy(G_student[std_id].secret,scc_secret);
			k = strcmp("123",G_student[std_id].secret);
		}
	}
	if(G_student[std_id].flag == 1 )
	{
		printf("您的帐号已锁定，请联系老师解锁！\n");
		sleep(3);
		return 1;
	}

	while(frequency)
	{
		printf("请输入密码，您有%d次机会！\n",frequency);
		scanf("%s", sc_secret);
		if(0 == strcmp(sc_secret,G_student[std_id].secret))
			break;
		frequency--;
	}

	if(frequency == 0)
	{
		printf("您的帐号已锁定，请联系老师解锁！\n");
		G_student[std_id].flag = 1;
		sleep(3);
		return 1;
	}
	return 0;
}

