#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
int num_flag=0; //控制调用successful还是defeat 
int c_flag=0;   //控制调用失败后的函数 
int flag1=0;    //控制成功后调用后的函数 
struct content         //文件每行写入存储 
{
	char contents[80];
	struct content *next;	
}; 
char menu(void);  
void xinjian(void);
void watch(void);
void shanchu(void);
void exit_program(void);
void check_lnk(char *p);
void destroy(struct content *head);
void successful_con(void);
void defeat_con(void);
void welcome();
void welcome()   //欢迎界面 
{
	int i,j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	for(i=0;i<8;i++)
	{
		printf("\n");
	}
	for(i=0;i<35;i++)
	{
		printf(" ");
	}
	printf("欢           迎             使            用");
	printf("\n\n");
	for(i=0;i<35;i++)
	{
		printf(" ");
	}
	printf("      记             事             本      "); 
	for(i=0;i<1000000;i++)
	{
		for(j=0;j<1000;j++);
	}
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void successful_con(void)   //控制是否继续 
{
	char ch_flag;
	fflush(stdin);
	printf("是否继续: y/n?  ");
	scanf("%c",&ch_flag);
	if(ch_flag=='y'||ch_flag=='Y')
	{
		flag1=1;
	}
	else if(ch_flag=='n'||ch_flag=='N')
	{
		num_flag=0;
	}
	else
	{
		printf("请输入正确的指令\n");
		successful_con();
	}
}
void defeat_con(void)   //失败后强制重新 
{
	if(c_flag==1)
	{
		watch();
		c_flag=0;
	}
	else
	{
		fflush(stdin);
		shanchu();
		c_flag=0;
	}
}
char menu(void)    //显示功能菜单 
{
	int i;
	char flag;
	fflush(stdin);
	for(i=0;i<30;i++)
	{
		printf("*");
	}
	printf("\n");
	printf("*                            *");
	printf("\n");
	printf("*                            *");
	printf("\n");
	printf("*       a、新建文件          *");
	printf("\n");
	printf("*       b、查看文件          *");
	printf("\n");
	printf("*       c、删除文件          *");
	printf("\n");
	printf("*       d、退出程序          *");
	printf("\n");
	printf("*       按Enter继续!         *");
	printf("\n");
	printf("*                            *");
	printf("\n");
	printf("*                            *");
	printf("\n");
	for(i=0;i<30;i++)
	{
		printf("*");
	}
	printf("\n");
	printf("请输入你的选择:");
	printf("\n");
	flag=getchar();
	return flag;
}
void xinjian()        //新建文件 
{
	char *p,*cont;
	FILE *fp;
	char ch;
	int i,flag,len,k; 
	struct content *head,*q,*s; 
	p=(char*)malloc(80);
	cont=(char*)malloc(80);
	fflush(stdin);
	printf("请输入文件名:");
	printf("\n");
	fgets(p,80,stdin);    
	if(p[strlen(p)-1]=='\n') 
	{
		p[strlen(p)-1]='\0';
	}
	check_lnk(p);
	fp=fopen(p,"a+");
	printf("请输入文件内容(按Enter换行，每行最多80个英文字符或者四十个中文字符,按#结束输入):");
	printf("\n");
	printf("Tips:在文件中想要输入#,请使用转义字符\\");
	printf("\n");
	scanf("%s",cont);
	head=s=(struct content*)malloc(sizeof(struct content));
	head->next=NULL;
	while(cont[0]!='#')
	{
		q=(struct content*)malloc(sizeof(struct content));
		for(i=1;i<80;i++)
		{
			if(cont[i]=='#')
			{
				if(cont[i-1]!='\\')
				{
					cont[i]='\0';
					flag=1;
					break;
				}
				else
				{
					len=strlen(cont);
					cont[i-1]='#';
					for(k=i;k<len;k++)
					{
						cont[k]=cont[k+1];
					}
				}
			}
		}
		strcpy(q->contents,cont);
		q->next=s->next;
		s->next=q;
		s=q;
		fprintf(fp,"%s\n",q->contents);
		if(flag==1)
		{
			flag=0;
			break;
		}
		scanf("%s",cont);
	}
	printf("新建文件%s完毕",p);
	printf("\n");
	fclose(fp);
	destroy(head);
	num_flag=1;
}
void check_lnk(char *p)    //检查文件后缀名是否合法，不合法使其合法 
{
	int len;
	len=strlen(p);
	fflush(stdin);
	if((p[len-1]=='t'||p[len-1]=='T')&&(p[len-2]=='x'||p[len-2]=='X')&&(p[len-3]=='t'||p[len-3]=='T')&&p[len-4]=='.')
	{
	}
	else
	{
		if(len>=76)
		{
			printf("文件名长度超过最大限度，请重新输入文件名:");
			printf("\n");
			fgets(p,80,stdin);
			check_lnk(p);
		}
		else
		{
			p[len]='.';
			p[len+1]='t';
			p[len+2]='x';
			p[len+3]='t';
			p[len+4]='\0';	
		}
	}
}
void destroy(struct content *head)     //销毁链表。释放内存 
{
	struct content *p,*q;
	p=head;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
	}
}
void watch(void)      //查看文件 
{
	char *note;
	FILE *fp1;
	char ch;
	note=(char*)malloc(80);
	fflush(stdin);
	printf("请输入文件名:");
	printf("\n");
	fgets(note,80,stdin);    
	if(note[strlen(note)-1]=='\n') 
	{
		note[strlen(note)-1]='\0';
	}
	check_lnk(note);
	fp1=fopen(note,"r");
	if(fp1==NULL)
	{
		printf("文件%s不存在,即将重新输入",note);
		printf("\n");
		num_flag=-1;
		c_flag=1;
	}
	else
	{
		printf("%s文件内容为:",note);
		printf("\n");
		while(!feof(fp1))
		{
			fscanf(fp1,"%c",&ch);
			if(ch=='\n')
			{
				printf("\n");
				continue;
			}
			else
			{
				printf("%c",ch);
			}
		}
		fclose(fp1);
		num_flag=1;
	}
}
void shanchu(void)          //删除文件 
{
	FILE *fp2;
	char *q;
	int flag;
	q=(char*)malloc(80);
	fflush(stdin);
	printf("请输入你要删除的文件名:");
	printf("\n");
	fgets(q,80,stdin);   
	if(q[strlen(q)-1]=='\n') 
	{
		q[strlen(q)-1]='\0';
	}
	check_lnk(q);
	fp2=fopen(q,"r");
	if(fp2==NULL)
	{
		printf("文件%s不存在,即将重新输入删除文件名",q);
		printf("\n");
		num_flag=-1;
		c_flag=-1;
	}
	else
	{
		fclose(fp2);
		flag=remove(q);
		if(flag==0)
		{
			printf("删除文件%s成功!",q);
			printf("\n");
			num_flag=1;
		}
		if(flag==-1)
		{
			printf("删除文件%s失败，即将重新执行删除操作",q);
			printf("\n");
			num_flag=-1;
			c_flag=-1;
		}
	}
}
void exit_program(void)      //程序退出 
{
	fflush(stdin);
	printf("程序退出!");
	printf("\n");
	exit(0);
}
int main(void)
{
	char m,flag;
	int n=1;
	welcome();
	while(n)
	{
		flag=menu();
		switch(flag)
		{
			case 'a':
				xinjian();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							xinjian();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'A':
				xinjian();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							xinjian();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'b':
				watch();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							watch();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'B':
				watch();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							watch();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'c':
				shanchu();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							shanchu();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'C':
				shanchu();
				while(num_flag!=0)
				{
					if(num_flag==1)
					{
						successful_con();
						if(flag1==1)
						{
							shanchu();
							flag1=0;
						}
					}
					else
					{
						defeat_con();
					}
				}
				break;
			case 'd':
				exit_program();
				break;
			case 'D':
				exit_program();
				break;
			case '\n':
				break;
			default:
				printf("请输入正确的选择!");
				printf("\n");
				break;
		}
	}
}
