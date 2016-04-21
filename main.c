#include <stdio.h>
#include <stdlib.h>
#include "head.h"

void error()
{
	printf("请输入正确格式：exec + filename\n");
	exit(0);
}

int main(int argc, char *argv[])
{
int ch;
	if(argc != 2) error();
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("file open failed\n");
		return 0;
	}
	parsing_result *head = parsing_data(fp);
	if(head == NULL){
		printf("file parsing failed\n");
		fclose(fp);
		return 0;
	}else{
		int i;
		for(i=0; i< head->sign+1; i++){
			printf("%s %s %s %s\n", head->name[i],  head->number[i], head->date_time[i], head->state[i]);
		}
	}
	close(fp);

	return 0;
}
