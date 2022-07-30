#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "teacher.h"
#include "system.h"
#include "student.h"
#include "principal.h"

Teacher *G_teacher_on;
Teacher *G_teacher_off;

int G_teacher_on_len=0;
int G_teacher_off_len=0;

static int find_max_id(void)
{
	int sign=0,max=19059999;
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id!=0)
		{
			if(G_student[i].id>max)
			{
				max=G_student[i].id;
			}
			sign++;
			if(sign>=Student_on_len)
			{
				break;
			}
		}
	}
	return max;
}
int find_student(int id)
{
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
int find_student_off(int id)
{
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id==id)
		{
			return i;
		}
	}
	return -1;
}


/**************************
*
*主代码如下
*佛祖保佑不出bug
*
**************************/
void add_new_student(void)
{
	Student s={};
	printf("1、单个添加\n2、批量添加\n请输入你的选择：");
	int ch=0,maxid=find_max_id();
	for(;;)
	{
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("\n请输入学生的姓名，性别，中间空格隔开：");
			scanf("%s %c",s.name,&s.sex);
			strcpy(s.secret,"123");
			s.id=++maxid;
			memcpy(&G_student[find_student(0)],&s,sizeof(Student));
			Student_on_len++;
			printf("添加成功……\n");
			sleep(3);
			break;
		}else if(ch==2)					//批量导入学生名单
		{
			printf("请选择需要导入的文件路径，文件格式：姓名 性别\n");
			system("ls");
			char path[30]={};
			scanf("%s",path);			//输入批量处理路径
			FILE* frp = fopen(path,"r");
			if(frp==NULL)
			{
				printf("open fail");
				return;
			}
			while(2 == fscanf(frp,"%s %c",s.name,&s.sex))
			{
				strcpy(s.secret,"123");
				s.id=++maxid;
				memcpy(&G_student[find_student(0)],&s,sizeof(Student));
				Student_on_len++;
			}
			fclose(frp);
			printf("批量导入成功……\n");
			sleep(3);
			break;
		}
	}
	
	
}

void del_student(void)
{
	int id,id1,temp;
	printf("\n请输入需要删除的学生学号：");
	scanf("%d",&id);
	temp = find_student(id);
	if(temp==-1)
	{
		printf("学生不存在\n");
		sleep(3);
		return;
	}
	printf("\n请再次输入学号确认：");
	scanf("%d",&id1);
	if(id!=id1)
	{
		printf("删除失败\n");
		sleep(1);
		return;
	}
	memcpy(&G_student_off[find_student_off(0)],&G_student[temp],sizeof(Student));//将删除后的数据存入
	G_student[temp].id=0;
	printf("学生删除成功\n");
	sleep(3);
}
void search_student(void)
{
	char name[20]={};
	int ch=0,cnt=0;;
	for(;;)
	{
		printf("1、姓名查找\n2、学号查找\n请输入你的选择(离校学生不在查找范围内)：");
		//debug("s_on=%d\ns_off=%d\n",Student_on_len,Student_off_len);
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("\n请输入学生的姓名：");
			scanf("%s",name);
			for(int i=0;i<STU_ON_MAX;i++)
			{
				if(G_student[i].id !=0)
				{
					cnt++;
					if(strstr(G_student[i].name,name) != NULL)
					{
						SHOW_MES(i);
					}
					if(cnt>=Student_on_len)
					{
						printf("查找结束\n");
						sleep(3);
						return;
					}
				}
			}
		}else if(ch==2)
		{
			printf("\n请输入学生的学号：");
			int id=0,temp;
			scanf("%d",&id);
			if((temp=find_student(id))!=-1)
			{
				SHOW_MES(temp);
				printf("查找结束\n");
				sleep(3);
				return;
			}else
			{
				printf("没有该学生\n");
				sleep(3);
				return;
			}
		}
	}
	
}
void change_student(void)//修改学生信息
{
	int id;
	printf("输入需要修改学生的学号：");
	scanf("%d",&id);
	printf("1,修改学生基础信息\n2,修改学生成绩\n请输入选择");
	int choise=0;
	scanf("%d",&choise);
	int ox=find_student(id);
	if(ox==-1)
	{
		printf("没有这个人\n");
	}else
	{
		if(choise==1)
		{
			printf("请输入修改后的学生姓名，性别，密码：");
			scanf("%s %c %s",G_student[ox].name,&G_student[ox].sex,G_student[ox].secret);
			printf("修改成功\n");
		}else if(choise==2)
		{
			printf("请输入修改后的学生成绩，语文，数学，外语：");
			scanf("%lf %lf %lf",&G_student[ox].score[0],&G_student[ox].score[1],&G_student[ox].score[2]);
			printf("修改成功\n");
			
		}else
		{
			printf("选择无效\n");
		}
	}
	sleep(3);
}

