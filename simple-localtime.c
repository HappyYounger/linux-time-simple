#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 * 调用localtime获取Linux系统日期时间
 */
int main(int argc, char* argv[]){

	time_t t;
	struct tm * p_tm;
	time(&t);
	p_tm = localtime(&t);

	printf("%d年 %d月 %d日 %d时 %d分 %d秒\n",
				p_tm->tm_year + 1900,
			       	p_tm->tm_mon + 1, 
				p_tm->tm_mday, 
				p_tm->tm_hour, 
				p_tm->tm_min, 
				p_tm->tm_sec);
	return 0;
}

