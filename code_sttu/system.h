#ifndef SYSTEM_H
#define SYSTEM_H

#define SHOW_MES(temp)	printf("%10s\t%c\t%d\t\t%s\t\t%lf\t%lf\t%lf\n",\
						G_student[temp].name,\
						G_student[temp].sex,\
						G_student[temp].id,\
						G_student[temp].secret,\
						G_student[temp].score[0],G_student[temp].score[1],G_student[temp].score[2])

#define SHOW_MES_OFF(temp)	printf("%10s\t%c\t%d\t\t%s\t\t%lf\t%lf\t%lf\n",\
						G_student_off[temp].name,\
						G_student_off[temp].sex,\
						G_student_off[temp].id,\
						G_student_off[temp].secret,\
						G_student_off[temp].score[0],G_student_off[temp].score[1],G_student_off[temp].score[2])
						
						

#define DEBUG_H

#ifdef DEBUG
	#define debug(...)	printf(__VA_ARGS__)
#else
	#define debug(...)
#endif


#define error(...)	printf("%s:%s %d %m%s %s %s",__FILE__,__FUNCTION__,__LINE__,__VA_ARGS__,__DATE__,__TIME__)


#define STU_ON_MAX			100
#define STU_OFF_MAX			100
#define TEACHER_ON_MAX		100
#define TEACHER_OFF_MAX		100


void load_data(void);
void write_data(void);

void sys_init(void);
void sys_release(void);

#endif
