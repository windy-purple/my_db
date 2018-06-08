#include<stdio.h>
int main(void)
{
	int year,month,day,days=0,i,k;
	int time1[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	int time2[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	printf("请输入日期：");
	scanf("%d-%d-%d",&year,&month,&day);
	if((year%4==0&&year%100!=0)||(year%400==0))
	{	
		for(i=0;i<month-1;i++)
		{
			days=days+time1[i];
		}
		days=days+day;
		printf("%d-%d-%d是%d年的第%d天\n",year,month,day,year,days);
	}
	else
	{
		for(k=0;i<month-1;k++)
		{
			days=days+time2[k];
		}
		days=days+day;
		printf("%d-%d-%d是%d年的第%d天\n",year,month,day,year,days);
	}
}

		  
