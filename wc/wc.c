#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CharCount(FILE *f) //�����ļ����ַ���Ŀ -c
{
	char c;
	int count=0;
	while(!feof(f))
	{
		c=fgetc(f);
		if(c!=' '&&c!='\n'&&c!='\t')    //���Ƕ�ȡ���ķǿո�س����ж�Ϊ�ַ�
			count++;
	}
	fclose(f);
	printf("The number of character is %d.\n",count);
}

void WordCount(FILE *f) //�����ļ��Ĵ���Ŀ -w
{
	char w;
	int count=0;
	int tag=1;    //���ڼ�¼�ļ�λ�ñ���Ƿ�����ͬһ�����ڣ�Ϊ0˵�����ڣ�Ϊ1˵�������µ���
	while(!feof(f))
	{
		w=fgetc(f);
		if((w>='A'&&w<='Z')||(w>='a'&&w<='z'))
		{
			if(1==tag)   //tagΪ1��������+1��ͬʱtag��0
			{
				count++;
				tag=0;
			}
		}
		else tag=1;
	}
	fclose(f);
	printf("The number of word is %d.\n",count);
}

void LineCount(FILE *f)  //�����ļ�������Ŀ -l
{
	char l;
	int count=0;
	fgetc(f);
	if(!feof(f))       //�ж��Ƿ��ǿհ��ļ�������Ϊ�հ��ļ�������+1�������س��Զ�+1
	{
		count++;
		rewind(f);
		while(!feof(f))
		{
			l=fgetc(f);
			if(l=='\n'||l=='\t')
				count++;
		}
	}
	fclose(f);
	printf("The number of line is %d.\n",count);
}

int main(int argc,char* argv[])         //�������������븳����������ֵ
{
	FILE *fp;
	if((fp=fopen(argv[argc-1],"r"))==NULL){
		printf("Please input the correct filename!\n");
		exit(0);
	}
	else if(!strcmp(argv[1],"-c"))
		CharCount(fp);
	else if(!strcmp(argv[1],"-w"))
		WordCount(fp);
	else if(!strcmp(argv[1],"-l"))
		LineCount(fp);
	else printf("Please input the correrct parameter!\n");
	return 0;
}
