#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CharCount(FILE *f) //计算文件的字符数目 -c
{
	char c;
	int count=0;
	while(!feof(f))
	{
		c=fgetc(f);
		if(c!=' '&&c!='\n'&&c!='\t')    //若非读取到的非空格回车则判断为字符
			count++;
	}
	fclose(f);
	printf("The number of character is %d.\n",count);
}

void WordCount(FILE *f) //计算文件的词数目 -w
{
	char w;
	int count=0;
	int tag=1;    //用于记录文件位置标记是否仍在同一单词内，为0说明仍在，为1说明遇到新单词
	while(!feof(f))
	{
		w=fgetc(f);
		if((w>='A'&&w<='Z')||(w>='a'&&w<='z'))
		{
			if(1==tag)   //tag为1，单词数+1，同时tag置0
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

void LineCount(FILE *f)  //计算文件的行数目 -l
{
	char l;
	int count=0;
	fgetc(f);
	if(!feof(f))       //判断是否是空白文件，若不为空白文件则行数+1，遇到回车自动+1
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

int main(int argc,char* argv[])         //在命令行中输入赋予参数具体的值
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
