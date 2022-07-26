#include <stdio.h>
#include <assert.h>
size_t  m_strlen(const char* s)
{
	assert(s != NULL);
	const char* temp = s;
	while(*temp++);
	return temp-s-1;
/*	int len = 0;
	while(s[len]) len++;
	return len;
*/
}

char* m_strcpy(char* s1, const char* s2)
{
//	int i=0;
//	for( ;s2[i]!=0; i++) s1[i] = s2[i];
//	s1[i] = 0;
	assert(s1 != NULL && s2 != NULL);
	char* start = s1;
	while((*s1++=*s2++)!=0);
	return start;
}
char* m_strcat(char* s1, const char* s2)
{
/*	int i = 0,j = 0;
	while(s1[i]!=0) i++;
	while(s2[j++]!=0) s1[i++] = s2[j-1];s1[i]=0;
	return s1;
	*/
	assert(s1 != NULL && s2 != NULL);
	char* temp = s1;
	while(*temp) temp++;
	while(*temp++=*s2++);
	return s1;
}
int m_strcmp(const char* s1,const char* s2)
{
/*	int i = 0;
	while(s1[i]!=0 && s2[i]!= 0 && s1[i]-s2[i]==0) i++;
	if(s1[i]-s2[i]==0) return 0;else if(s1[i]-s2[i]>0) return 1; else return -1;
	*/
	assert(s1 != NULL && s2 != NULL);
	while(*s1 == *s2 && *s1) s1++,s2++;
	return *s1-*s2>0?1:*s1-*s2<0?-1:0;
}
int main(int argc,const char* argv[])
{
	char str[50] = "hahaxixicaca";
	char str1[50] = "hehe";
//	printf("%d\n", m_strlen(str));
//	printf("%s\n", m_strcpy(str1,str));
//	printf("%s\n", m_strcat(str,str1));
	printf("%d\n", m_strcmp(str,str1));
	return 0;
}
