#include "head.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct phone_format *parsing_data(FILE *fp)
{
	parsing_result *head = malloc(sizeof(parsing_result *));
	head->sign = 0;
	int ch;
	int i, length, sign=0;
	for(i=0; i<6; i++)
	{
		switch(i)
		{
			case 0:
				if(fscanf(fp,"%x",&ch) == EOF){
					printf("(case0)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}else if(ch != 208){
					printf("(case0!)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				
				}
				sign ++;
				break;
			case 1:
				if(fscanf(fp,"%x", &ch) == EOF){
					printf("(case1)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}else if(ch != 1){
					printf("(case1!)file parsing fialed\n");
					printf("%d\n", sign);
					return NULL;
				}
				break;
			case 3:
				if(fscanf(fp,"%x",&ch) == EOF){
					printf("(case3)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}else if(ch != 0){
					printf("(case3!)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}
				break;
			case 5:
				if(fscanf(fp, "%x", &ch) == EOF){
					printf("(case5)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}else if(ch != 1){
					printf("(case5!)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}
				break;
			default:
				if(fscanf(fp, "%x", &ch) == EOF){
					printf("(case5)file parsing failed\n");
					printf("%d\n", sign);
					return NULL;
				}
				break;
		}
		
	}

/*============================解析姓名================================*/
while(1)
{
	head->state[head->sign] = malloc(100);
	head->number[head->sign] = malloc(100);
	head->name[head->sign] = malloc(100);
	head->date_time[head->sign] = malloc(100);
	if(fscanf(fp,"%x",&length) == EOF){
		printf("file parsing failed\n");
		printf("%d\n", sign);
		return NULL;
	}
	for(i=0; i<length; i++)
	{
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("2 file parsing failed\n");
			printf("%d\n", sign);
			return NULL;
		}else if(ch/0x10 == 0xd){
			i--;
			sign ++;
			continue;
		}
		head->name[head->sign][i] = (char)ch;
	}
	head->name[head->sign][i] = '\0';
//	printf("%s\n",  head->name[head->sign]);
/*===========================解析号码状态=============================*/
	if(fscanf(fp, "%x", &ch) == EOF){
		printf("3file parsing failed\n");
		printf("%d\n", sign);
		return NULL;
	}else if(ch/0x10 == 0xd){
		sign ++;
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("3!file parsing failed\n");
			printf("%d\n", sign);
			return NULL;
		}else if((ch >= 1 && ch<= 3) || (ch >= 33 && ch <= 35)){
			if(ch == 1 || ch == 33)
				strcpy(head->state[head->sign], "未接来电");
			else if(ch == 2 || ch == 34)
				strcpy(head->state[head->sign], "已接来电");
			else strcpy(head->state[head->sign], "已拨");
			
		}else{
			printf("3!!file parsing failed\n");
			printf("%d\n", sign);
			return NULL;
		}
	}else if((ch >= 1 && ch <= 3) || (ch >= 33 && ch <= 35)){
		if(ch == 1 || ch == 33)
			strcpy(head->state[head->sign], "未接来电");
		else if(ch == 2 || ch == 34)
			strcpy(head->state[head->sign], "已接来电");
		else strcpy(head->state[head->sign], "已拨");
	}else{
		printf("3!!!file parsing failed\n");
		printf("%d\n", sign);
		return NULL;
	}
//	printf("%s\n",head->state[head->sign]);
/*=============================解析号码===============================*/
	if(fscanf(fp, "%x", &ch) == EOF){
		printf("4file parsing failed\n");
		printf("%d\n", sign);
		return NULL;
	}
	length = ch;
	for(i=0; i<length; i++)
	{
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("4file parsing failed\n");
			printf("%d\n", sign);
			return NULL;
		}else if(ch/0x10 == 0xd){
			i--;
			sign ++;
			continue;
		}
		head->number[head->sign][i] = (char)ch;
	}
	head->number[head->sign][i] = '\0';
//	printf("%s\n", head->number[head->sign]);
/*==============================解析日期==============================*/
	for(i=0; i<6; i++)
	{
		int len;
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("5file parsing failed\n");
			printf("%d\n", sign);
			return NULL;
		}else if(ch/0x10 == 0xd){
			i--;
			sign ++;
			continue;
		}else if(i == 0){
			sprintf(head->date_time[head->sign], "%d日",ch);
		}else if(i == 1){
			len = strlen(head->date_time[head->sign]);
			sprintf(head->date_time[head->sign]+len, "%d月",ch);
		}else if(i == 2){
			len = strlen(head->date_time[head->sign]);
			sprintf(head->date_time[head->sign]+len, "%d年 ",ch);
		}else{
			len = strlen(head->date_time[head->sign]);
			if(i != 5)
				sprintf(head->date_time[head->sign]+len, "%d:",ch);
			else
				sprintf(head->date_time[head->sign]+len, "%d",ch);
		}
	}
//	printf("%s\n",head->date_time[head->sign]);

	if(fscanf(fp, "%x", &ch) == EOF) break;
	else if(ch/0x10 == 0xd){
		sign ++;
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("parsing the interrupt sign= %d\n", sign);
			return NULL;
		}else if(fscanf(fp, "%x", &ch) == EOF){
			printf("parsing the interrupt sign = %d\n", sign);
			return NULL;
		}else if(ch != 1){
			printf("parsing the interrupt sign=%d ch= %x\n",sign,ch);
			return NULL;
		}
	}
	else if(fscanf(fp, "%x", &ch) == EOF){
		printf("parsing the interrupt sign= %d\n", sign);
		return NULL;
	}else if(ch/0x10 == 0xd){
		sign ++;
		if(fscanf(fp, "%x", &ch) == EOF){
			printf("parsing the interrupt sign= %d\n", sign);
			return NULL;
		}else if(ch != 1){
			printf("parsing the interrupt sign=%d ch= %x\n",sign,ch);
			return NULL;
		}
	
	}else if(ch != 1){
		printf("parsing the interrupt sign=%d ch= %x\n",sign,ch);
		return NULL;
	}
	head->sign ++;
}//end while(1)
	return head;
}

