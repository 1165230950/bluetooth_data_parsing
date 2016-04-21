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
		printf("%s %s %s %s\n", head->name,  head->number, head->date_time, head->state);
		fclose(fp);
	}

	return 0;
}
