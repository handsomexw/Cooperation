
#include "game2048.h"
#include "tools.h"

void up(void)
{
	//检测并合并
	int m=0,n=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j])
			{
				m = i;
				n = i-1;
				for(;n>=0;n--)
				{
					if(infe[m][j] == infe[n][j])
					{
						infe[n][j] += infe[m][j];
						infe[m][j] = 0;	
						score++;
						cnt = 0;
					}
					if(infe[n][j] !=0 && infe[m][j] != infe[n][j])
						break;
				}
			
			}
		
		}
	}
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j])
			{
				m = i;
				n = i-1;
				for(;n>=0;n--)
				{
					if( 0 == infe[n][j])
					{
						infe[n][j] = infe[m][j];
						infe[m][j] = 0;	
						m--;
						cnt = 0;
					}
				}
			
			}
		
		}
	}
}

void right(void)
{
	int m=0,n=0;
	for(int i=3; i>=0; i--)
	{
		for(int j=3; j>=0; j--)
		{
			if(infe[i][j])
			{
				m = j;
				n = j+1;
				for(;n<4;n++)
				{
					if( infe[i][m] == infe[i][n])
					{
						infe[i][n] += infe[i][m];
						infe[i][m] = 0;	
						score++;
						cnt = 0;
					}
					if(infe[i][n] != 0 && infe[i][m] != infe[i][n])
						break;
				}
			}
		}
	}
	
	for(int i=3; i>=0; i--)
	{
		for(int j=3; j>=0; j--)
		{
			if(infe[i][j])
			{
				m = j;
				n = j+1;
				for(;n<4;n++)
				{
					if( 0 == infe[i][n])
					{
						infe[i][n] = infe[i][m];
						infe[i][m] = 0;
						m++;
						cnt = 0;
					}
				}
			}
		}
	}
}

void down(void)
{
	int m=0,n=0;
	for(int i=3; i>=0; i--)
	{
		for(int j=3; j>=0; j--)
		{
			if(infe[i][j])
			{
				m = i;
				n = i+1;
				for(;n<4;n++)
				{
					if( infe[m][j] == infe[n][j])
					{
						infe[n][j] += infe[m][j];
						infe[m][j] = 0;	
						score++;
						cnt = 0;
					}
					if(infe[n][j] != 0 && infe[m][j] != infe[n][j])
						break;
				}
			}
		}
	}
	
	for(int i=3; i>=0; i--)
	{
		for(int j=3; j>=0; j--)
		{
			if(infe[i][j])
			{
				m = i;
				n = i+1;
				for(;n<4;n++)
				{
					if( 0 == infe[n][j])
					{
						infe[n][j] = infe[m][j];
						infe[m][j] = 0;
						m++;
						cnt = 0;
					}
				}
			}
		}
	}
}

void left(void)
{
	//检测并合并
	int m=0,n=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j])
			{
				m = j;
				n = j-1;
				for(;n>=0;n--)
				{
					if(infe[i][m] == infe[i][n])
					{
						infe[i][n] += infe[i][m];
						infe[i][m] = 0;	
						score++;
						cnt = 0;
					}
					if(infe[i][n] !=0 && infe[i][m] != infe[i][n])
						break;
				}
			
			}
		
		}
	}
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(infe[i][j])
			{
				m = j;
				n = j-1;
				for(;n>=0;n--)
				{
					if(0 == infe[i][n])
					{
						infe[i][n] = infe[i][m];
						infe[i][m] = 0;
						m--;
						cnt = 0;	
					}
				}
			
			}
		}
	}
}
