#include <stdio.h>
#include <stdlib.h>
#include <getch.h>

#include "tools.h"
#include "direction.h"

int (*infe)[4] = NULL;
int score = 0;
int flag = 1;
int cnt = 0;


#include "game2048.h"

void init_game(void)
{
	//申请堆内存
	infe = calloc(4*4,4);
	//初始化数据
	//读取文件，加载数据
}
void start_game(void)
{
	for(;;)
	{
		//随机位置生成2/4
		rand_num();
		//显示界面
		show();
		//获取方向键并处理
		if(flag)
		{
			switch(getch())
			{
				case 183: up(); break;
				case 184: down(); break;
				case 186: left(); break;
				case 185: right(); break;
			}
		}
		
		if_win();
		if(!flag) break;
	}
}

void end_game()
{
	show();
	printf("您的得分是：%d，请再接再厉！\n",score);
	free(infe);
}

