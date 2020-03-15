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
			if(l=='\n')
				count++;
		}
	}
	fclose(f);
	printf("The number of line is %d.\n",count);
}

void BlankLineCount(FILE *f)   //计算空白行
{
	char b;
	int blankline=0;     //统计空白行数
	int chcount=0;       //统计字符个数
	while(!feof(f))
	{
		b=fgetc(f);
		if(0==chcount)
		{
			if(b=='\n')
				blankline++;
			else if(b!=' '&&b!='\t')
				chcount++;
		}
		else if(1==chcount)
		{
			if(b=='\n')
			{
				blankline++;
				chcount=0;
			}
			else if(b!=' '&&b!='\t')
				chcount++;
		}
		else
		{
			if(b=='\n')
				chcount=0;
		}
	}
	if(chcount<=1)           //判断最后一行是否为空白行
		blankline++;
	fclose(f);
	printf("The number of blankline is %d.\n",blankline);
}

void CodeLineCount(FILE *f)    //计算代码行
{
	char c;
	int chcount=0;
	int codeline=0;
	while(!feof(f))
	{
		c=fgetc(f);
		if(chcount<=1)
		{
			if(c=='\n')
				chcount=0;
			else if(c!=' '&&c!='\t')
				chcount++;
		}
		else
		{
			if(c=='\n')
			{
				codeline++;
				chcount=0;
			}
		}
	}
	if(chcount<=1)           //判断最后一行是否为代码行
		codeline++;
	fclose(f);
	printf("The number of codeline is %d.\n",codeline);
}

void CommentLineCount(FILE *f) //计算单行注释行的行数
{
	char c;
	int chcount=0;       //字符数
	int commentline=0;   //注释行数
	int tag=0;           //tag为1表示该行为注释行，为0表示非注释行
	int flag=0;          //flag为1表示出现'/'
	while(!feof(f))
	{
		c=fgetc(f);
		if(chcount<=1)
		{
			if(c=='\n')
			{
				if(tag==1)
					commentline++;
				tag=0;
				flag=0;
				chcount=0;
			}
			else if(c=='/')
			{
				if(flag==0)
					flag=1;
				else
					tag=1;
			}
			else if(c!=' '&&c!='\t')
			{
				chcount++;
				flag=0;
			}
			else flag=0;
		}
		else
		{
			if(c=='\n')
			{
				tag=0;
				flag=0;
				chcount=0;
			}
		}
	}
	if(tag==1)           //判断最后一行是否为注释行
		commentline++;
	fclose(f);
	printf("The number of commentline is %d.\n",commentline);
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
	else if(!strcmp(argv[1],"-a"))
	{
		CodeLineCount(fp);
		BlankLineCount(fp);
		CommentLineCount(fp);
	}
	else printf("Please input the correrct parameter!\n");
	return 0;
}
