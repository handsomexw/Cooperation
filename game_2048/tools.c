#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game2048.h"
#include "tools.h"

int if_same(void)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(infe[i][j]==infe[i+1][j] || infe[i][j]==infe[i][j+1])
			{
				return 1;	
			}
		}
	}
	return 0;
}



void rand_num(void)
{
	if(cnt == 1) 
		return;
	cnt = 1;
	int sum=0;
	//判断是否还有空位
	int q=0,k=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j] == 0)
			{
				sum = 1;
				q = i; k = j;
				i = 4; j = 4;
			}	
		}
	}
		
	int x=0,y=0,l=5;	
	if(sum == 0) 
	{
		if(if_same())
		{
			return;
		}
		else
		{
			flag = 0;
			return;
		}
	}
	int num = 0;
	while(l)
	{
		srand(time(NULL));
		x = rand()%4;
		y = rand()%4;
		num = (rand()%2 + 1)*2;
		if(infe[x][y]==0)
		{
			infe[x][y] = num;
			break;
		}
		l--;
	}
	if(l==0)
	{
		infe[q][k] = num;	
	}
	
}

void show(void)
{
	system("clear");
	for(int i=0; i<4; i++)
	{
		printf("---------------------\n");
		for(int j=0; j<4; j++)
		{
			if(infe[i][j])
				printf("|%4d", infe[i][j]);
			else
				printf("|    ");
		}
		printf("|\n");
	}
	printf("---------------------\n");
}

void if_win(void)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j] == 64)
				flag = 0;
		}
	}
}



