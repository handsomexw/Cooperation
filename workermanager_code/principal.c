#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "principal.h"
#include "system.h"
#include "teacher.h"

char G_pri_sec[12] = "123";

static int find_max_id(void)   //自动生成
{
	int sign=0,max=90000000;
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id!=0)
		{
			if(G_teacher_on[i].id>max)
			{
				max=G_teacher_on[i].id;
			}
			sign++;
			if(sign>=G_teacher_on_len)
			{
				break;
			}
		}
	}
	return max;
}

int find_teacher(int id)
{
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
int find_teacher_off(int id)
{
	for(int i=0;i<TEACHER_OFF_MAX;i++)
	{
		if(G_teacher_off[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
static void code(void)
{
	int k = strcmp("123",G_pri_sec);
	char pri_secret[50]={};
	int num = 0;
	if(k==0)
	{
		while(k==0)
		{
			printf("请修改您的初始密码\n");
			printf("在此处输入您的新密码：");
			while(1)
			{
				scanf("%s", pri_secret);
				num = strlen(pri_secret);
				if(num>11 || num<3)
				{
					printf("请重新输入3-11位密码：");	
				}
				else
					break;
			}

			strcpy(G_pri_sec,pri_secret);
			k = strcmp("123",G_pri_sec);
		}
	}	
	
	while(1)
	{
		printf("请输入密码");
		scanf("%s", pri_secret);
		if(0 == strcmp(pri_secret,G_pri_sec))
			break;
		else
		{
			printf("密码错误！\n");
		}
	}
}

void show_teacher_on(void)
{
	system("clear");
	for(int i =0; i<G_teacher_on_len+G_teacher_off_len; i++)
	{
		if(G_teacher_on[i].id)
		{
			printf("姓名: %s\n性别: %c\n工号：%d\n", 
			G_teacher_on[i].name,G_teacher_on[i].sex,G_teacher_on[i].id);
			printf("-------------------\n");
		}
	}
}

void show_teacher_off(void)
{
	system("clear");
	for(int i =0; i<G_teacher_off_len; i++)
	{
		printf("姓名: %s\n性别: %c\n工号： %d\n", 
		G_teacher_off[i].name,G_teacher_off[i].sex,G_teacher_off[i].id);
		printf("-------------------\n");
	}
}

void add_teacher(void)
{
	system("clear");
	int k = 0;
	printf("1.单个添加\n2.批量添加\n请输入你的选择：");
	int ch = 0, next_id = find_max_id();
	scanf("%d", &ch);
	if(ch == 1)
	{
		printf("请依次输入教师的姓名 性别\n");
		while(G_teacher_on[k].id) k++;
		scanf("%s %c",G_teacher_on[k].name, &G_teacher_on[k].sex);
		strcpy(G_teacher_on[k].secret,"123");
		G_teacher_on[k].id = ++next_id;
		G_teacher_on_len += 1;
		printf("添加成功！\n");
		sleep(3);
	}
	if(ch == 2)
	{
		printf("\n请输入需要导入的文件路径，注意：文件格式为姓名 性别\n");
		system("ls");
		char path[30] = {};
		scanf("%s", path);
		FILE* frp = fopen(path,"r");
		if(frp == NULL)
		{
			printf("读取文件失败！");
			return;
		}
		int k1 = 0;
		Teacher tp = {};
		while(fscanf(frp,"%s %c",tp.name,&tp.sex) == 2)
		{
			strcpy(tp.secret,"123");
			tp.id = ++next_id;
			while(G_teacher_on[k1].id) k1++;
			memcpy(&G_teacher_on[k1],&tp,sizeof(Teacher));
			G_teacher_on_len++;
		}
		fclose(frp);
		printf("批量导入成功！\n");
		sleep(3);
	}
}

void del_teacher(void)
{
	system("clear");
	printf("请输入工号：");
	int num = 0;
	scanf("%d", &num);
	int k = find_teacher(num);
	if(k == -1)
	{
		printf("没有此教师！");
		return;
	}
	memcpy(&G_teacher_off[G_teacher_off_len],&G_teacher_on[k],sizeof(G_teacher_on[k]));
	G_teacher_off_len += 1;
	G_teacher_on[k].id = 0;
	G_teacher_on_len -= 1;
	printf("删除成功！\n");
}

void unlock_teacher(void)
{
	system("clear");
	printf("请输入工号：");
	int num = 0;
	scanf("%d", &num);
	int k = find_teacher(num);
	if(k == -1)
	{
		printf("没有此教师！\n");
		return;
	}
	G_teacher_on[k].flag = 0;
	printf("解锁成功！\n");
}

void reset_teacher(void)
{
	system("clear");
	printf("请输入工号：");
	int new_id = 0;
	scanf("%d", &new_id);
	int k = find_teacher(new_id);
	if(k == -1)
	{
		printf("没有此教师！\n");
		return;
	}
	printf("请输入重置密码：");
	char new_sec[50] = {};
	scanf("%s", new_sec);
	strcpy(G_teacher_on[k].secret,new_sec);
	G_teacher_on[k].flag = 0;
	printf("重置成功！\n");
}
	

void reset_me(void)
{
	system("clear");
	printf("请输入重置密码：");
	char new_sec[50] = {};
	scanf("%s", new_sec);
	strcpy(G_pri_sec,new_sec);
	printf("重置成功！\n");
}

void main_principal(void)
{
	system("clear");
	code();
	system("clear");
	printf("---------欢迎进入校长系统---------\n\n");
	while(1)
	{
		printf("请选择您需要的功能\n");
		printf("1.显示所有在职教师   2.显示所有离职教师\n");
		printf("3.添加教师           4.删除教师\n");
		printf("5.重置教师密码       6.解锁教师帐号\n");
		printf("7.重置自己密码       0.退出系统\n");
		
		int choice = 0;
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				show_teacher_on();
				break;

			case 2:
				show_teacher_off();
				break;

			case 3:
				add_teacher();
				break;

			case 4:
				del_teacher();
				break;

			case 5:
				reset_teacher();
				break;

			case 6:
				unlock_teacher();
				break;

			case 7:
				reset_me();
				break;

			case 0:
				return;

			default:
				printf("无效指令！\n");
				break;
		}
	}
}
