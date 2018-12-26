#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 此例程为调用stime设置Linux系统日期时间
 * 注意：stime需要root权限
 */

char tip[] = "需要输入 年 月 日 时 分 秒 6个参数\n";

int main(int argc, char* argv[]){

	if(argc == 7){
		time_t t;
		struct tm * p_tm;

		time(&t);
		p_tm = localtime(&t);

		int year = strtol(argv[1], NULL, 10);
		int mon = strtol(argv[2], NULL, 10);
		int day = strtol(argv[3], NULL, 10);
		int hour = strtol(argv[4], NULL, 10);
		int min = strtol(argv[5], NULL, 10);
		int sec = strtol(argv[6], NULL, 10);


		printf("%d %d %d %d %d %d", year, mon, day, hour, min, sec);
		p_tm->tm_year = year - 1900;
		p_tm->tm_mon = mon - 1;
		p_tm->tm_mday = day - 1;
		p_tm->tm_hour = hour;
		p_tm->tm_min = min;
		p_tm->tm_sec = sec;

		t = mktime(p_tm);

		stime(&t);

	}else{

		printf("%s\n",tip);
	}

	return 0;
}
