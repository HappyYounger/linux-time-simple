#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

const int MAX_YEAR = 9999;
const int VAL_END = -2;//end
const int VAL_CURRENT = -1;//do not change

char PARAM_HELP [] = "--help";
char PARAM_SET [] = "-d";
char HELP_TEXT [] = "-d 年 月 日 时 分 秒。如果输入参数为x，表示不变，如 mock-date x x x 14 0 0,将时间设为14:00:00\n--help 显示帮助文档";
char TIP_INVALID_PARAM [] = "输入的时间无效：年（1-9999），月（1-12），日（1-28/29/30/31），时（0-23），分（0-59），秒（0-59）";

void show_tip();
int is_valid_tm_member(int m, int min, int max);
int set_date(char* args[]);
int is_leap(int year);
int * validate_tm_member(char* args[]);
int set_date_time(int* args);

int main(int argc, char* argv[]){

	time_t t;
	struct tm * p_tm;
	time(&t);
	p_tm = localtime(&t);

	if(argc == 1){
		printf("%d年 %d月 %d日 %d时 %d分 %d秒\n",
				p_tm->tm_year + 1900,
			       	p_tm->tm_mon + 1, 
				p_tm->tm_mday, 
				p_tm->tm_hour, 
				p_tm->tm_min, 
				p_tm->tm_sec);
	}else if(argc == 2){

		if(strcmp(PARAM_HELP, argv[1]) == 0){

			printf("%s\n", HELP_TEXT);
		}else{
			show_tip();
		}	

	}else if(argc == 8){

		if(strcmp(PARAM_SET, argv[1]) == 0){
			set_date(argv + 2);
		}else{
			show_tip();
		}
		
	}else{
		show_tip();
	}

	return 0;
}


void show_tip(){

	printf("请使用--help查看帮助\n");
}

int is_valid_tm_member(int m, int min, int max){

	return m >= min && m <= max;;
}

int set_date(char* args[]){

	int index = 0;
	int * p_tm_member = validate_tm_member(args);
	int * p = p_tm_member;
	if(p_tm_member == NULL){

		return -1;
	}

	set_date_time(p_tm_member);
	free(p_tm_member);
	return 0;
}


int is_leap(int year){

	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int * validate_tm_member(char* args[]){

	int * p_tm_member = malloc(sizeof(int) * 7);
	int * p = p_tm_member;
	int index = 0;
	int max;
	int min;
	while( args[index] != NULL){

		if(strcmp("x", args[index]) == 0){

			*p  = VAL_CURRENT;
			index ++;
			p ++;

			continue;
		}

		long member = strtol(args[index], NULL, 10);
		if(errno == EINVAL || errno == ERANGE ){

			printf("数据格式异常或超出表示范围");
			return NULL;
		}

		switch(index){

			case 0:
				min = 1;
				max = MAX_YEAR;
				break;
			case 1:
				min = 1;
				max = 12;
				break;
			case 2:
				min = 1;
				int year = p_tm_member[0];
				int mon = p_tm_member[1];
				switch(mon){
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:
						max = 31;
						break;

					case 2:
						max = 28;
						if(is_leap(year)){

							max = 29;
						}
						break;
					case 4:
					case 6:
					case 9:
					case 11:
						max = 30;
						break;

				}
				break;

			case 3:
				min = 0;
				max = 23;
				break;

			case 4:
				min = 0;
				max = 59;
				break;

			case 5:
				min = 0;
				max = 59;
				break;
		}

		if( !is_valid_tm_member(member, min, max)){
			printf("%s\n", TIP_INVALID_PARAM );
			return NULL;
		}

		*p = member;
		index ++;
		p ++;
	}

	p_tm_member[6] = VAL_END;

	return p_tm_member;
}

int set_date_time(int* args){

	time_t t;
	struct tm * p_tm;

	time(&t);
	p_tm = localtime(&t);

	p_tm->tm_year = args[0] == -1 ? p_tm->tm_year : args[0] - 1900;
	p_tm->tm_mon = args[1] == -1 ? p_tm->tm_mon : args[1] - 1;
	p_tm->tm_mday = args[2] == -1 ? p_tm->tm_mday : args[2] - 1;
	p_tm->tm_hour = args[3] == -1 ? p_tm->tm_hour : args[3];
	p_tm->tm_min = args[4] == -1 ? p_tm->tm_min : args[4];
	p_tm->tm_sec = args[5] == -1 ? p_tm->tm_sec : args[5];

	t = mktime(p_tm);

	return stime(&t);
}
