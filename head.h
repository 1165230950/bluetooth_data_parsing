#include <stdio.h>
#ifndef head_h
#define head_h


typedef struct phone_format{
	char state[50];
	char name[256];
	char number[256];
	char date_time[100];
}parsing_result;

struct phone_format *parsing_data(FILE *);


#endif
