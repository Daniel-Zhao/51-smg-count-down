#include <reg51.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit key=P2^5;

unsigned int second=12;
unsigned int gewei;
unsigned int shiwei;
unsigned int i;
unsigned int num=0;//计数

unsigned char code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
																0x7f,0x6f};/*,0x77,0x7c,0x39,0x5e,0x79,0x71};*///显示0~F的值

void delay(unsigned int i)//us
{
	while(--i);	
}

void DigDisplay()
{
	unsigned char i;
	for(i=0;i<2;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0;	P0=smgduan[gewei]; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0;	P0=smgduan[shiwei]; break;//显示第1位
		}
		delay(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
 }

void main()
{	
	TMOD=0x01;
	TH0=(65535-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		gewei = second%10; //个位
		shiwei = second/10%10; //十位		
		DigDisplay();			
  	}
}

void time() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	if(num==20) //50ms定时，50*20=1s
	{
			num=0;
			second--;
		if(second == 0)
		{
			second = 12;
		}
	}
}
