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
			if(l=='\n')
				count++;
		}
	}
	fclose(f);
	printf("The number of line is %d.\n",count);
}

void BlankLineCount(FILE *f)   //����հ���
{
	char b;
	int blankline=0;     //ͳ�ƿհ�����
	int chcount=0;       //ͳ���ַ�����
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
	if(chcount<=1)           //�ж����һ���Ƿ�Ϊ�հ���
		blankline++;
	fclose(f);
	printf("The number of blankline is %d.\n",blankline);
}

void CodeLineCount(FILE *f)    //���������
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
	if(chcount<=1)           //�ж����һ���Ƿ�Ϊ������
		codeline++;
	fclose(f);
	printf("The number of codeline is %d.\n",codeline);
}

void CommentLineCount(FILE *f) //���㵥��ע���е�����
{
	char c;
	int chcount=0;       //�ַ���
	int commentline=0;   //ע������
	int tag=0;           //tagΪ1��ʾ����Ϊע���У�Ϊ0��ʾ��ע����
	int flag=0;          //flagΪ1��ʾ����'/'
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
	if(tag==1)           //�ж����һ���Ƿ�Ϊע����
		commentline++;
	fclose(f);
	printf("The number of commentline is %d.\n",commentline);
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
	else if(!strcmp(argv[1],"-a"))
	{
		CodeLineCount(fp);
		BlankLineCount(fp);
		CommentLineCount(fp);
	}
	else printf("Please input the correrct parameter!\n");
	return 0;
}