void add_score_student(void)
{
	printf("\n1,单个录入\n2,批量录入\n请输入选择");
	int choise=0;
	scanf("%d",&choise);
	if(choise==1)
	{
		int id;
		printf("输入需要修改学生的学号：");
		scanf("%d",&id);
		
		int ox=find_student(id);
		if(ox==-1)
		{
			printf("没有这个人\n");
		}else
		{
			printf("请输入修改后的学生成绩，语文，数学，外语：");
			scanf("%lf %lf %lf",&G_student[ox].score[0],&G_student[ox].score[1],&G_student[ox].score[2]);
			printf("修改成功\n");
		}
	}else if(choise == 2)
	{
		printf("请选择需要导入的文件路径，文件格式：学号 语文 数学 英语:\n");
		system("ls");
		char path[30]={};
		Student s={};
		scanf("%s",path);			//输入批量处理路径
		FILE* frp = fopen(path,"r");
		if(frp==NULL)
		{
			printf("open fail\n");
			return;
		}
		int des=0;
		while(4 == fscanf(frp,"%d %lf %lf %lf",&s.id,&s.score[0],&s.score[1],&s.score[2]))
		{
			//debug("%d\n",s.id);
			des=find_student(s.id);
			if(des != -1)
			{
				G_student[des].score[0] = s.score[0];
				G_student[des].score[1] = s.score[1];
				G_student[des].score[2] = s.score[2];
			}
			fgetc(frp);
		}
		fclose(frp);
		printf("批量修改成绩成功……\n");
	}else
	{
		printf("无效输入\n");
	}
	sleep(3);
}

void reset_sec_student(void)
{
	int id,temp=0;
	printf("输入需要重置密码学生的学号：");
	scanf("%d",&id);
	temp = find_student(id);
	if(temp==-1)
	{
		printf("没有这个人\n");
	}else
	{
		strcpy(G_student[temp].secret,"123");
		G_student[temp].flag=0;
		printf("重置成功\n");
	}
	sleep(3);
}
void show_on_student(void)
{
	int cnt=0;
	printf("在校学生信息：\n");

	printf("%10s\t性别\t学号\t\t\t密码\t\t语文\t\t数学\t\t外语\n","姓名");
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id!=0)
		{
			cnt++;
			SHOW_MES(i);
		}
		if(cnt>=Student_on_len)
		{
			break;
		}
	}
	getchar();
	getchar();
	//sleep(5);
}
void show_off_student(void)
{
	int cnt=0;
	printf("离校学生信息：\n");
	printf("%10s\t性别\t学号\t\t\t密码\t\t语文\t\t数学\t\t外语\n","姓名");
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id!=0)
		{
			cnt++;
			SHOW_MES_OFF(i);
		}
		if(cnt>=Student_off_len)
		{
			break;
		}
	}
	getchar();
	getchar();
}

int signin(int id)
{
	int count=3;
	char key[30]={};
	if(find_teacher(id)==-1)
	{
		printf("帐号不存在\n");
		sleep(3);
		return 0;
	}
	if(G_teacher_on[find_teacher(id)].flag == 1)
	{
		printf("密码锁定，联系校长\n");
		sleep(3);
		return 0;
	}

	if(strcmp(G_teacher_on[find_teacher(id)].secret,"123")==0)
	{
		char s[20];
		for(;;)
		{
			printf("第一次登录，请输入修改后的密码：");
			scanf("%s",s);
			s[19]='\0';
			if(strlen(s)>11 || strlen(s)<3 )
			{
				printf("密码长度非法……\n");
				continue;
			}
			strcpy(G_teacher_on[find_teacher(id)].secret,s);
			break;
		}	
		
	}
	for(;;)
	{
		printf("请输入密码(%d)：",count);
		scanf("%s",key);
		key[29]=0;
		if(strlen(key)>11 || strlen(key)<3)
		{
			printf("密码长度非法……\n");
		}else
		{
			if(strcmp(G_teacher_on[find_teacher(id)].secret,key)==0)
			{
				printf("登录成功\n");
				sleep(3);
				return 1;
			}
		}
		count--;
		if(count==0)
		{
			printf("密码锁定，联系校长……\n");
			sleep(3);
			G_teacher_on[find_teacher(id)].flag = 1;
			return 0;
		}
	}
	return 0;
}
void (*func[])(void)={
	add_new_student,
	del_student,
	search_student,
	change_student,
	add_score_student,
	reset_sec_student,
	show_on_student,
	show_off_student,
};
void main_teacher(int id)
{
	if(signin(id)==0)
	{
		return;
	}
	
	int  choise=0;
	for(;;)
	{
		system("clear");
		printf("---1、添加学生\n");
		printf("---2、删除学生\n");
		printf("---3、查找学生\n");
		printf("---4、修改学生信息\n");
		printf("---5、录入学生成绩\n");
		printf("---6、重置学生密码\n");
		printf("---7、显示所有在校学生信息\n");
		printf("---8、显示所有退出学生信息\n");
		printf("---9、退出登录\n");
		printf("请输入选项：");
		scanf("%d",&choise);
		if(choise == 9)
		{
			printf("退出登录\n");
			sleep(3);
			return;
		}
		if(choise>0 && choise<9)
		{
			func[choise-1]();
		}
		
	}
	
}
			 
