#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int CharCount(FILE *f) //计算文件的字符数目 -c
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
	return count;
}

int WordCount(FILE *f) //计算文件的词数目 -w
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
	return count;
}

int LineCount(FILE *f)  //计算文件的行数目 -l
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
	return count;
}

int BlankLineCount(FILE *f)   //计算空白行
{
	char b;
	int blankline=0;     //统计空白行数
	int chcount=0;       //统计字符个数
	fgetc(f);
	if(!feof(f))       //判断是否是空白文件，若为空白文件则行数为0
	{
		rewind(f);
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
	}
	fclose(f);
	printf("The number of blankline is %d.\n",blankline);
	return blankline;
}

int CodeLineCount(FILE *f)
{
	char c;
	int codeline=0;       //代码行数
	int chcount=0;        //字符数
	while(!feof(f))
	{
		c=fgetc(f);
		if(chcount==0)
		{
			if(c!='\n'&&c!=' '&&c!='\t')
				chcount++;
		}
		else if(chcount==1)
		{
			if(c=='\n')
				chcount=0;
			else if(c=='/')
				chcount++;
			else if(c!=' '&&c!='\t')
			{
				codeline++;
				chcount++;
			}
		}
		else
		{
			if(c=='\n')
				chcount=0;
		}
	}
	fclose(f);
	printf("The number of codeline is %d.\n",codeline);
	return codeline;
}

int main(int argc,char* argv[])         //在命令行中输入赋予参数具体的值
{
	FILE *fp;
	int a,b,c;
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
		a=LineCount(fp);
		fp=fopen(argv[argc-1],"r");
		b=BlankLineCount(fp);
		fp=fopen(argv[argc-1],"r");
		c=CodeLineCount(fp);
		printf("The number of commentline is %d.\n",a-b-c);
	}
	else printf("Please input the correrct parameter!\n");
	return 0;
}
